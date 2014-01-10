#ifndef K3D_TESTS_UNIT_TESTS_UTILS_H
#define	K3D_TESTS_UNIT_TESTS_UTILS_H

// K-3D
// Copyright (c) 1995-2008, Timothy M. Shead
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

#include <string>

#include <k3dsdk/iproperty.h>
#include <k3dsdk/iwritable_property.h>
#include <k3dsdk/node.h>

namespace k3d
{
namespace tests
{

iproperty* get_property_by_name(node& Node, const std::string& Name);

iwritable_property* get_writable_property_by_name(node& Node, const std::string& Name);

} // namespace tests
} // namespace k3d

#endif // !K3D_TESTS_UNIT_TESTS_UTILS_H

