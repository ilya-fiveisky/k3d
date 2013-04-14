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

#include <functional>

#include <k3dsdk/function_nodes.h>
#include <k3dsdk/geometric_operations.h>
#include <k3dsdk/line3.h>
#include <k3dsdk/module.h>
#include <k3dsdk/plane.h>
#include <k3dsdk/point3.h>
#include <k3dsdk/uuid.h>
#include <k3dsdk/vector3.h>
#include <k3dsdk/vectors.h>

using namespace std;
using namespace k3d;
using namespace k3d::function_nodes;

namespace module
{ 
namespace geometric_operations
{
    
category_t category("GeometricOperation");

namespace vector_subtraction
{
node_info the_node_info(name_t("VectorSubtraction"), description_t("Subtracts two given vectors"), 
        uuid(0x835bb1af, 0x95a04399, 0x856afa74, 0x92a2bda4), category);
property_info<vector3> input1_info(name_t("a"), label_t("A"), description_t("A"));
property_info<vector3> input2_info(name_t("b"), label_t("B"), description_t("B"));
property_info<vector3> output_info(name_t("a_minus_b"), label_t("A - B"), description_t("A - B"));
typedef function_node<the_node_info, minus<vector3>, output_property<vector3, output_info>, 
        input_property<vector3, input1_info>, input_property<vector3, input2_info>> type;
}

namespace point_subtraction
{
node_info the_node_info(name_t("PointSubtraction"), description_t("Subtracts two given points"), 
        uuid(0xa1075e01, 0x157a4e44, 0x9ecbc310, 0xf5895647), category);
property_info<point3> input1_info(name_t("a"), label_t("A"), description_t("A"));
property_info<point3> input2_info(name_t("b"), label_t("B"), description_t("B"));
property_info<vector3> output_info(name_t("a_minus_b"), label_t("A - B"), description_t("A - B"));
struct subtract_points { vector3 operator()(const point3& A, const point3& B) const
    {return A - B;} };
typedef function_node<the_node_info, subtract_points, output_property<vector3, output_info>, 
        input_property<point3, input1_info>, input_property<point3, input2_info>> type;
}

namespace create_plane
{
node_info the_node_info(name_t("PlaneCreation"), 
        description_t("Creates plane from given normal and point"), 
        uuid(0xccc116ac, 0x3a0f4a83, 0x86eddda5, 0xc5f7a872), category);
property_info<vector3> normal_info(name_t("normal"), label_t("Normal"), description_t("Plane normal"));
property_info<point3> point_info(name_t("point"), label_t("Point"), 
        description_t("Point that belongs to plane"));
property_info<plane> output_info(name_t("plane"), label_t("Plane"), description_t("Plane"));
struct create_plane { plane operator()(const vector3& Normal, const point3& Point) const 
    {return plane(Normal, Point);}};
typedef function_node<the_node_info, create_plane, output_property<plane, output_info>, 
        input_property<vector3, normal_info>, input_property<point3, point_info>> type;
}

namespace plane_line_intersection
{
node_info the_node_info(name_t("PlaneLineIntersection"), 
        description_t("Finds intersection of given plane and line"), 
        uuid(0x6121a41d, 0x1dad4c1b, 0x8774e8d7, 0xe896f944), category);
property_info<plane> plane_info(name_t("plane"), label_t("Plane"), description_t("Plane"));
property_info<line3> line_info(name_t("line"), label_t("Line"), description_t("Line"));
property_info<point3> output_info(name_t("intersection_point"), label_t("Intersection Point"), 
        description_t("Intersection Point"));
struct get_intersection { 
    point3 operator()(const plane& Plane, const line3& Line) const
    {
        point3 Intersection;
        intersect(Plane, Line, Intersection);
        return Intersection;
    }
};
typedef function_node<the_node_info, get_intersection, output_property<point3, output_info>, 
        input_property<plane, plane_info>, input_property<line3, line_info>> type;
}

namespace point_to_vector
{
node_info the_node_info(name_t("PointToVector"), 
        description_t("Converts 3d point to 3d vector"), 
        uuid(0x88791f3a, 0xaa1942b1, 0x939e541b, 0xf58dd0ba), category);
property_info<point3> input_info(name_t("point"), label_t("Point"), description_t("Input Point"));
property_info<vector3> output_info(name_t("vector"), label_t("Vector"), description_t("Output Vector"));
struct point_to_vector { vector3 operator()(const point3& Point) const 
    {return vector3(Point[0], Point[1], Point[2]);}};
typedef function_node<the_node_info, point_to_vector, output_property<vector3, output_info>, 
        input_property<point3, input_info>> type;
}

namespace vector_to_point
{
node_info the_node_info(name_t("VectorToPoint"), 
        description_t("Converts 3d vector to 3d point"), 
        uuid(0x8a422a2a, 0x45a3430e, 0x80dda5ed, 0xde581fdf), category);
property_info<vector3> input_info(name_t("vector"), label_t("Vector"), description_t("Input Vector"));
property_info<point3> output_info(name_t("point"), label_t("Point"), description_t("Output Point"));
struct vector_to_point { point3 operator()(const vector3& Vector) const 
    {return point3(Vector[0], Vector[1], Vector[2]);}};
typedef function_node<the_node_info, vector_to_point, output_property<point3, output_info>, 
        input_property<vector3, input_info>> type;
}

} // namespace geometric_operations
} // namespace module

K3D_MODULE_START(Registry)
    Registry.register_factory(module::geometric_operations::vector_subtraction::type::get_factory());
    Registry.register_factory(module::geometric_operations::point_subtraction::type::get_factory());
    Registry.register_factory(module::geometric_operations::create_plane::type::get_factory());
    Registry.register_factory(module::geometric_operations::plane_line_intersection::type::get_factory());
    Registry.register_factory(module::geometric_operations::point_to_vector::type::get_factory());
    Registry.register_factory(module::geometric_operations::vector_to_point::type::get_factory());
K3D_MODULE_END

