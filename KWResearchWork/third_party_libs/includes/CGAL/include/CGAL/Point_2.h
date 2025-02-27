// Copyright (c) 1999  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kernel_23/include/CGAL/Point_2.h $
// $Id: Point_2.h 59630 2010-11-10 21:14:11Z glisse $
//
//
// Author(s)     : Andreas Fabri, Stefan Schirra

#ifndef CGAL_POINT_2_H
#define CGAL_POINT_2_H

#include <CGAL/Origin.h>
#include <CGAL/Bbox_2.h>
#include <boost/static_assert.hpp>
#include <boost/type_traits.hpp>
#include <CGAL/Kernel/Return_base_tag.h>
#include <CGAL/representation_tags.h>
#include <CGAL/Dimension.h>

namespace CGAL {

template <class R_>
class Point_2 : public R_::Kernel_base::Point_2
{
  typedef typename R_::RT                    RT;
  typedef typename R_::FT                    FT;
  typedef typename R_::Aff_transformation_2  Aff_transformation_2;
  typedef typename R_::Kernel_base::Point_2  RPoint_2;

  typedef Point_2                            Self;
  BOOST_STATIC_ASSERT((boost::is_same<Self, typename R_::Point_2>::value));

public:

  typedef Dimension_tag<2>  Ambient_dimension;
  typedef Dimension_tag<0>  Feature_dimension;

  typedef RPoint_2 Rep;
  typedef typename R_::Cartesian_const_iterator_2 Cartesian_const_iterator;

  const Rep& rep() const
  {
    return *this;
  }

  Rep& rep()
  {
    return *this;
  }

  typedef  R_   R;

  Point_2() {}

  Point_2(const Origin& o)
    : RPoint_2(typename R::Construct_point_2()(Return_base_tag(), o))
  {}

  Point_2(const RPoint_2& p)
    : RPoint_2(p)
  {}

  template < typename T1, typename T2 >
  Point_2(const T1 &x, const T2 &y)
    : Rep(typename R::Construct_point_2()(Return_base_tag(), x, y))
  {}

  Point_2(const RT& hx, const RT& hy, const RT& hw)
    : RPoint_2(typename R::Construct_point_2()(Return_base_tag(), hx, hy, hw))
  {}

  typename Qualified_result_of<typename R::Compute_x_2,Point_2>::type
  x() const
  {
    return typename R::Compute_x_2()(*this);
  }

  typename Qualified_result_of<typename R::Compute_y_2,Point_2>::type
  y() const
  {
    return typename R::Compute_y_2()(*this);
  }

  typename Qualified_result_of<typename R::Compute_x_2,Point_2>::type
  cartesian(int i) const
  {
    CGAL_kernel_precondition( (i == 0) || (i == 1) );
    return (i==0) ?  x() : y();
  }

  typename Qualified_result_of<typename R::Compute_x_2,Point_2>::type
  operator[](int i) const
  {
      return cartesian(i);
  }

  Cartesian_const_iterator cartesian_begin() const
  {
    return typename R::Construct_cartesian_const_iterator_2()(*this);
  }

  Cartesian_const_iterator cartesian_end() const
  {
    return typename R::Construct_cartesian_const_iterator_2()(*this,2);
  }



  typename Qualified_result_of<typename R::Compute_hx_2,Point_2>::type
  hx() const
  {
    return typename R::Compute_hx_2()(*this);
  }

  typename Qualified_result_of<typename R::Compute_hy_2,Point_2>::type
  hy() const
  {
    return typename R::Compute_hy_2()(*this);
  }

  typename Qualified_result_of<typename R::Compute_hw_2,Point_2>::type
  hw() const
  {
    return typename R::Compute_hw_2()(*this);
  }

  int dimension() const
  {
      return 2;
  }

  typename Qualified_result_of<typename R::Compute_hx_2,Point_2>::type
  homogeneous(int i) const
  {
    CGAL_kernel_precondition( (i >= 0) || (i <= 2) );
    return (i==0) ?  hx() : (i==1)? hy() : hw();
  }

  Bbox_2 bbox() const
  {
    return R().construct_bbox_2_object()(*this);
  }

  Point_2 transform(const Aff_transformation_2 &t) const
  {
    return t.transform(*this);
  }

};


template <class R >
std::ostream&
insert(std::ostream& os, const Point_2<R>& p,const Cartesian_tag&)
{
    switch(os.iword(IO::mode)) {
    case IO::ASCII :
        return os << p.x() << ' ' << p.y();
    case IO::BINARY :
        write(os, p.x());
        write(os, p.y());
        return os;
    default:
        return os << "PointC2(" << p.x() << ", " << p.y() << ')';
    }
}

template <class R >
std::ostream&
insert(std::ostream& os, const Point_2<R>& p,const Homogeneous_tag&)
{
  switch(os.iword(IO::mode))
  {
    case IO::ASCII :
        return os << p.hx() << ' ' << p.hy() << ' ' << p.hw();
    case IO::BINARY :
        write(os, p.hx());
        write(os, p.hy());
        write(os, p.hw());
        return os;
    default:
        return os << "PointH2(" << p.hx() << ", "
                                << p.hy() << ", "
                                << p.hw() << ')';
  }
}

template < class R >
std::ostream&
operator<<(std::ostream& os, const Point_2<R>& p)
{
  return insert(os, p, typename R::Kernel_tag() );
}


template <class R >
std::istream&
extract(std::istream& is, Point_2<R>& p, const Cartesian_tag&)
{
    typename R::FT x, y;
    switch(is.iword(IO::mode)) {
    case IO::ASCII :
        is >> x >> y;
        break;
    case IO::BINARY :
        read(is, x);
        read(is, y);
        break;
    default:
        std::cerr << "" << std::endl;
        std::cerr << "Stream must be in ascii or binary mode" << std::endl;
        break;
    }
    if (is)
	p = Point_2<R>(x, y);
    return is;
}


template <class R >
std::istream&
extract(std::istream& is, Point_2<R>& p, const Homogeneous_tag&)
{
  typename R::RT hx, hy, hw;
  switch(is.iword(IO::mode))
  {
    case IO::ASCII :
        is >> hx >> hy >> hw;
        break;
    case IO::BINARY :
        read(is, hx);
        read(is, hy);
        read(is, hw);
        break;
    default:
        std::cerr << "" << std::endl;
        std::cerr << "Stream must be in ascii or binary mode" << std::endl;
        break;
  }
  if (is)
    p = Point_2<R>(hx, hy, hw);
  return is;
}

template < class R >
std::istream&
operator>>(std::istream& is, Point_2<R>& p)
{
  return extract(is, p, typename R::Kernel_tag() );
}

} //namespace CGAL

#endif // CGAL_POINT_2_H
