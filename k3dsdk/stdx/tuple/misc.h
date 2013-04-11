#ifndef STDX_MISC_H
#define STDX_MISC_H

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

#include <tuple>

namespace stdx {

/// Used to pass U instance in variadic expression submitting unpacked parameters into T parameter.
/// Necessary for initializing tuple of types with shared owner and without copy constructor.
/// See m_inputs initialization in the k3d::function_nodes::function_node as example.
template<typename T, typename U> U& variadic_id(U& x){return x;}

} // namespace stdx

#endif // !STDX_MISC_H