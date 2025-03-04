// Copyright (c) 2003,2004  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Apollonius_graph_2/include/CGAL/Apollonius_graph_2/Is_hidden_C2.h $
// $Id: Is_hidden_C2.h 56668 2010-06-09 08:45:58Z sloriot $
// 
//
// Author(s)     : Menelaos Karavelas <mkaravel@cse.nd.edu>



#ifndef CGAL_APOLLONIUS_GRAPH_2_IS_HIDDEN_C2_H
#define CGAL_APOLLONIUS_GRAPH_2_IS_HIDDEN_C2_H

#include <CGAL/Apollonius_graph_2/basic.h>


namespace CGAL {

namespace ApolloniusGraph_2 {

//--------------------------------------------------------------------


template<class K, class MTag>
class Is_hidden_2
{
public:
  typedef K                    Kernel;
  typedef MTag                 Method_tag;
  typedef typename K::Site_2   Site_2;
  typedef typename K::RT       RT;
  typedef typename K::Sign     Sign;

private:
  bool is_hidden(const Site_2& p, const Site_2& q,
		 const Integral_domain_without_division_tag&) const
  {
    RT w1 = p.weight();
    RT w2 = q.weight();
    Sign s = CGAL::sign( CGAL::square(p.x() - q.x())
			 + CGAL::square(p.y() - q.y())
			 - CGAL::square(w1 - w2)
			 );
    if ( s == POSITIVE ) { return false; }
    return (CGAL::compare(w1, w2) != SMALLER);
  }

  bool is_hidden(const Site_2& p, const Site_2& q,
		 const Field_with_sqrt_tag&) const
  {
    RT d = CGAL::sqrt(CGAL::square(p.x() - q.x())
		      + CGAL::square(p.y() - q.y()));
    Sign s = CGAL::sign(d - p.weight() + q.weight());

    return ( s != POSITIVE );
  }

public:
  typedef bool                 result_type;
  typedef Site_2               argument_type;

  inline bool operator()(const Site_2 &p, const Site_2 &q) const {
#ifdef AG2_PROFILE_PREDICATES
    ag2_predicate_profiler::is_trivial_counter++;
#endif
    return is_hidden(p, q, Method_tag());
  }
};


//--------------------------------------------------------------------

} //namespace ApolloniusGraph_2

} //namespace CGAL

#endif // CGAL_APOLLONIUS_GRAPH_2_IS_HIDDEN_C2_H
