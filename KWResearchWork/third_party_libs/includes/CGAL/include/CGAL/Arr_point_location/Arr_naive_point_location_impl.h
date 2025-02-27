// Copyright (c) 2005  Tel-Aviv University (Israel).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Arrangement_on_surface_2/include/CGAL/Arr_point_location/Arr_naive_point_location_impl.h $
// $Id: Arr_naive_point_location_impl.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Ron Wein   <wein@post.tau.ac.il>
//                 (based on old version by Eyal Flato)
#ifndef CGAL_ARR_NAIVE_POINT_LOCATION_FUNCTIONS_H
#define CGAL_ARR_NAIVE_POINT_LOCATION_FUNCTIONS_H

/*! \file
 * Member-function definitions for the Arr_naive_point_location<Arrangement>
 * class.
 */

namespace CGAL {

//-----------------------------------------------------------------------------
// Locate the arrangement feature containing the given point.
//
template <class Arrangement>
Object Arr_naive_point_location<Arrangement>::locate (const Point_2& p) const
{
  // Go over the arrangement vertices and check whether one of them equals
  // the query point.
  typename Traits_adaptor_2::Equal_2   equal = geom_traits->equal_2_object();
  typename Arrangement_2::Vertex_const_iterator  vit;
  Vertex_const_handle                            vh;

  for (vit = p_arr->vertices_begin(); vit != p_arr->vertices_end(); ++vit)
  {
    vh = vit;
    if (equal (p, vh->point()))
      return (CGAL::make_object (vh));
  }

  // Go over arrangement halfedges and check whether one of them contains
  // the query point in its interior.
  typename Traits_adaptor_2::Is_in_x_range_2    is_in_x_range = 
                                        geom_traits->is_in_x_range_2_object();
  typename Traits_adaptor_2::Compare_y_at_x_2   compare_y_at_x = 
                                        geom_traits->compare_y_at_x_2_object();
  typename Arrangement_2::Edge_const_iterator   eit;
  Halfedge_const_handle                         hh;

  for (eit = p_arr->edges_begin(); eit != p_arr->edges_end(); ++eit)
  {
    hh = eit;

    if (is_in_x_range (hh->curve(), p) &&
        compare_y_at_x (p, hh->curve()) == EQUAL)
    {
      return (CGAL::make_object (hh));
    }
  }

  // Go over all faces an locate the innermost one that contains the query
  // point in its interior.
  typename Arrangement_2::Face_const_iterator   fit;
  Face_const_handle                             fh;
  Face_const_handle                             f_inner;
  const Face_const_handle                       invalid_f;
  
  for (fit = p_arr->faces_begin(); fit != p_arr->faces_end(); ++fit)
  {
    fh = fit;
  
    if (top_traits->is_in_face (&(*fh), p, NULL))
    {
      // The current face contains p in its interior.
      if (f_inner == invalid_f ||
          f_inner->is_unbounded() ||
          f_inner->number_of_outer_ccbs() == 0)
      {
        // This is the first face that contains p we encounter:
        f_inner = fh;
      }
      else if (! fh->is_unbounded() && fh->number_of_outer_ccbs() > 0)
      {
        // As we have already some other containing face, one face must be
        // contained inside the other. Two check that, we select a
        // representative vertex of inner_f and check whether it is contained
        // in our current face.

        // This is a workaround for MSVC. For some reason the compiler barfs
        // when the iterator is not saved in a variable and only then the
        // source() of its value_type is accessed.
        typename Arrangement_2::Outer_ccb_const_iterator it =
          fh->outer_ccbs_begin();
        Vertex_const_handle  v = (*it)->source();

        if (top_traits->is_in_face (&(*f_inner), v->point(), NULL))
          f_inner = fh;
      }
    }
  }

  // Return the innermost face.
  CGAL_assertion (f_inner != invalid_f);
  return (CGAL::make_object (f_inner));
}

} //namespace CGAL

#endif
