// Copyright (c) 2005  Stanford University (USA).
// All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kinetic_data_structures/include/CGAL/Kinetic/internal/Instantaneous_adaptor.h $
// $Id: Instantaneous_adaptor.h 56668 2010-06-09 08:45:58Z sloriot $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_INSTANTANEOUS_ADAPTOR_H
#define CGAL_INSTANTANEOUS_ADAPTOR_H
#include <CGAL/Kinetic/basic.h>
#include <functional>

namespace CGAL { namespace Kinetic {

//! An object to help convert between moving objects and their static representations to wrap a predicate.
/*!  A ref counted pointer is stored to the part of the
  Instantaneous_kernel which actually performs the conversions.

  Look at the source to figure out how it works.
*/
template <class Static_predicate, class Kinetic_predicate, class Rep, class Argument>
class Instantaneous_adaptor
{
  typedef typename Rep::Time Time;

  BOOST_STATIC_ASSERT((boost::is_convertible<Time, typename Kinetic_predicate::Time>::value));
public:
  Instantaneous_adaptor(typename Rep::Handle rep,
			Static_predicate pred,
			Kinetic_predicate kpred): rep_(rep), pred_(pred), kpred_(kpred) {
  }

  typedef typename Static_predicate::result_type result_type;
  typedef Argument argument_type;
  typedef argument_type first_argument_type;
  typedef argument_type second_argument_type;
  typedef argument_type third_argument_type;
  typedef argument_type fourth_argument_type;
  typedef argument_type fifth_argument_type;

  result_type operator()(const first_argument_type &arg0) const
  {
    result_type ret;
    //bool check;

    if (rep_->time_is_nt() && !rep_->time_after()) {
      ret= pred_(rep_->static_object(arg0));
      //check= kpred_(rep_->kinetic_object(arg0), rep_->time());
    } else if (rep_->time_after()) {
      ret= static_cast<result_type>(kpred_(rep_->kinetic_object(arg0), rep_->time()));
    } else {
      ret= static_cast<result_type>(kpred_(rep_->kinetic_object(arg0), rep_->time()));
    }
    return ret;
  }

  result_type operator()(const first_argument_type &arg0,
			 const second_argument_type &arg1) const
  {
    if (rep_->time_is_nt() && !rep_->time_after()) {
      //std::cout << "Comparing " << arg0 << " and " << arg1 << " at time " << rep_->time() << std::endl;
      result_type ret= pred_(rep_->static_object(arg0), rep_->static_object(arg1));
      //std::cout << "Got " << ret << std::endl;
      //result_type check= kpred_(rep_->kinetic_object(arg0), rep_->kinetic_object(arg1), rep_->time());
      //CGAL_assertion(ret==check || ret== CGAL::ZERO);
      return ret;
    } else if (rep_->time_after()) {
      return static_cast<result_type>(kpred_.sign_after(rep_->kinetic_object(arg0),
                                                        rep_->kinetic_object(arg1),
                                                        rep_->time()));
    } else {
      return static_cast<result_type>(kpred_.sign_at(rep_->kinetic_object(arg0),
                                                     rep_->kinetic_object(arg1),
                                                     rep_->time()));
    }
  }

  result_type operator()(const first_argument_type &arg0,
			 const second_argument_type &arg1,
			 const third_argument_type &arg2) const
  {
    if (rep_->time_is_nt() && !rep_->time_after()) {
      return pred_(rep_->static_object(arg0), rep_->static_object(arg1),
                   rep_->static_object(arg2));
    } else if (rep_->time_after()) {
      return static_cast<result_type>(kpred_.sign_after(rep_->kinetic_object(arg0),
                                                        rep_->kinetic_object(arg1),
                                                        rep_->kinetic_object(arg2),
                                                        rep_->time()));
    } else {
      return static_cast<result_type>(kpred_.sign_at(rep_->kinetic_object(arg0),
                                                     rep_->kinetic_object(arg1),
                                                     rep_->kinetic_object(arg2),
                                                     rep_->time()));
    }
  }

  result_type operator()(const first_argument_type &arg0,
			 const second_argument_type &arg1,
			 const third_argument_type &arg2,
			 const fourth_argument_type &arg3) const
  {
    if (rep_->time_is_nt() && !rep_->time_after()) {
      return pred_(rep_->static_object(arg0), rep_->static_object(arg1),
		   rep_->static_object(arg2), rep_->static_object(arg3));
    } else if (rep_->time_after()){
      return static_cast<result_type>(kpred_.sign_after(rep_->kinetic_object(arg0),
                                                        rep_->kinetic_object(arg1),
                                                        rep_->kinetic_object(arg2),
                                                        rep_->kinetic_object(arg3),
                                                        rep_->time()));
    } else {
      return static_cast<result_type>(kpred_.sign_at(rep_->kinetic_object(arg0),
                                                     rep_->kinetic_object(arg1),
                                                     rep_->kinetic_object(arg2),
                                                     rep_->kinetic_object(arg3),
                                                     Time(rep_->time())));
    }
  }

  result_type operator()(const first_argument_type &arg0,
			 const second_argument_type &arg1,
			 const third_argument_type &arg2,
			 const fourth_argument_type &arg3,
			 const fifth_argument_type &arg4) const
  {
    if (rep_->time_is_nt() && !rep_->time_after()) {
      return pred_(rep_->static_object(arg0), rep_->static_object(arg1),
		   rep_->static_object(arg2), rep_->static_object(arg3),
		   rep_->static_object(arg4));
    } else if (rep_->time_after()) {
      return static_cast<result_type>(kpred_.sign_at(rep_->kinetic_object(arg0),
                                                     rep_->kinetic_object(arg1),
                                                     rep_->kinetic_object(arg2),
                                                     rep_->kinetic_object(arg3),
                                                     rep_->kinetic_object(arg4),
                                                     rep_->time()));
    } else {
      return static_cast<result_type>(kpred_.sign_at(rep_->kinetic_object(arg0),
                                                     rep_->kinetic_object(arg1),
                                                     rep_->kinetic_object(arg2),
                                                     rep_->kinetic_object(arg3),
                                                     rep_->kinetic_object(arg4),
                                                     rep_->time()));
    }
  }

protected:

  typename Rep::Handle rep_;
  Static_predicate pred_;
  Kinetic_predicate kpred_;
};

} } //namespace CGAL::Kinetic
#endif
