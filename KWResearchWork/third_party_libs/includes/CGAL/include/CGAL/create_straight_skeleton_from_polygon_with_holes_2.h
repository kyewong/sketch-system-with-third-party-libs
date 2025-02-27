// Copyright (c) 2006-2008 Fernando Luis Cacciola Carballal. All rights reserved.
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

// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Straight_skeleton_2/include/CGAL/create_straight_skeleton_from_polygon_with_holes_2.h $
// $Id: create_straight_skeleton_from_polygon_with_holes_2.h 59832 2010-11-23 11:20:03Z lrineau $
//
// Author(s)     : Fernando Cacciola <fernando_cacciola@ciudad.com.ar>
//
#ifndef CGAL_CREATE_STRAIGHT_SKELETON_FROM_POLYGON_WITH_HOLES_2_H
#define CGAL_CREATE_STRAIGHT_SKELETON_FROM_POLYGON_WITH_HOLES_2_H

#include <CGAL/create_straight_skeleton_2.h>
#include <CGAL/Polygon_with_holes_2.h>

namespace CGAL {

template<class K>
boost::shared_ptr< Straight_skeleton_2<K> >
inline
create_interior_straight_skeleton_2 ( Polygon_with_holes_2<K> const& aPolyWithHoles )
{
  return create_interior_straight_skeleton_2(aPolyWithHoles.outer_boundary().vertices_begin()
                                            ,aPolyWithHoles.outer_boundary().vertices_end  ()
                                            ,aPolyWithHoles.holes_begin   ()
                                            ,aPolyWithHoles.holes_end     ()
                                            ,K()
                                            );
}

} // end namespace CGAL


#endif // CGAL_STRAIGHT_SKELETON_BUILDER_2_H //
// EOF //
