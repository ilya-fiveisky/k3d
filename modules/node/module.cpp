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
#include <k3dsdk/inode.h>
#include <k3dsdk/uuid.h>

using namespace std;
using namespace k3d;
using namespace k3d::function_nodes;

namespace module
{ 
namespace node
{
    
category_t category("Node");

namespace equality
{
node_info the_node_info(name_t("NodeEquality"), description_t("Compares two nodes by reference."), 
        uuid(0xec0c8694, 0xf1a0440c, 0xbf5ad042, 0x8fd2eee6), category);
property_info<inode*> input1_info(name_t("a"), label_t("A"), description_t("A"));
property_info<inode*> input2_info(name_t("b"), label_t("B"), description_t("B"));
property_info<bool_t> output_info(name_t("a_equals_b"), label_t("A = B"), description_t("A = B"));
typedef function_node<the_node_info, equal_to<inode*>, output_property<bool_t, output_info>, 
        input_property<inode*, input1_info>, input_property<inode*, input2_info>> type;
}

} // namespace node
} // namespace module

K3D_MODULE_START(Registry)
    Registry.register_factory(module::node::equality::type::get_factory());
K3D_MODULE_END

