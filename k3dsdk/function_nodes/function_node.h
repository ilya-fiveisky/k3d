#ifndef K3DSDK_FUNCTION_NODES_FUNCTION_NODE_H
#define K3DSDK_FUNCTION_NODES_FUNCTION_NODE_H

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

#include <k3dsdk/iplugin_factory.h>
#include <k3dsdk/function_nodes/multi_function_node.h>
#include <k3dsdk/function_nodes/node_info.h>

namespace k3d
{
namespace function_nodes
{

template<
        node_info& NodeInfo,
        typename function_t,
        typename output_property_t,
        typename... input_property_ts> 
using function_node_base = multi_function_node<NodeInfo, 
        parameter_pack<output_pair<function_t, output_property_t>>, 
        parameter_pack<input_property_ts...>>;

template<
        node_info& NodeInfo,
        typename function_t,
        typename output_property_t,
        typename... input_property_ts> 
class function_node : 
    public function_node_base<NodeInfo, function_t, output_property_t, input_property_ts...>
{
    typedef function_node_base<NodeInfo, function_t, output_property_t, input_property_ts...> base;
public:
    function_node(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document) {}
        
    output_property_t& output_property() {return std::get<0>(base::m_outputs.params()).output_property();}
};

} //namespace function_node

} // namespace k3d

#endif // !K3DSDK_FUNCTION_NODES_FUNCTION_NODE_H

