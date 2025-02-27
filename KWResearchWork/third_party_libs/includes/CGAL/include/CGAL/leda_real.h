// Copyright (c) 1999,2007  Utrecht University (The Netherlands),
// ETH Zurich (Switzerland), Freie Universitaet Berlin (Germany),
// INRIA Sophia-Antipolis (France), Martin-Luther-University Halle-Wittenberg
// (Germany), Max-Planck-Institute Saarbruecken (Germany), RISC Linz (Austria),
// and Tel-Aviv University (Israel).  All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public License as
// published by the Free Software Foundation; version 2.1 of the License.
// See the file LICENSE.LGPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Number_types/include/CGAL/leda_real.h $
// $Id: leda_real.h 56667 2010-06-09 07:37:13Z sloriot $
//
//
// Author(s)     : Stefan Schirra, Michael Hemmer

#ifndef CGAL_LEDA_REAL_H
#define CGAL_LEDA_REAL_H

#include <CGAL/number_type_basic.h>

#ifdef CGAL_USE_LEDA

#include <CGAL/leda_coercion_traits.h>

#include <CGAL/utils.h>
#include <CGAL/Interval_nt.h>

#include <utility>

#include <CGAL/LEDA_basic.h>
#if CGAL_LEDA_VERSION < 500
#include <LEDA/real.h>
#include <LEDA/interval.h>
#else
#include <LEDA/numbers/real.h>
#endif


