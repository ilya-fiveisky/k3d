#ifndef MODULES_BOOLEAN_OPERATIONS_H
#define MODULES_BOOLEAN_OPERATIONS_H
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

#include <k3dsdk/module.h>
#include <k3dsdk/nodes/functional/single.h>
#include <k3dsdk/nodes/property.h>
#include <k3dsdk/uuid.h>

namespace module
{ 
namespace boolean
{
using namespace std;
using namespace k3d;
using namespace k3d::nodes;
using namespace k3d::nodes::functional;
    
string category_bool = "Boolean";

namespace conjunction
{
struct the_node_info { string name = "And"; string description = "Logical and.";
        uuid id = uuid(0x28934d5d, 0xcefc4a12, 0xa307303d, 0x6987b78e); string category = category_bool;};
        
struct input1_info { string name = "a"; string label = "A"; string description = "A"; bool_t default_value = false;};
struct input2_info { string name = "b"; string label = "B"; string description = "B"; bool_t default_value = false;};

struct output_info { string name = "a_and_b"; string label = "A & B"; string description = "A & B"; bool_t default_value = false;};

typedef single<the_node_info, logical_and<bool_t>, output_property<bool_t, output_info>, 
        input_property<bool_t, input1_info>, input_property<bool_t, input2_info>> type;
}

namespace disjunction
{
struct the_node_info { string name = "Or"; string description = "Logical or.";
        uuid id = uuid(0xbf247478, 0x90ee4093, 0xbb316705, 0xa2416a05); string category = category_bool;};
        
struct input1_info { string name = "a"; string label = "A"; string description = "A"; bool_t default_value = false;};
struct input2_info { string name = "b"; string label = "B"; string description = "B"; bool_t default_value = false;};

struct output_info { string name = "a_or_b"; string label = "A V B"; string description = "A V B"; bool_t default_value = false;};

typedef single<the_node_info, logical_or<bool_t>, output_property<bool_t, output_info>, 
        input_property<bool_t, input1_info>, input_property<bool_t, input2_info>> type;
}

namespace negation
{
struct the_node_info { string name = "Not"; string description = "Logical not.";
        uuid id = uuid(0x7900a1cc, 0x1d1b44e0, 0xa83f0bbe, 0xd3d187dd); string category = category_bool;};
        
struct input_info { string name = "a"; string label = "A"; string description = "A"; bool_t default_value = false;};

struct output_info { string name = "not_a"; string label = "~A"; string description = "~A"; bool_t default_value = false;};

typedef single<the_node_info, logical_not<bool_t>, output_property<bool_t, output_info>, 
        input_property<bool_t, input_info>> type;
}

} // namespace boolean
} // namespace module

#endif // !MODULES_BOOLEAN_OPERATIONS_H
