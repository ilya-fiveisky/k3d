#ifndef K3DSDK_NODES_MEMORIZATION_H
#define K3DSDK_NODES_MEMORIZATION_H

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

#include <type_traits>

#include <boost/concept/assert.hpp>
#include <boost/utility.hpp>

#include <k3d-i18n-config.h>
#include <k3dsdk/document_plugin_factory.h>
#include <k3dsdk/hints.h>
#include <k3dsdk/interface_list.h>
#include <k3dsdk/node.h>
#include <k3dsdk/nodes/NodeInfo.h>
#include <k3dsdk/nodes/property.h>
#include <k3dsdk/nodes/TypeInfo.h>

namespace k3d
{

/////////////////////////////////////////////////////////////////////////////
// memorization

template<
    class node_info_t, 
    typename value_t,
    class type_info_t,
    class interface_list = null_interface>
class memorization :
    private boost::base_from_member<type_info_t>,
	public node
{
    BOOST_CONCEPT_ASSERT((nodes::NodeInfo<node_info_t>));
    BOOST_CONCEPT_ASSERT((nodes::TypeInfo<type_info_t, value_t>));
    
    typedef boost::base_from_member<type_info_t>  tbase;
	typedef node base;

public:
	memorization(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document),
        m_input_value(this->tbase::member.default_value),
		m_input(init_owner(*this) + init_name("input") + init_label(_("Input")) + 
                init_description(_("Input")) + init_value(this->tbase::member.default_value)),
		m_event(init_owner(*this) + init_name("event") + init_label(_("Event")) + 
                init_description(_("Event on which to memorize")) + init_value(false)),
		m_output(init_owner(*this) + init_name("output") + init_label(_("Output")) + 
                init_description(_("Output (read only)")) + init_value(this->tbase::member.default_value))
	{
		m_event.changed_signal().connect(sigc::mem_fun(*this, &memorization::on_event));
		m_output.set_update_slot(sigc::mem_fun(*this, &memorization::execute));
	}

	static iplugin_factory& get_factory()
	{
        static node_info_t ni;
		static document_plugin_factory<memorization, interface_list> factory(
            ni.id,
            ni.name.c_str(),
            _(ni.description.c_str()),
            ni.category.c_str(),
            iplugin_factory::EXPERIMENTAL);

		return factory;
	}

protected:
	nodes::input_property_t<value_t> m_input;
	nodes::output_property_t<value_t> m_output;
    
private:
	nodes::input_property_t<bool_t> m_event;
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

#endif // !K3DSDK_NODES_MEMORIZATION_H