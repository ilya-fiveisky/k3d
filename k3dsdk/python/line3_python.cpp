// K-3D
// Copyright (c) 1995-2006, Timothy M. Shead
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

#include <k3dsdk/python/line3_python.h>

#include <boost/python.hpp>
#include <boost/python/detail/api_placeholder.hpp>

#include <k3dsdk/algebra.h>
#include <k3dsdk/line3.h>
#include <k3dsdk/point3.h>
#include <k3dsdk/python/utility_python.h>
#include <k3dsdk/vector3.h>

using namespace boost::python;
using namespace k3d;

namespace k3d
{

namespace python
{

void define_class_line3()
{
	class_<line3>("line3",
		"Encapsulates a 3D line")
        .def(init<vector3, point3>())
		.def(init<point3, point3>())
		.def(init<const line3&>())
		.def_readonly("direction", &line3::direction)
        .def_readonly("point", &line3::point)
		.def(self == self)
		.def(self != self)
		.def(self_ns::str(self));
}

} // namespace python

} // namespace k3d

