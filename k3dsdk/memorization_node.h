#ifndef K3DSDK_MEMORIZATION_NODE_H
#define K3DSDK_MEMORIZATION_NODE_H

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
#include <k3dsdk/function_nodes.h>
#include <k3dsdk/hints.h>
#include <k3dsdk/interface_list.h>
#include <k3dsdk/node.h>

namespace k3d
{

/////////////////////////////////////////////////////////////////////////////
// memorization_node

template<
    function_nodes::node_info& Info, 
    typename value_t,
    function_nodes::type_info<value_t>& TypeInfo,
    class interface_list = null_interface>
class memorization_node :
	public node
{
	typedef node base;

public:
	memorization_node(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document),
        m_input_value(TypeInfo.default_value()),
		m_input(init_owner(*this) + init_name("input") + init_label(_("Input")) + 
                init_description(_("Input")) + init_value(TypeInfo.default_value())),
		m_event(init_owner(*this) + init_name("event") + init_label(_("Event")) + 
                init_description(_("Event on which to memorize")) + init_value(false)),
		m_output(init_owner(*this) + init_name("output") + init_label(_("Output")) + 
                init_description(_("Output (read only)")) + init_value(TypeInfo.default_value()))
	{
		m_event.changed_signal().connect(sigc::mem_fun(*this, &memorization_node::on_event));
		m_output.set_update_slot(sigc::mem_fun(*this, &memorization_node::execute));
	}

	static iplugin_factory& get_factory()
	{
		static document_plugin_factory<memorization_node, interface_list> factory(
				Info.id(),
				Info.name(),
				_("Memorizes input value on event"),
				Info.category(),
				iplugin_factory::EXPERIMENTAL);

		return factory;
	}

protected:
	function_nodes::input_property_t<value_t> m_input;
	function_nodes::output_property_t<value_t> m_output;
    
private:
	function_nodes::input_property_t<bool_t> m_event;
    value_t m_input_value;

	/// Called whenever the output matrix has been modified and needs to be updated.
	void execute(const std::vector<ihint*>& Hints, value_t& Input)
	{
		Input = m_input_value;
	}
    
    void on_event(ihint* Hints)
	{
        if(m_event.internal_value())
        {
            m_input_value = m_input.internal_value();
            m_output.update();
        }
	}

};

} // namespace k3d

#endif // !K3DSDK_MEMORIZATION_NODE_H