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
#include <k3dsdk/inode.h>
#include <k3dsdk/node.h>
#include <k3dsdk/data.h>
#include <k3dsdk/ihint.h>
#include <k3dsdk/point2.h>
#include <k3dsdk/inode_picker.h>

using namespace k3d;
using namespace k3d::data;

namespace module
{

namespace object_pickers
{

/// Picks node under cursor (or under any given coordinates)".
class node_picker :
	public node,
    public inode_picker_client
{
	typedef node base;
public:
	node_picker(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document),
		m_xy(init_owner(*this) + init_name("xy") + init_label(_("(X, Y)")) + init_description(_("X,Y coordinates")) + init_value(point2())),
        m_event(init_owner(*this) + init_name("event") + init_label(_("Event")) + init_description(_("Event on which to pick")) + init_value(false)),
        m_picked_node(init_owner(*this) + init_name("picked_node") + init_label(_("Picked Node")) + init_description(_("Picked node")) + init_value(static_cast<inode*>(NULL))),
        m_node_picker(NULL)
	{
            m_event.changed_signal().connect(sigc::mem_fun(*this, &node_picker::execute));
	}
        
    void set_node_picker(inode_picker* NodePicker)
    {
        m_node_picker = NodePicker;
    }
    
	static iplugin_factory& get_factory()
	{
		static document_plugin_factory<node_picker > factory(
			uuid(0x6b44be8e, 0x86614bc1, 0xb4106ff2, 0xbee66d4f),
			"NodePicker",
			_("Picks node under cursor (or under any given coordinates)"),
			"ObjectPickers",
			iplugin_factory::EXPERIMENTAL);

		return factory;
	}

private:
    void execute(ihint* const Hint)
    {
        if(m_event.pipeline_value())
        {
            m_picked_node.property_set_value(pick_node(m_xy.pipeline_value()), Hint);
        }
    }
    
    inode* pick_node(const point2& Point)
    {
        if(m_node_picker)
            return m_node_picker->pick_node(Point);
        else return NULL;
    }

    k3d_data(point2, immutable_name, change_signal, with_undo, local_storage, no_constraint, writable_property, with_serialization) m_xy;
    k3d_data(bool_t, immutable_name, change_signal, with_undo, local_storage, no_constraint, writable_property, with_serialization) m_event;
    k3d_data(inode*, immutable_name, change_signal, no_undo, node_storage, no_constraint, node_property, no_serialization) m_picked_node;
    
    inode_picker* m_node_picker;
};

iplugin_factory& node_picker_factory()
{
	return node_picker::get_factory();
}

} //namespace object_pickers

} // namespace module



