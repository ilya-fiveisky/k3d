#ifndef K3DSDK_NODES_FUNCTIONAL_SINGLE_H
#define K3DSDK_NODES_FUNCTIONAL_SINGLE_H

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
#include <k3dsdk/nodes/functional/multi.h>

namespace k3d
{
namespace nodes
{
namespace functional
{

template<
        class node_info_t,
        typename function_t,
        typename output_property_t,
        typename... input_property_ts> 
using single_base = multi<node_info_t, 
        parameter_pack<output_pair<function_t, output_property_t>>, 
        parameter_pack<input_property_ts...>>;

template<
        class node_info_t,
        typename function_t,
        typename output_property_t,
        typename... input_property_ts> 
class single : 
    public single_base<node_info_t, function_t, output_property_t, input_property_ts...>
{
    typedef single_base<node_info_t, function_t, output_property_t, input_property_ts...> base;
public:
    single(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document) {}
        
    output_property_t& output_property() {return std::get<0>(base::m_outputs.params()).output_property();}
};

} // namespace functional
} // namespace nodes
} // namespace k3d

#endif // !K3DSDK_NODES_FUNCTIONAL_SINGLE_H

