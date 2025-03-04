// Copyright (c) 2003-2004  INRIA Sophia-Antipolis (France).
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Mesh_2/include/CGAL/Filter_circulator.h $
// $Id: Filter_circulator.h 56230 2010-05-14 09:13:45Z afabri $
// 
//
// Author(s)     : Laurent RINEAU

#ifndef CGAL_FILTRED_CIRCULATOR_H
#define CGAL_FILTRED_CIRCULATOR_H

namespace CGAL {

template <class Circ, class Pred>
class Filter_circulator : public Circ
{
  bool is_null;
  Pred test;

public:
  typedef Filter_circulator<Circ,Pred> Self;


  Filter_circulator(const Pred p=Pred()): is_null(true), test(p) {}

  Filter_circulator(const Self& c): Circ(c), is_null(c.is_null),
    test(c.test) {}

  Self& operator=(const Self& c)
    {
      //this->Circ::operator=(c); // This does not work with bcc
      //*this = c;  // This does not work with VC++6
      static_cast<Circ&>(*this) = static_cast<const Circ&>(c);
      is_null=c.is_null;
      test=c.test;
      return *this;
    }

  Filter_circulator(const Circ& c, const Pred& p=Pred())
    : Circ(c), is_null(false), test(p)
    {
      if(test(static_cast<Circ&>(*this)))
	is_null=false;
      else
	{
	  Self end(*this);
	  do { 
	    this->Circ::operator++();
	  } while( !test(static_cast<Circ&>(*this)) && (*this)!=end );
	  if((*this)==end)
	    is_null=true;
	}
    }

  bool operator==( Nullptr_t ) const {
    return is_null;
  }

  bool operator!=( Nullptr_t ) const {
    return !is_null;
  }

  bool operator==(const Self& c) const 
    {
      return is_null==c.is_null && this->Circ::operator==(c);
    }

  bool operator!=( const Self& c) const { return !(*this == c); }

  Self& operator++() {
    CGAL_assertion(!is_null);
    do {
      this->Circ::operator++();
    } while( !test(static_cast<Circ&>(*this)) );
    return *this;
  }

  Self  operator++(int) {
    Self tmp= *this;
    ++*this;
    return tmp;
  }
};

}

#endif
