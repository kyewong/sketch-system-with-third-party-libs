// Copyright (c) 2007  GeometryFactory (France).  All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/BGL/include/CGAL/HalfedgeDS_vertex_max_base_with_id.h $
// $Id: HalfedgeDS_vertex_max_base_with_id.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Andreas Fabri, Fernando Cacciola

#ifndef CGAL_HALFEDGEDS_VERTEX_MAX_BASE_WITH_ID_H
#define CGAL_HALFEDGEDS_VERTEX_MAX_BASE_WITH_ID_H 1

#include <CGAL/HalfedgeDS_vertex_base.h>

namespace CGAL {

template < class Refs, class P, class ID>
class HalfedgeDS_vertex_max_base_with_id : public HalfedgeDS_vertex_base< Refs, Tag_true, P>
{
public:
    typedef HalfedgeDS_vertex_base< Refs, Tag_true, P> Base ;
    
    typedef ID size_type ;
    
    typedef P Point ;
    
private:

    size_type mID ;
    
public:

    HalfedgeDS_vertex_max_base_with_id() : mID ( size_type(-1) )  {}
    HalfedgeDS_vertex_max_base_with_id( Point const& p) : Base(p), mID ( size_type(-1) ) {}
    HalfedgeDS_vertex_max_base_with_id( Point const& p, size_type i ) : Base(p), mID(i) {}
    
    size_type&       id()       { return mID; }
    size_type const& id() const { return mID; }
};

} //namespace CGAL

#endif // CGAL_HALFEDGEDS_VERTEX_MAX_BASE_WITH_ID_H //
// EOF //
