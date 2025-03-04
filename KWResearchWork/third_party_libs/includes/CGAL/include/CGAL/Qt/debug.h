// Copyright (c) 2008  GeometryFactory Sarl (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/GraphicsView/include/CGAL/Qt/debug.h $
// $Id: debug.h 45422 2008-09-09 11:56:57Z afabri $
// 
//
// Author(s)     : Andreas Fabri <Andreas.Fabri@geometryfactory.com>
//                 Laurent Rineau <Laurent.Rineau@geometryfactory.com>

#ifndef CGAL_QT_DEBUG_H
#define CGAL_QT_DEBUG_H

#include <CGAL/auto_link/Qt4.h>
#include <QString>

namespace CGAL {
namespace Qt {

/**
 *  Must be used like that:
 *     CGAL::Qt:traverse_resources(":/cgal"); // view CGAL resources
 *  or
 *     CGAL::Qt:traverse_resources(":"); // view all resources
 *  and displays the resources tree on std::cerr.
 */
void traverse_resources(const QString& name,
                        const QString& dirname = QString(),
                        int indent = 0);

} // namespace Qt
} // namespace CGAL


#endif // CGAL_QT_DEBUG_H
