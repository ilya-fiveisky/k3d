#ifndef STDX_HAS_RESULT_TYPE_H
#define STDX_HAS_RESULT_TYPE_H

// K-3D
// Copyright (c) 1995-2009, Timothy M. Shead
//
// Contact: tshead@k-3d.com
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/** \file
	\author Ilya Fiveisky (ilya.five@gmail.com)
*/

namespace stdx 
{
template <typename T>
class has_result_type {
    // Types "yes" and "no" are guaranteed to have different sizes,
    // specifically sizeof(yes) == 1 and sizeof(no) == 2.
    typedef char yes[1];
    typedef char no[2];
 
    template <typename C>
    static yes& test(typename C::result_type*);
 
    template <typename>
    static no& test(...);
 
public:
    // If the "sizeof" the result of calling test<T>(0) would be equal to the sizeof(yes),
    // the first overload worked and T has a nested type named result_type.
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes);
};

} // namespace stdx

#endif // !STDX_HAS_RESULT_TYPE_H