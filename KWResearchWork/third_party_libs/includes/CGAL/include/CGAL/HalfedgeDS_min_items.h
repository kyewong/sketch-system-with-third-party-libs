// Copyright (c) 1997  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/HalfedgeDS/include/CGAL/HalfedgeDS_min_items.h $
// $Id: HalfedgeDS_min_items.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>

#ifndef CGAL_HALFEDGEDS_MIN_ITEMS_H
#define CGAL_HALFEDGEDS_MIN_ITEMS_H 1
#include <CGAL/HalfedgeDS_vertex_min_base.h>
#include <CGAL/HalfedgeDS_halfedge_min_base.h>
#include <CGAL/HalfedgeDS_face_min_base.h>

namespace CGAL {

class HalfedgeDS_min_items {
public:
    template < class Refs, class Traits>
    struct Vertex_wrapper {
        typedef HalfedgeDS_vertex_min_base< Refs>   Vertex;
    };
    template < class Refs, class Traits>
    struct Halfedge_wrapper {
        typedef HalfedgeDS_halfedge_min_base< Refs> Halfedge;
    };
    template < class Refs, class Traits>
    struct Face_wrapper {
        typedef HalfedgeDS_face_min_base< Refs>     Face;
    };
};

} //namespace CGAL
#endif // CGAL_HALFEDGEDS_MIN_ITEMS_H //
// EOF //
