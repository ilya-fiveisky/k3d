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

#include <k3dsdk/inode.h>
#include <k3dsdk/module.h>
#include <k3dsdk/nodes/functional/single.h>
#include <k3dsdk/nodes/property.h>
#include <k3dsdk/uuid.h>

using namespace std;
using namespace k3d;
using namespace k3d::nodes;
using namespace k3d::nodes::functional;

namespace module
{ 
namespace node
{
    
string category_node = "Node";

namespace equality
{
struct the_node_info { string name = "NodeEquality"; 
    string description = "Compares two nodes by reference.";
    uuid id = uuid(0xec0c8694, 0xf1a0440c, 0xbf5ad042, 0x8fd2eee6); string category = category_node;};

struct input1_info { string name = "a"; string label = "A"; string description = "A"; 
    inode* default_value = nullptr;};
struct input2_info { string name = "b"; string label = "B"; string description = "B"; 
    inode* default_value = nullptr;};

struct output_info { string name = "a_equals_b"; string label = "A = B"; string description = "A = B"; 
    bool_t default_value = false;};

typedef single<the_node_info, equal_to<inode*>, output_property<bool_t, output_info>, 
        input_property<inode*, input1_info>, input_property<inode*, input2_info>> type;
}

} // namespace node
} // namespace module

K3D_MODULE_START(Registry)
    Registry.register_factory(module::node::equality::type::get_factory());
K3D_MODULE_END

