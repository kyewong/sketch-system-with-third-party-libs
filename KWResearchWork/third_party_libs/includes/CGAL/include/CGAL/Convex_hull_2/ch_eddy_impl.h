// Copyright (c) 1999  Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Convex_hull_2/include/CGAL/Convex_hull_2/ch_eddy_impl.h $
// $Id: ch_eddy_impl.h 56898 2010-06-20 21:48:20Z lrineau $
// 
//
// Author(s)     : Stefan Schirra

#ifndef CGAL_CH_EDDY_C
#define CGAL_CH_EDDY_C

#ifndef CGAL_CH_NO_POSTCONDITIONS
#include <CGAL/convexity_check_2.h>
#endif // CGAL_CH_NO_POSTCONDITIONS

#include <CGAL/Convex_hull_2/ch_assertions.h>
#include <CGAL/ch_selected_extreme_points_2.h>
#include <CGAL/algorithm.h>
#include <list>
#include <algorithm>
#include <boost/bind.hpp>

namespace CGAL {

template <class List, class ListIterator, class Traits>
void
ch__recursive_eddy(List& L, 
                        ListIterator  a_it, ListIterator  b_it, 
                        const Traits& ch_traits)
{
  using namespace boost;

  typedef  typename Traits::Point_2                         Point_2;    
  typedef  typename Traits::Left_turn_2                     Left_turn_2;
  typedef  typename Traits::Less_signed_distance_to_line_2  Less_dist;

  Left_turn_2 left_turn    = ch_traits.left_turn_2_object();
  
  CGAL_ch_precondition( \
    std::find_if(a_it, b_it, \
                 boost::bind(left_turn, *b_it, *a_it, _1)) \
    != b_it );


  ListIterator f_it = successor(a_it);
  Less_dist less_dist = ch_traits.less_signed_distance_to_line_2_object();
  ListIterator 
      c_it = std::min_element( f_it, b_it,  // max before
                               boost::bind(less_dist, *a_it, *b_it, _1, _2));
  Point_2 c = *c_it;

  c_it = std::partition(f_it, b_it, boost::bind(left_turn, c, *a_it, _1));
  f_it = std::partition(c_it, b_it, boost::bind(left_turn, *b_it, c, _1));
  c_it = L.insert(c_it, c);
  L.erase( f_it, b_it );

  if ( successor(a_it) != c_it )
  {
      ch__recursive_eddy( L, a_it, c_it, ch_traits);
  }
  if ( successor(c_it) != b_it )
  {
      ch__recursive_eddy( L, c_it, b_it, ch_traits);
  }
}

template <class InputIterator, class OutputIterator, class Traits>
OutputIterator
ch_eddy(InputIterator first, InputIterator last,
             OutputIterator  result,
             const Traits& ch_traits)
{
  using namespace boost;

  typedef  typename Traits::Point_2                         Point_2;    
  typedef  typename Traits::Left_turn_2                     Left_turn_2;
  typedef  typename Traits::Equal_2                         Equal_2;   

  Left_turn_2 left_turn    = ch_traits.left_turn_2_object();  
  Equal_2     equal_points = ch_traits.equal_2_object();   

  if (first == last) return result;
  std::list< Point_2 >   L (first, last);

  typedef typename std::list< Point_2 >::iterator  list_iterator;
  list_iterator   w, e;
  ch_we_point(L.begin(), L.end(), w, e, ch_traits);
  Point_2 wp = *w;
  Point_2 ep = *e;
  if (equal_points(wp,ep) )
  {
      *result = wp;  ++result;
      return result;
  }

  L.erase(w);
  L.erase(e);
  
  e = std::partition(L.begin(), L.end(), 
                     boost::bind(left_turn, ep, wp, _1) );
  L.push_front(wp);
  e = L.insert(e, ep);

  if ( successor(L.begin()) != e )
  {
      ch__recursive_eddy( L, L.begin(), e, ch_traits);
  }
  w = std::find_if( e, L.end(), boost::bind(left_turn, wp, ep, _1) );
  if ( w == L.end() )
  {
      L.erase( ++e, L.end() );
      return std::copy( L.begin(), L.end(), result );
  }
  w = L.insert(L.end(), wp);
  ch__recursive_eddy( L, e, w, ch_traits);


  CGAL_ch_postcondition( \
      is_ccw_strongly_convex_2( L.begin(), w, ch_traits) );
  CGAL_ch_expensive_postcondition( \
      ch_brute_force_check_2( first, last, \
                                   L.begin(), w, ch_traits ) );

  return std::copy( L.begin(), w, result );
}

} //namespace CGAL

#endif // CGAL_CH_EDDY_C
