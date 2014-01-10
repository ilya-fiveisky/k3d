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
#include <string>

#include <k3dsdk/geometric_operations.h>
#include <k3dsdk/line3.h>
#include <k3dsdk/module.h>
#include <k3dsdk/nodes/functional/single.h>
#include <k3dsdk/nodes/property.h>
#include <k3dsdk/plane.h>
#include <k3dsdk/point3.h>
#include <k3dsdk/uuid.h>
#include <k3dsdk/vector3.h>
#include <k3dsdk/vectors.h>

using namespace std;
using namespace k3d;
using namespace k3d::nodes;
using namespace k3d::nodes::functional;

namespace module
{ 
namespace geometric_operations
{
    
string category_geom = "GeometricOperation";

namespace vector_subtraction
{
struct the_node_info { string name = "VectorSubtraction"; 
    string description = "Subtracts two given vectors";
    uuid id = uuid(0x835bb1af, 0x95a04399, 0x856afa74, 0x92a2bda4); string category = category_geom;};

struct input1_info { string name = "a"; string label = "A"; string description = "A"; 
    vector3 default_value = vector3();};
struct input2_info { string name = "b"; string label = "B"; string description = "B"; 
    vector3 default_value = vector3();};

struct output_info { string name = "a_minus_b"; string label = "A - B"; string description = "A - B"; 
    vector3 default_value = vector3();};

typedef single<the_node_info, minus<vector3>, output_property<vector3, output_info>, 
        input_property<vector3, input1_info>, input_property<vector3, input2_info>> type;
}

namespace point_subtraction
{
struct the_node_info { string name = "PointSubtraction"; 
    string description = "Subtracts two given points";
    uuid id = uuid(0xa1075e01, 0x157a4e44, 0x9ecbc310, 0xf5895647); string category = category_geom;};

struct input1_info { string name = "a"; string label = "A"; string description = "A"; 
    point3 default_value = point3();};
struct input2_info { string name = "b"; string label = "B"; string description = "B"; 
    point3 default_value = point3();};

struct output_info { string name = "a_minus_b"; string label = "A - B"; string description = "A - B"; 
    vector3 default_value = vector3();};

struct subtract_points { vector3 operator()(const point3& A, const point3& B) const
    {return A - B;} };
    
typedef single<the_node_info, subtract_points, output_property<vector3, output_info>, 
        input_property<point3, input1_info>, input_property<point3, input2_info>> type;
}

namespace plane_creation
{
struct the_node_info { string name = "PlaneCreation"; 
    string description = "Creates plane from given normal and point";
    uuid id = uuid(0xccc116ac, 0x3a0f4a83, 0x86eddda5, 0xc5f7a872); string category = category_geom;};

struct normal_info { string name = "normal"; string label = "Normal"; 
    string description = "Plane normal"; vector3 default_value = vector3();};
struct point_info { string name = "point"; string label = "Point"; 
    string description = "Point that belongs to plane"; point3 default_value = point3();};

struct output_info { string name = "plane"; string label = "Plane"; string description = "Plane"; 
    plane default_value = plane();};

struct create_plane { plane operator()(const vector3& Normal, const point3& Point) const 
    {return plane(Normal, Point);}};
    
typedef single<the_node_info, create_plane, output_property<plane, output_info>, 
        input_property<vector3, normal_info>, input_property<point3, point_info>> type;
}

namespace plane_line_intersection
{
struct the_node_info { string name = "PlaneLineIntersection"; 
    string description = "Finds intersection of given plane and line";
    uuid id = uuid(0x6121a41d, 0x1dad4c1b, 0x8774e8d7, 0xe896f944); string category = category_geom;};

struct plane_info { string name = "plane"; string label = "Plane"; 
    string description = "Plane"; plane default_value = plane();};
struct line_info { string name = "line"; string label = "Line"; 
    string description = "Line"; line3 default_value = line3();};

struct output_info { string name = "intersection_point"; string label = "Intersection Point"; 
    string description = "Intersection Point"; point3 default_value = point3();};

struct get_intersection { 
    point3 operator()(const plane& Plane, const line3& Line) const
    {
        point3 Intersection;
        intersect(Plane, Line, Intersection);
        return Intersection;
    }
};

typedef single<the_node_info, get_intersection, output_property<point3, output_info>, 
        input_property<plane, plane_info>, input_property<line3, line_info>> type;
}

namespace point_to_vector
{
struct the_node_info { string name = "PointToVector"; 
    string description = "Converts 3d point to 3d vector";
    uuid id = uuid(0x88791f3a, 0xaa1942b1, 0x939e541b, 0xf58dd0ba); string category = category_geom;};

struct input_info { string name = "point"; string label = "Point"; string description = "Input Point"; 
    point3 default_value = point3();};

struct output_info { string name = "vector"; string label = "Vector"; string description = "Output Vector"; 
    vector3 default_value = vector3();};

struct point_to_vector { vector3 operator()(const point3& Point) const 
    {return vector3(Point[0], Point[1], Point[2]);}};
    
typedef single<the_node_info, point_to_vector, output_property<vector3, output_info>, 
        input_property<point3, input_info>> type;
}

namespace vector_to_point
{
struct the_node_info { string name = "VectorToPoint"; 
    string description = "Converts 3d vector to 3d point";
    uuid id = uuid(0x8a422a2a, 0x45a3430e, 0x80dda5ed, 0xde581fdf); string category = category_geom;};

struct input_info { string name = "vector"; string label = "Vector"; string description = "Input Vector"; 
    vector3 default_value = vector3();};

struct output_info { string name = "point"; string label = "Point"; string description = "Output Point"; 
    point3 default_value = point3();};

struct vector_to_point { point3 operator()(const vector3& Vector) const 
    {return point3(Vector[0], Vector[1], Vector[2]);}};
    
typedef single<the_node_info, vector_to_point, output_property<point3, output_info>, 
        input_property<vector3, input_info>> type;
}

} // namespace geometric_operations
} // namespace module

using namespace module::geometric_operations;

K3D_MODULE_START(Registry)
    Registry.register_factory(vector_subtraction::type::get_factory());
    Registry.register_factory(point_subtraction::type::get_factory());
    Registry.register_factory(plane_creation::type::get_factory());
    Registry.register_factory(plane_line_intersection::type::get_factory());
    Registry.register_factory(point_to_vector::type::get_factory());
    Registry.register_factory(vector_to_point::type::get_factory());
K3D_MODULE_END

