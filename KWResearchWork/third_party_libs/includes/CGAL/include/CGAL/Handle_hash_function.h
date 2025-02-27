// Copyright (c) 1997-2000  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Hash_map/include/CGAL/Handle_hash_function.h $
// $Id: Handle_hash_function.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Michael Seel <seel@mpi-sb.mpg.de>
//                 Lutz Kettner <kettner@inf.ethz.ch>

#ifndef CGAL_HANDLE_HASH_FUNCTION_H
#define CGAL_HANDLE_HASH_FUNCTION_H

#include <CGAL/basic.h>
#include <cstddef>

namespace CGAL {

struct Handle_hash_function {
    typedef std::size_t result_type;
    template <class H> 
    std::size_t operator() (const H& h) const { 
        return std::size_t(&*h) / 
            sizeof( typename std::iterator_traits<H>::value_type);
    } 
};

} //namespace CGAL

#endif // CGAL_HANDLE_HASH_FUNCTION_H
// EOF
