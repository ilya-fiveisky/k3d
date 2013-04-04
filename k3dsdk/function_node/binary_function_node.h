#ifndef K3DSDK_FUNCTION_NODE_BINARY_FUNCTION_NODE_H
#define K3DSDK_FUNCTION_NODE_BINARY_FUNCTION_NODE_H

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

#include <k3d-i18n-config.h>
#include <k3dsdk/document_plugin_factory.h>
#include <k3dsdk/data.h>
#include <k3dsdk/uuid.h>
#include <k3dsdk/value_demand_storage.h>
#include <k3dsdk/node.h>
#include <k3dsdk/function_node/node_info.h>
#include <k3dsdk/function_node/property_info.h>
#include <k3dsdk/function_node/property.h>

#include <type_traits>

namespace k3d
{

namespace function_node
{

/// Binary function template.
template<
        node_info& NodeInfo, 
        typename input1_property_t,
        typename input2_property_t,
        typename output_property_t,
        typename function_t> 
class binary_function_node :
	public node
{
    static_assert(std::is_default_constructible<function_t>::value, "Function type should be default constructible");
    typedef binary_function_node<NodeInfo, input1_property_t, input2_property_t, output_property_t, function_t> this_t;
	typedef node base;
public:
	binary_function_node(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document),
		m_input1(*this),
        m_input2(*this),
        m_output(*this),
        m_function(function_t())
	{
            m_input1.changed_signal().connect(m_output.make_slot());
            m_input2.changed_signal().connect(m_output.make_slot());
            m_output.set_update_slot(sigc::mem_fun(*this, &this_t::execute));
	}
    
	static iplugin_factory& get_factory()
	{
		static document_plugin_factory<binary_function_node > factory(
			NodeInfo.id(),
			NodeInfo.name(),
			_(NodeInfo.description()),
			NodeInfo.category(),
			iplugin_factory::EXPERIMENTAL);

		return factory;
	}

private:
    void execute(const std::vector<ihint*>& Hints, typename output_property_t::value_type& Output)
    {
        Output = m_function(m_input1.pipeline_value(), m_input2.pipeline_value());
    }

    input1_property_t m_input1;
    input2_property_t m_input2;
    output_property_t m_output;
    function_t m_function;
};

} //namespace function_node

} // namespace k3d

#endif // !K3DSDK_FUNCTION_NODE_BINARY_FUNCTION_NODE_H

