// Copyright (c) 2003  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Triangulation_2/include/CGAL/Dummy_tds_2.h $
// $Id: Dummy_tds_2.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Mariette Yvinec

#ifndef CGAL_TRIANGULATION_DUMMY_TDS_2_H
#define CGAL_TRIANGULATION_DUMMY_TDS_2_H

#include <CGAL/basic.h>

namespace CGAL {

// Dummy TDS which provides all types that a vertex_base or cell_base can use.
struct Dummy_tds_2 {
  struct Vertex {};
  struct Face {};
  struct Edge {};

  struct Vertex_handle {};
  struct Face_handle {};

  struct Vertex_iterator {};
  struct Face_iterator {};
  struct Edge_iterator {};

  struct Edge_circulator {};
  struct Facet_circulator {};
  struct Face_circulator {};
  struct Vertex_circulator {};
  
  typedef std::size_t size_type;
};

} //namespace CGAL

#endif // CGAL_TRIANGULATION_DUMMY_TDS_2_H
