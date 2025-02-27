// Copyright (c) 2005  Stanford University (USA).
// All rights reserved.
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
// $URL: svn+ssh://scm.gforge.inria.fr/svn/cgal/trunk/Kinetic_data_structures/include/CGAL/Polynomial/internal/nt_converters.h $
// $Id: nt_converters.h 56668 2010-06-09 08:45:58Z sloriot $
// 
//
// Author(s)     : Daniel Russel <drussel@alumni.princeton.edu>

#ifndef CGAL_POLYNOMIAL_NT_CONVERTERS_H
#define CGAL_POLYNOMIAL_NT_CONVERTERS_H

#include <CGAL/Polynomial/basic.h>

#ifdef CGAL_POLYNOMIAL_USE_CGAL
#include <CGAL/NT_converter.h>
#include <CGAL/number_utils_classes.h>

namespace CGAL { namespace POLYNOMIAL {

template <class NT1, class NT2>
class NT_converter: public CGAL::NT_converter<NT1, NT2>
{
    public:
        NT_converter(){}
};

template <class NT>
class To_double: public CGAL::To_double<NT>
{
    public:
        To_double(){}
};

/*template <class NT>
double to_double(const NT &nt) {
  return CGAL::to_double(nt);
  }*/

} } //namespace CGAL::POLYNOMIAL

#else

Not implemented yet;
#endif

namespace CGAL { namespace POLYNOMIAL {

//! This does not use any CGAL code.
template <class NT>
struct Identity_converter
{
    typedef NT argument_type;
    typedef NT result_type;
    Identity_converter(){}
    const NT &operator()(const NT &nt) const
    {
        return nt;
    }
};

} } //namespace CGAL::POLYNOMIAL
#endif
