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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Boolean_set_operations_2/include/CGAL/Boolean_set_operations_2/Gps_sym_diff_functor.h $
// $Id: Gps_sym_diff_functor.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Baruch Zukerman <baruchzu@post.tau.ac.il>

#ifndef CGAL_GPS_SYM_DIFF_FUNCTOR_H
#define CGAL_GPS_SYM_DIFF_FUNCTOR_H

#include <CGAL/Boolean_set_operations_2/Gps_base_functor.h>

namespace CGAL {

template <class Arrangement_>
class Gps_sym_diff_functor : public Gps_base_functor<Arrangement_>
{
public:
  typedef Arrangement_                                    Arrangement_2;

  typedef typename Arrangement_2::Face_const_handle       Face_const_handle;
  typedef typename Arrangement_2::Face_handle             Face_handle;

  void create_face (Face_const_handle f1,
                    Face_const_handle f2,
                    Face_handle res_f)
  {
    if((f1->contained() && !f2->contained()) ||
       (!f1->contained() && f2->contained()))
    {
     res_f->set_contained(true);
    }
  }
};


} //namespace CGAL

#endif