namespace CGAL {

template <> class Algebraic_structure_traits< leda_real >

#if CGAL_LEDA_VERSION >= 500
  : public Algebraic_structure_traits_base< leda_real,
                                            Field_with_root_of_tag >  {
#else
  : public Algebraic_structure_traits_base< leda_real,
                                            Field_with_kth_root_tag >  {
#endif

  public:
    typedef Tag_true           Is_exact;
    typedef Tag_true           Is_numerical_sensitive;

    class Sqrt
      : public std::unary_function< Type, Type > {
      public:
        Type operator()( const Type& x ) const {
          return CGAL_LEDA_SCOPE::sqrt( x );
        }
    };

    class Kth_root
      : public std::binary_function<int, Type, Type> {
      public:
        Type operator()( int k,
                                        const Type& x) const {
            CGAL_precondition_msg(k > 0, "'k' must be positive for k-th roots");
            return CGAL_LEDA_SCOPE::root( x, k);
        }
    };

// Root_of is only available for LEDA versions >= 5.0
#if CGAL_LEDA_VERSION >= 500
    class Root_of {
      public:
        typedef Type result_type;

//        typedef leda_rational Boundary;
      private:
        template< class ForwardIterator >
        inline
        CGAL_LEDA_SCOPE::polynomial<Type>
        make_polynomial(ForwardIterator begin,
                        ForwardIterator end) const {
          CGAL_LEDA_SCOPE::growing_array<Type> coeffs;
          for(ForwardIterator it = begin; it < end; it++)
              coeffs.push_back(*it);
          return CGAL_LEDA_SCOPE::polynomial<Type>(coeffs);
        }
      public:
        template <class ForwardIterator>
        Type operator()( int k,
                       ForwardIterator begin,
                       ForwardIterator end) const {
            return CGAL_LEDA_SCOPE::diamond(k,make_polynomial(begin,end));
        }
/*        template <class ForwardIterator>
        Type operator()( leda_rational lower,
                                        leda_rational upper,
                                        ForwardIterator begin,
                                        ForwardIterator end) const {
            return CGAL_LEDA_SCOPE::diamond(lower,upper,
                                             make_polynomial(begin,end));
        };*/
    };

#endif


};

template <> class Real_embeddable_traits< leda_real >
  : public INTERN_RET::Real_embeddable_traits_base< leda_real , CGAL::Tag_true > {
  public:
    class Abs
      : public std::unary_function< Type, Type > {
      public:
        Type operator()( const Type& x ) const {
            return CGAL_LEDA_SCOPE::abs( x );
        }
    };

    class Sgn
      : public std::unary_function< Type, ::CGAL::Sign > {
      public:
        ::CGAL::Sign operator()( const Type& x ) const {
          return (::CGAL::Sign) CGAL_LEDA_SCOPE::sign( x );
        }
    };

    class Compare
      : public std::binary_function< Type, Type,
                                Comparison_result > {
      public:
        Comparison_result operator()( const Type& x,
                                            const Type& y ) const {
          return (Comparison_result) CGAL_LEDA_SCOPE::compare( x, y );
        }

        CGAL_IMPLICIT_INTEROPERABLE_BINARY_OPERATOR_WITH_RT( Type,
                                                      Comparison_result )

    };

    class To_double
      : public std::unary_function< Type, double > {
      public:
        double operator()( const Type& x ) const {
          // this call is required to get reasonable values for the double
          // approximation (as of LEDA-4.3.1)
          x.improve_approximation_to(53);
          return x.to_double();
        }
    };

    class To_interval
      : public std::unary_function< Type, std::pair< double, double > > {
      public:
        std::pair<double, double> operator()( const Type& x ) const {

#if CGAL_LEDA_VERSION >= 501
            leda_bigfloat bnum = x.to_bigfloat();
            leda_bigfloat berr = x.get_bigfloat_error();

            double dummy;
            double low = CGAL_LEDA_SCOPE::sub(bnum, berr, 53, CGAL_LEDA_SCOPE::TO_N_INF).to_double(dummy,
                                                     CGAL_LEDA_SCOPE::TO_N_INF);
            double upp = CGAL_LEDA_SCOPE::add(bnum, berr, 53, CGAL_LEDA_SCOPE::TO_P_INF).to_double(dummy,
                                                     CGAL_LEDA_SCOPE::TO_P_INF);

            std::pair<double, double> result(low, upp);
            CGAL_postcondition(Type(result.first)<=x);
            CGAL_postcondition(Type(result.second)>=x);
            return result;
#else
            CGAL_LEDA_SCOPE::interval temp(x); //bug in leda
            std::pair<double, double> result(temp.lower_bound(),temp.upper_bound());
            CGAL_postcondition_msg(Type(result.first)<=x,
                                                    "Known bug in LEDA <=5.0");
            CGAL_postcondition_msg(Type(result.first)>=x,
                                                    "Known bug in LEDA <=5.0");
            return result;
            // If x is very small and we look closer at x
            // (i.e. comparison or to_double() or to_bigfloat())
            // then x gets 0, which is really bad.
            // Therefore we do not touch x.
            // The LEDA interval above returns (-inf, inf) for
            // very small x, which is also bad and leads to
            // problems lateron. The postcondition fails in this
            // situation.
#endif
              // Original CGAL to_interval:
            //  Protect_FPU_rounding<true> P (CGAL_FE_TONEAREST);
            //  double approx = z.to_double();
            //  double rel_error = z.get_double_error();
            //  FPU_set_cw(CGAL_FE_UPWARD);
            //  Interval_nt_advanced ina(-rel_error,rel_error);
            //  ina += 1;
            //  ina *= approx;
            //  return ina.pair();
        }
    };
};


template <>
class Output_rep< ::leda::real > {
    const ::leda::real& t;
public:
    //! initialize with a const reference to \a t.
    Output_rep( const ::leda::real& tt) : t(tt) {}
    //! perform the output, calls \c operator\<\< by default.
    std::ostream& operator()( std::ostream& out) const {
        out << CGAL_NTS to_double(t);
        return out;
    }

};

template <>
class Output_rep< ::leda::real, CGAL::Parens_as_product_tag > {
    const ::leda::real& t;
public:
    //! initialize with a const reference to \a t.
    Output_rep( const ::leda::real& tt) : t(tt) {}
    //! perform the output, calls \c operator\<\< by default.
    std::ostream& operator()( std::ostream& out) const {
        if (t<0) out << "(" << ::CGAL::oformat(t)<<")";
        else out << ::CGAL::oformat(t);
        return out;
    }
};



} //namespace CGAL

// Unary + is missing for leda::real

namespace leda {
    inline real operator+( const real& i) { return i; }
} // namespace leda

//since types are included by leda_coercion_traits.h:
#include <CGAL/leda_integer.h>
#include <CGAL/leda_rational.h>
#include <CGAL/leda_bigfloat.h>
#include <CGAL/leda_real.h>

#endif // CGAL_USE_LEDA

#endif // CGAL_LEDA_REAL_H
