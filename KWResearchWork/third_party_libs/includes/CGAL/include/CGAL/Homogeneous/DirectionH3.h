// Copyright (c) 1999  Utrecht University (The Netherlands),
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Homogeneous_kernel/include/CGAL/Homogeneous/DirectionH3.h $
// $Id: DirectionH3.h 56667 2010-06-09 07:37:13Z sloriot $
// 
//
// Author(s)     : Stefan Schirra
 
#ifndef CGAL_HOMOGENEOUS_DIRECTION_3_H
#define CGAL_HOMOGENEOUS_DIRECTION_3_H

#include <CGAL/array.h>
#include <CGAL/Handle_for.h>

namespace CGAL {

template < class R_ >
class DirectionH3
{
   typedef typename R_::RT                   RT;
   typedef typename R_::FT                   FT;
   typedef typename R_::Point_3              Point_3;
   typedef typename R_::Vector_3             Vector_3;
   typedef typename R_::Segment_3            Segment_3;
   typedef typename R_::Line_3               Line_3;
   typedef typename R_::Ray_3                Ray_3;

    typedef cpp0x::array<RT, 4>              Rep;
    typedef typename R_::template Handle<Rep>::type  Base;
 
    Base base;

public:

    typedef R_                 R;

  DirectionH3() {}

  //DirectionH3(const Point_3 & p )
    //: base(p) {}

  DirectionH3(const Vector_3 & v )
  { *this = v.direction(); }

  DirectionH3(const Line_3 & l )
  { *this = l.rep().direction(); }

  DirectionH3(const Ray_3 & r )
  { *this = r.direction(); }

  DirectionH3(const Segment_3 & s )
  { *this = s.direction(); }

  // the fourth argument is not documented.  Should go away ?
  DirectionH3(const RT& x, const RT& y,
              const RT& z, const RT& w = RT(1) )
    : base( w >= RT(0) ? CGAL::make_array(x, y, z, w)
                       : CGAL::make_array<RT>(-x, -y, -z, -w) ) {}

  bool  is_degenerate() const;

  bool  operator==( const DirectionH3<R>& d) const;
  bool  operator!=( const DirectionH3<R>& d) const;

  Vector_3    to_vector() const;
  Vector_3    vector() const { return to_vector(); }

  const RT & dx() const { return get(base)[0]; }
  const RT & dy() const { return get(base)[1]; }
  const RT & dz() const { return get(base)[2]; }
  const RT & x()  const { return get(base)[0]; }
  const RT & y()  const { return get(base)[1]; }
  const RT & z()  const { return get(base)[2]; }
  const RT & hx() const { return get(base)[0]; }
  const RT & hy() const { return get(base)[1]; }
  const RT & hz() const { return get(base)[2]; }
};

template <class R >
CGAL_KERNEL_INLINE
bool
DirectionH3<R>::operator==( const DirectionH3<R>& d) const
{
  return ( ( hx()*d.hy() == hy()*d.hx() )
        &&( hx()*d.hz() == hz()*d.hx() )
        &&( hy()*d.hz() == hz()*d.hy() )
        &&( CGAL_NTS sign( hx() ) == CGAL_NTS sign( d.hx() ) )
        &&( CGAL_NTS sign( hy() ) == CGAL_NTS sign( d.hy() ) )
        &&( CGAL_NTS sign( hz() ) == CGAL_NTS sign( d.hz() ) ) );
}

template <class R >
inline
bool
DirectionH3<R>::operator!=( const DirectionH3<R>& d) const
{ return !operator==(d); }

template <class R >
CGAL_KERNEL_INLINE
bool
DirectionH3<R>::is_degenerate() const
{ return ((hx() == RT(0)) && (hy() == RT(0)) && (hz() == RT(0))); }

template <class R >
inline
typename DirectionH3<R>::Vector_3
DirectionH3<R>::to_vector() const
{ return Vector_3(dx(), dy(), dz(), RT(1)); }

template <class R>
CGAL_KERNEL_INLINE
DirectionH3<R>
cross_product( const DirectionH3<R>& d1,
               const DirectionH3<R>& d2)
{ return cross_product(d1.to_vector(),d2.to_vector()).direction(); }

} //namespace CGAL

#endif // CGAL_HOMOGENEOUS_DIRECTION_3_H
