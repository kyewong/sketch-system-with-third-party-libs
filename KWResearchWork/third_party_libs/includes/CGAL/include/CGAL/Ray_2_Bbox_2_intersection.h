// Copyright (c) 2000  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Intersections_2/include/CGAL/Ray_2_Bbox_2_intersection.h $
// $Id: Ray_2_Bbox_2_intersection.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Geert-Jan Giezeman


#ifndef CGAL_RAY_2_BBOX_2_INTERSECTION_H
#define CGAL_RAY_2_BBOX_2_INTERSECTION_H

#include <CGAL/Bbox_2.h>
#include <CGAL/Ray_2.h>
#include <CGAL/kernel_assertions.h>
#include <CGAL/number_utils.h>

namespace CGAL {

class Bbox_2_Ray_2_pair_impl;

class Bbox_2_Ray_2_pair {
public:
    enum Intersection_results {NO_INTERSECTION, POINT, SEGMENT};
    ~Bbox_2_Ray_2_pair() ;
    Bbox_2_Ray_2_pair() ;
    Bbox_2_Ray_2_pair(Bbox_2_Ray_2_pair const &o) ;
    Bbox_2_Ray_2_pair(Bbox_2 const &box,
                      double x, double y, double dx, double dy) ;
    Bbox_2_Ray_2_pair& operator=(Bbox_2_Ray_2_pair const &o) ;
    Intersection_results intersection_type() const;
    bool intersection(double &x, double &y) const;
    bool intersection(double &x1, double &y1, double &x2, double &y2) const;
protected:
    Bbox_2_Ray_2_pair_impl *pimpl;
};

bool do_intersect_ray_2(
    const Bbox_2 &box, double x, double y, double dx, double dy);

template <class Ray>
bool do_intersect_ray_2(
    const Bbox_2 &box,
    const Ray &ray)
{
    double startx = to_double(ray->start().x());
    double starty = to_double(ray->start().y());
    double dx = to_double(ray->direction().to_vector().x());
    double dy = to_double(ray->direction().to_vector().y());
    return do_intersect_ray_2(box, startx, starty, dx, dy);
}

template <class Ray>
inline bool do_intersect_ray_2(
    const Ray &ray,
    const Bbox_2 &box)
{
    return do_intersect_ray_2(box, ray);
}
} //namespace CGAL



#endif
