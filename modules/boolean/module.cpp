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
#include <k3dsdk/module.h>
#include <k3dsdk/uuid.h>

using namespace std;
using namespace k3d;
using namespace k3d::function_nodes;

namespace module
{ 
namespace boolean
{
    
category_t category("Boolean");

namespace conjunction
{
node_info the_node_info(name_t("And"), description_t("Logical and."), 
        uuid(0x28934d5d, 0xcefc4a12, 0xa307303d, 0x6987b78e), category);
property_info<bool_t> input1_info(name_t("a"), label_t("A"), description_t("A"));
property_info<bool_t> input2_info(name_t("b"), label_t("B"), description_t("B"));
property_info<bool_t> output_info(name_t("a_and_b"), label_t("A & B"), description_t("A & B"));
typedef function_node<the_node_info, logical_and<bool_t>, output_property<bool_t, output_info>, 
        input_property<bool_t, input1_info>, input_property<bool_t, input2_info>> type;
}

namespace disjunction
{
node_info the_node_info(name_t("Or"), description_t("Logical or."), 
        uuid(0xbf247478, 0x90ee4093, 0xbb316705, 0xa2416a05), category);
property_info<bool_t> input1_info(name_t("a"), label_t("A"), description_t("A"));
property_info<bool_t> input2_info(name_t("b"), label_t("B"), description_t("B"));
property_info<bool_t> output_info(name_t("a_or_b"), label_t("A V B"), description_t("A V B"));
typedef function_node<the_node_info, logical_or<bool_t>, output_property<bool_t, output_info>, 
        input_property<bool_t, input1_info>, input_property<bool_t, input2_info>> type;
}

namespace negation
{
node_info the_node_info(name_t("Not"), description_t("Logical not."), 
        uuid(0x7900a1cc, 0x1d1b44e0, 0xa83f0bbe, 0xd3d187dd), category);
property_info<bool_t> input_info(name_t("a"), label_t("A"), description_t("A"));
property_info<bool_t> output_info(name_t("not_a"), label_t("~A"), description_t("~A"));
typedef function_node<the_node_info, logical_not<bool_t>, output_property<bool_t, output_info>, 
        input_property<bool_t, input_info>> type;
}

} // namespace boolean
} // namespace module

K3D_MODULE_START(Registry)
    Registry.register_factory(module::boolean::conjunction::type::get_factory());
    Registry.register_factory(module::boolean::disjunction::type::get_factory());
    Registry.register_factory(module::boolean::negation::type::get_factory());
K3D_MODULE_END

