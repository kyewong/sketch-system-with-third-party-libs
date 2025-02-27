// Copyright (c) 2009 INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_3/include/CGAL/Mesh_3/Mesh_sizing_field.h $
// $Id: Mesh_sizing_field.h 57256 2010-07-01 08:27:03Z stayeb $
//
//
// Author(s)     : Stephane Tayeb
//
//******************************************************************************
// File Description : Defines a sizing field stored into an external
// mesh triangulation
//******************************************************************************

#ifndef CGAL_MESH_3_MESH_SIZING_FIELD_H
#define CGAL_MESH_3_MESH_SIZING_FIELD_H

namespace CGAL {

namespace Mesh_3
{
  
/**
 * @class Mesh_sizing_field
 */
template <typename Tr, bool Need_vertex_update = true>
class Mesh_sizing_field
{
  // Types
  typedef typename Tr::Geom_traits   Gt;
  typedef typename Tr::Point         Point_3;
  typedef typename Gt::FT            FT;

  typedef typename Tr::Vertex_handle      Vertex_handle;
  typedef typename Tr::Cell_handle        Cell_handle;
  
public:
  // update vertices of mesh triangulation ? 
  static const bool is_vertex_update_needed = Need_vertex_update;
  
public:
  /**
   * Constructor
   */
  Mesh_sizing_field(Tr& tr);
  
  /**
   * Fill sizing field, using size associated to point in \c value_map
   */
  void fill(const std::map<Point_3, FT>& value_map);
  
  /**
   * Returns size at point \c p.
   */
  FT operator()(const Point_3& p) const
  { return this->operator()(p,last_cell_); }
  
  /**
   * Returns size at point \c p, using \c v to accelerate \c p location
   * in triangulation
   */
  FT operator()(const Point_3& p, const Vertex_handle& v) const
  { return this->operator()(p,v->cell()); }
  
  /**
   * Returns size at point \c p.
   */
  FT operator()(const Point_3& p, const Cell_handle& c) const;
  
  /**
   * Returns size at point \c p. Assumes that p is the centroid of c.
   */
  FT operator()(const Point_3& p, const std::pair<Cell_handle,bool>& c) const;
  
private:
  /**
   * Returns size at point \c p, by interpolation into tetrahedron.
   */
  FT interpolate_on_cell_vertices(const Point_3& p,
                                  const Cell_handle& cell) const;
  
