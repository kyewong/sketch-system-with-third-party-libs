// Copyright (c) 2005 Rijksuniversiteit Groningen (Netherlands)
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Skin_surface_3/include/CGAL/Skin_surface_traits_3.h $
// $Id: Skin_surface_traits_3.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Nico Kruithof <Nico@cs.rug.nl>

#ifndef CGAL_SKIN_SURFACE_TRAITS_3_H
#define CGAL_SKIN_SURFACE_TRAITS_3_H

#include <CGAL/Regular_triangulation_euclidean_traits_3.h>
#include <CGAL/predicates/predicates_for_mixed_complex_3.h>

namespace CGAL { 

/** Input: a list of n weighted points p_1...p_n and a query point x.
    There is a plane separating the mixed cell defined by p_1...p_n-1
    and the mixed cell defined by p_1...p_n. The predicate tests
    whether x lies on the same side of this plane as the mixed cell
    defined by p_1...p_n-1 (NEGATIVE), on the plane (ZERO) or on the
    opposite side (POSITIVE).
 **/
template <class K>
class Side_of_mixed_cell_3 {
public:
  typedef typename K::FT             FT;
  typedef typename K::Bare_point     Bare_point;
  typedef typename K::Weighted_point Weighted_point;

  Side_of_mixed_cell_3(const FT &shrink) : s(shrink) {}
  
  typedef CGAL::Sign           result_type;
  
  result_type operator()(const Weighted_point &p1,
			 const Weighted_point &p2,
			 const Bare_point &x) const {
    return side_of_mixed_cellC3(p1.x(),p1.y(),p1.z(),p1.weight(),
				p2.x(),p2.y(),p2.z(),p2.weight(),
				x.x(),x.y(),x.z(),
				s);
  }
  result_type operator()(const Weighted_point &p1,
			 const Weighted_point &p2,
			 const Weighted_point &p3,
			 const Bare_point &x) const {
    return side_of_mixed_cellC3(p1.x(),p1.y(),p1.z(),p1.weight(),
				p2.x(),p2.y(),p2.z(),p2.weight(),
				p3.x(),p3.y(),p3.z(),p3.weight(),
				x.x(),x.y(),x.z(),
				s);
  }
  result_type operator()(const Weighted_point &p1,
			 const Weighted_point &p2,
			 const Weighted_point &p3,
			 const Weighted_point &p4,
			 const Bare_point &x) const {
    return side_of_mixed_cellC3(p1.x(),p1.y(),p1.z(),p1.weight(),
				p2.x(),p2.y(),p2.z(),p2.weight(),
				p3.x(),p3.y(),p3.z(),p3.weight(),
				p4.x(),p4.y(),p4.z(),p4.weight(),
				x.x(),x.y(),x.z(),
				s);
  }
  
private:
  FT s;
};

/** Input: Two weighted points
    Computes the anchor point of a Delaunay center and a Voronoi center
 **/
template <class K>
class Construct_anchor_point_3 {
public:
  typedef typename K::FT             FT;
  typedef typename K::Bare_point     Bare_point;

  Construct_anchor_point_3(const FT &shrink) : s(shrink) {}
  
  typedef Bare_point           result_type;
  
  result_type operator()(const Bare_point &p_del,
			 const Bare_point &p_vor) const {
    return Bare_point((1-s)*p_del.x() + s*p_vor.x(),
		      (1-s)*p_del.y() + s*p_vor.y(),
		      (1-s)*p_del.z() + s*p_vor.z());
  }
  
private:
  FT s;
};

template <class K_>
class Skin_surface_traits_base_3 
  : public Regular_triangulation_euclidean_traits_3<K_>
{
  typedef Regular_triangulation_euclidean_traits_3<K_> Base;
public:
  typedef K_                                  Kernel;
  typedef Skin_surface_traits_base_3<Kernel>  Self;

  typedef typename Kernel::FT                 FT;
  typedef typename Kernel::Point_3            Bare_point;
  typedef typename Base::Weighted_point       Weighted_point;
  typedef Weighted_point                      Weighted_point_3;

  typedef CGAL::Side_of_mixed_cell_3<Self>          Side_of_mixed_cell_3;
  typedef CGAL::Construct_weighted_circumcenter_3<Self> 
                                              Construct_weighted_circumcenter_3;
  typedef CGAL::Construct_anchor_point_3<Self> Construct_anchor_point_3;
  
 
  
  Skin_surface_traits_base_3() : s(-1) {
  }
  Skin_surface_traits_base_3(FT s) : s(s) {
  }
  void set_shrink(FT s_) { 
    s = s_; 
  }
  FT get_shrink() const {
    return s;
  }

  
  Side_of_mixed_cell_3 
  side_of_mixed_cell_3_object() const { 
    CGAL_assertion((s>0) && (s<1));
    return Side_of_mixed_cell_3(get_shrink()); }

  Construct_anchor_point_3
  construct_anchor_point_3_object() const
  { return Construct_anchor_point_3(get_shrink()); }

private:
  FT s;
};

// We need to introduce a "traits_base_3" class in order to get the
// specialization for Exact_predicates_inexact_constructions_kernel to work,
// otherwise there is a cycle in the derivation.
// Similar to Regular_triangulation_euclidean_traits_3
template < class K, bool UseFilteredPredicates=K::Has_filtered_predicates >
class Skin_surface_traits_3
  : public Skin_surface_traits_base_3<K>
{
  typedef Skin_surface_traits_base_3<K> Base;
public:
  Skin_surface_traits_3() {}
  Skin_surface_traits_3(typename Base::FT s) : Base(s) {}
  enum { Has_filtered_predicates=false };
};

} //namespace CGAL

// Now specialize for Filtered_kernel<CK>, to get
// the filtered traits automatically.
#include <CGAL/Skin_surface_filtered_traits_3.h>
#include <CGAL/Filtered_kernel.h>


namespace CGAL {

// Just FK would be nicer, but VC 2005 messes it up with an "FK" in a base class when compiling degenerate_test.cpp
template < typename Sst3FK >
class Skin_surface_traits_3 < Sst3FK,true >
  : public Skin_surface_filtered_traits_3 < Sst3FK >
{
  typedef Skin_surface_filtered_traits_3 < Sst3FK > Base;
public:
  typedef Sst3FK                                    Kernel;
  
  Skin_surface_traits_3() {}
  Skin_surface_traits_3(typename Base::FT s) :  Base(s) {}

};



} //namespace CGAL
#endif // CGAL_SKIN_SURFACE_TRAITS_3_H
