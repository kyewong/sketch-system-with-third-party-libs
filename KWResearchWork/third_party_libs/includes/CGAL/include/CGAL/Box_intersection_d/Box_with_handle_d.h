// Copyright (c) 2004  Max-Planck-Institute Saarbruecken (Germany).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Box_intersection_d/include/CGAL/Box_intersection_d/Box_with_handle_d.h $
// $Id: Box_with_handle_d.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Lutz Kettner  <kettner@mpi-sb.mpg.de>
//                 Andreas Meyer <ameyer@mpi-sb.mpg.de>

#ifndef CGAL_BOX_INTERSECTION_D_BOX_WITH_HANDLE_D_H
#define CGAL_BOX_INTERSECTION_D_BOX_WITH_HANDLE_D_H

#include <CGAL/basic.h>
#include <CGAL/Box_intersection_d/Box_d.h>

namespace CGAL {

namespace Box_intersection_d {

// Generic template signature of boxes, specialized for ID_FROM_HANDLE policy
template<class NT_, int N, class Handle_, class IdPolicy = ID_FROM_HANDLE> 
class Box_with_handle_d : public Box_d< NT_, N, IdPolicy> {
protected:
    Handle_ m_handle;
public:
    typedef Box_d< NT_, N, IdPolicy> Base;
    typedef NT_                      NT;
    typedef Handle_                  Handle;
    Box_with_handle_d() {}
    Box_with_handle_d( Handle h) : m_handle(h) {}
    Box_with_handle_d( bool complete, Handle h): Base(complete), m_handle(h) {}
    Box_with_handle_d(NT l[N], NT h[N], Handle n) : Base( l, h), m_handle(n) {}
    Box_with_handle_d( const Bbox_2& b, Handle h) : Base( b), m_handle(h) {}
    Box_with_handle_d( const Bbox_3& b, Handle h) : Base( b), m_handle(h) {}
    Handle handle() const { return m_handle; }
};

// Specialization for ID_FROM_HANDLE policy
template<class NT_, int N, class Handle_> 
class Box_with_handle_d<NT_, N, Handle_, ID_FROM_HANDLE>
    : public Box_d< NT_, N, ID_NONE> {
protected:
    Handle_ m_handle;
public:
    typedef Box_d< NT_, N, ID_NONE> Base;
    typedef NT_                     NT;
    typedef Handle_                 Handle;
    typedef std::size_t             ID;

    Box_with_handle_d() {}
    Box_with_handle_d( Handle h) : m_handle(h) {}
    Box_with_handle_d( bool complete, Handle h): Base(complete), m_handle(h) {}
    Box_with_handle_d(NT l[N], NT h[N], Handle n) : Base( l, h), m_handle(n) {}
    Box_with_handle_d( const Bbox_2& b, Handle h) : Base( b), m_handle(h) {}
    Box_with_handle_d( const Bbox_3& b, Handle h) : Base( b), m_handle(h) {}
    Handle handle() const { return m_handle; }
    ID  id() const { return reinterpret_cast<ID>( &* m_handle); }
};


} // end namespace Box_intersection_d


} //namespace CGAL

#endif