  /**
   * Returns size at point \c p, by interpolation into facet (\c cell is assumed
   * to be an infinite cell).
   */
  FT interpolate_on_facet_vertices(const Point_3& p,
                                   const Cell_handle& cell) const;
  
private:
  /// The triangulation
  Tr& tr_;
  /// A cell that is used to accelerate location queries
  mutable Cell_handle last_cell_;
};
  
  
  
template <typename Tr, bool B>
Mesh_sizing_field<Tr,B>::
Mesh_sizing_field(Tr& tr)
  : tr_(tr)
  , last_cell_()
{
}  
  
  
template <typename Tr, bool B>
void
Mesh_sizing_field<Tr,B>::
fill(const std::map<Point_3, FT>& value_map)
{
  typedef typename Tr::Finite_vertices_iterator  Fvi;
  
  for ( Fvi vit = tr_.finite_vertices_begin() ;
        vit != tr_.finite_vertices_end() ;
        ++ vit )
  {
    typename std::map<Point_3, FT>::const_iterator find_result = 
      value_map.find(vit->point());
    
    if ( find_result != value_map.end() )
    {
      vit->set_meshing_info(find_result->second);
    }
    else
    {
      CGAL_assertion(false);
      vit->set_meshing_info(FT(0));
    }
  }
}  

template <typename Tr, bool B>
typename Mesh_sizing_field<Tr,B>::FT
Mesh_sizing_field<Tr,B>::
operator()(const Point_3& p, const Cell_handle& c) const  
{  
  const Cell_handle cell = tr_.locate(p,c);
  last_cell_ = cell;
  
  if ( !tr_.is_infinite(cell) )
    return interpolate_on_cell_vertices(p,cell);
  else
    return interpolate_on_facet_vertices(p,cell);
}


template <typename Tr, bool B>
typename Mesh_sizing_field<Tr,B>::FT
Mesh_sizing_field<Tr,B>::
operator()(const Point_3&, const std::pair<Cell_handle,bool>& c) const
{
  // Assumes that p is the centroid of c
  const Cell_handle& cell = c.first;
  
  // Interpolate value using tet vertices values
  const FT& va = cell->vertex(0)->meshing_info();
  const FT& vb = cell->vertex(1)->meshing_info();
  const FT& vc = cell->vertex(2)->meshing_info();
  const FT& vd = cell->vertex(3)->meshing_info();
  
  return ( (va+vb+vc+vd)/4 );
}

  
template <typename Tr, bool B>
typename Mesh_sizing_field<Tr,B>::FT
Mesh_sizing_field<Tr,B>::
interpolate_on_cell_vertices(const Point_3& p, const Cell_handle& cell) const
{
  typename Gt::Compute_volume_3 volume =
    Gt().compute_volume_3_object();
  
  // Interpolate value using tet vertices values
  const FT& va = cell->vertex(0)->meshing_info();
  const FT& vb = cell->vertex(1)->meshing_info();
  const FT& vc = cell->vertex(2)->meshing_info();
  const FT& vd = cell->vertex(3)->meshing_info();
  
  const Point_3& a = cell->vertex(0)->point();
  const Point_3& b = cell->vertex(1)->point();
  const Point_3& c = cell->vertex(2)->point();
  const Point_3& d = cell->vertex(3)->point();
  
  const FT abcp = CGAL::abs(volume(a,b,c,p));
  const FT abdp = CGAL::abs(volume(a,d,b,p));
  const FT acdp = CGAL::abs(volume(a,c,d,p));
  const FT bcdp = CGAL::abs(volume(b,d,c,p));
  
  // If volume is 0, then compute the average value
  if ( is_zero(abcp+abdp+acdp+bcdp) )
    return (va+vb+vc+vd)/4.;
  
  return ( (abcp*vd + abdp*vc + acdp*vb + bcdp*va) / (abcp+abdp+acdp+bcdp) );
}
  
  
  
template <typename Tr, bool B>
typename Mesh_sizing_field<Tr,B>::FT
Mesh_sizing_field<Tr,B>::
interpolate_on_facet_vertices(const Point_3& p, const Cell_handle& cell) const
{
  typename Gt::Compute_area_3 area =
    Gt().compute_area_3_object();
  
  // Find infinite vertex and put it in k0
  int k0 = 0;
  int k1 = 1;
  int k2 = 2;
  int k3 = 3;
  
  if ( tr_.is_infinite(cell->vertex(1)) )
    std::swap(k0,k1);
  if ( tr_.is_infinite(cell->vertex(2)) )
    std::swap(k0,k2);
  if ( tr_.is_infinite(cell->vertex(3)) )
    std::swap(k0,k3);
  
  // Interpolate value using tet vertices values
  const FT& va = cell->vertex(k1)->meshing_info();
  const FT& vb = cell->vertex(k2)->meshing_info();
  const FT& vc = cell->vertex(k3)->meshing_info();
  
  const Point_3& a = cell->vertex(k1)->point();
  const Point_3& b = cell->vertex(k2)->point();
  const Point_3& c = cell->vertex(k3)->point();
  
  const FT abp = area(a,b,p);
  const FT acp = area(a,c,p);
  const FT bcp = area(b,c,p);
  
  CGAL_assertion(abp >= 0);
  CGAL_assertion(acp >= 0);
  CGAL_assertion(bcp >= 0);
  
  // If area is 0, then compute the average value
  if ( is_zero(abp+acp+bcp) )
    return (va+vb+vc)/3.;
  
  return ( (abp*vc + acp*vb + bcp*va ) / (abp+acp+bcp) );
}
  
} // end namespace Mesh_3


} //namespace CGAL

#endif // CGAL_MESH_3_MESH_SIZING_FIELD_H
