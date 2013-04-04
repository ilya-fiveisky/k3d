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

#include <k3dsdk/module.h>
#include <k3dsdk/function_node.h>
#include <k3dsdk/vector3.h>
#include <k3dsdk/point3.h>
#include <k3dsdk/plane.h>
#include <k3dsdk/line3.h>
#include <k3dsdk/uuid.h>
#include <k3dsdk/geometric_operations.h>

using namespace k3d;
using namespace k3d::function_node;

namespace module{ namespace geometric_operations
{
    
category_t category("GeometricOperation");

namespace subtraction
{
node_info the_node_info(name_t("Subtraction"), description_t("Subtracts two given vectors"), uuid(0x835bb1af, 0x95a04399, 0x856afa74, 0x92a2bda4), category);
property_info<vector3> input1_info(name_t("a"), label_t("A"), description_t("A"));
property_info<vector3> input2_info(name_t("b"), label_t("B"), description_t("B"));
property_info<vector3> output_info(name_t("a_minus_b"), label_t("A - B"), description_t("A - B"));
struct subtract { vector3 operator()(const vector3& a, const vector3& b) const {return a-b;}};
typedef binary_function_node<the_node_info, input_property<vector3, input1_info>, input_property<vector3, input2_info>, output_property<vector3, output_info>, subtract> type;
}

namespace create_plane
{
node_info the_node_info(name_t("PlaneCreation"), description_t("Creates plane from given normal and point"), uuid(0xccc116ac, 0x3a0f4a83, 0x86eddda5, 0xc5f7a872), category);
property_info<vector3> normal_info(name_t("normal"), label_t("Normal"), description_t("Plane normal"));
property_info<point3> point_info(name_t("point"), label_t("Point"), description_t("Point that belongs to plane"));
property_info<plane> output_info(name_t("plane"), label_t("Plane"), description_t("Plane"));
struct create_plane { plane operator()(const vector3& Normal, const point3& Point) const {return plane(Normal, Point);}};
typedef binary_function_node<the_node_info, input_property<vector3, normal_info>, input_property<point3, point_info>, output_property<plane, output_info>, create_plane> type;
}

namespace plane_line_intersection
{
node_info the_node_info(name_t("PlaneLineIntersection"), description_t("Finds intersection of given plane and line"), uuid(0x6121a41d, 0x1dad4c1b, 0x8774e8d7, 0xe896f944), category);
property_info<plane> plane_info(name_t("plane"), label_t("Plane"), description_t("Plane"));
property_info<line3> line_info(name_t("line"), label_t("Line"), description_t("Line"));
property_info<point3> output_info(name_t("intersectionPoint"), label_t("Intersection Point"), description_t("Intersection Point"));
struct get_intersection { 
    point3 operator()(const plane& Plane, const line3& Line) const
    {
        point3 Intersection;
        intersect(Plane, Line, Intersection);
        return Intersection;
    }
};
typedef binary_function_node<the_node_info, input_property<plane, plane_info>, input_property<line3, line_info>, output_property<point3, output_info>, get_intersection> type;
}

} // namespace geometric_operations
} // namespace module

K3D_MODULE_START(Registry)
    Registry.register_factory(module::geometric_operations::subtraction::type::get_factory());
    Registry.register_factory(module::geometric_operations::create_plane::type::get_factory());
    Registry.register_factory(module::geometric_operations::plane_line_intersection::type::get_factory());
K3D_MODULE_END

