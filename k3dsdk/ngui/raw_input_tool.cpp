// K-3D
// Copyright (c) 1995-2006, Timothy M. Shead
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

#include <k3dsdk/ngui/basic_viewport_input_model.h>
#include <k3dsdk/ngui/document_state.h>
#include <k3dsdk/ngui/navigation_input_model.h>
#include <k3dsdk/ngui/raw_input_tool.h>
#include <k3dsdk/data.h>
#include <k3dsdk/property_collection.h>
#include <k3dsdk/imouse_observer.h>
#include <k3dsdk/inode_picker.h>
#include <k3dsdk/ixy_to_3d_line.h>
#include <k3d-i18n-config.h>

#include <boost/lambda/if.hpp>
#include <boost/lambda/casts.hpp>
#include <boost/lambda/bind.hpp>

#include <set>

#include "viewport.h"

using namespace std;
using namespace boost::lambda;
using namespace k3d;
using namespace k3d::input_devices;
        
namespace k3d
{

namespace ngui
{

/////////////////////////////////////////////////////////////////////////////
// raw_input_tool::implementation

class raw_input_tool::implementation :
	public k3d::property_collection,
    public k3d::inode_picker,
    public k3d::ixy_to_3d_line
{
public:
	implementation(document_state& DocumentState) :
		m_document_state(DocumentState),
		m_navigation_model(DocumentState)
	{
        m_document_state.document().nodes().add_nodes_signal().connect(sigc::mem_fun(*this, &raw_input_tool::implementation::on_nodes_added));
        m_document_state.document().nodes().remove_nodes_signal().connect(sigc::mem_fun(*this, &raw_input_tool::implementation::on_nodes_removed));
        
        m_input_model.connect_mouse_move(sigc::mem_fun(*this, &raw_input_tool::implementation::on_mouse_move));
        m_input_model.connect_lbutton_click(sigc::mem_fun(*this, &raw_input_tool::implementation::on_lbutton_click));
        m_input_model.connect_lbutton_start_drag(sigc::mem_fun(*this, &raw_input_tool::implementation::on_lbutton_start_drag));
        m_input_model.connect_lbutton_drag(sigc::mem_fun(*this, &raw_input_tool::implementation::on_lbutton_drag));
        m_input_model.connect_lbutton_end_drag(sigc::mem_fun(*this, &raw_input_tool::implementation::on_lbutton_end_drag));
        
		m_input_model.connect_mbutton_click(sigc::mem_fun(m_navigation_model, &navigation_input_model::on_button1_click));
		m_input_model.connect_mbutton_start_drag(sigc::mem_fun(m_navigation_model, &navigation_input_model::on_button1_start_drag));
		m_input_model.connect_mbutton_drag(sigc::mem_fun(m_navigation_model, &navigation_input_model::on_button1_drag));
		m_input_model.connect_mbutton_end_drag(sigc::mem_fun(m_navigation_model, &navigation_input_model::on_button1_end_drag));
		m_input_model.connect_rbutton_click(sigc::mem_fun(m_navigation_model, &navigation_input_model::on_button2_click));
		m_input_model.connect_rbutton_start_drag(sigc::mem_fun(m_navigation_model, &navigation_input_model::on_button2_start_drag));
		m_input_model.connect_rbutton_drag(sigc::mem_fun(m_navigation_model, &navigation_input_model::on_button2_drag));
		m_input_model.connect_rbutton_end_drag(sigc::mem_fun(m_navigation_model, &navigation_input_model::on_button2_end_drag));
		m_input_model.connect_scroll(sigc::mem_fun(m_navigation_model, &navigation_input_model::on_scroll));
        
        connect_observer_nodes();
	}
        
    inode* pick_node(const k3d::point2& Point)
    {
        viewport::control* viewport = m_document_state.get_focus_viewport();
        k3d::selection::record record = viewport->pick_node(Point);
        return k3d::selection::get_node(record);
    }
    
    line3 convert(const k3d::point2& Point)
    {
        return mouse_to_world(*m_document_state.get_focus_viewport(), Point);
    }
        
    void connect_observer_nodes()
    {
        on_nodes_added(m_document_state.document().nodes().collection());
    }

	k3d::idocument& document()
	{
		return m_document_state.document();
	}
    
    void on_mouse_move(viewport::control& v, const GdkEventMotion& e)
    {
        for(imouse_observer* mouseObserver: m_mouse_observer_nodes)
        {
            mouseObserver->mouse_move(e.x, e.y);
        }
    }
    
    void on_lbutton_click(viewport::control& v, const GdkEventButton& e)
    {
        for(imouse_observer* mouseObserver: m_mouse_observer_nodes)
        {
            mouseObserver->lbutton_click();
        }
    }
    
    void on_lbutton_start_drag(viewport::control& v, const GdkEventMotion& e)
    {
        for(imouse_observer* mouseObserver: m_mouse_observer_nodes)
        {
            mouseObserver->lbutton_start_drag();
        }
    }
    
    void on_lbutton_drag(viewport::control& v, const GdkEventMotion& e)
    {
        for(imouse_observer* mouseObserver: m_mouse_observer_nodes)
        {
            mouseObserver->lbutton_drag();
        }
    }
    
    void on_lbutton_end_drag(viewport::control& v, const GdkEventButton& e)
    {
        for(imouse_observer* mouseObserver: m_mouse_observer_nodes)
        {
            mouseObserver->lbutton_end_drag();
        }
    }
  
    typedef set<imouse_observer*> mouse_observer_nodes_t;
    
    template<typename target_nodes_t, typename return_t> 
    void on_nodes(const inode_collection::nodes_t& Nodes, target_nodes_t& TargetNodes,
        return_t (mouse_observer_nodes_t::*f)(const mouse_observer_nodes_t::value_type&))
    {
        target_nodes_t temp = target_nodes_t(TargetNodes);
        for(inode* node: Nodes)
        {
            if(imouse_observer* mouseObserver = dynamic_cast<imouse_observer*>(node))
            {
                (temp.*f)(mouseObserver);
            }
        }
        TargetNodes = temp;
    }
    
    void on_nodes_added(const inode_collection::nodes_t& Nodes)
    {
        on_nodes<mouse_observer_nodes_t, pair<mouse_observer_nodes_t::iterator, bool> >(Nodes,
                m_mouse_observer_nodes, &mouse_observer_nodes_t::insert);
        
        for(inode* node: Nodes)
        {
            if(inode_picker_client* nodePickerClient = dynamic_cast<inode_picker_client*>(node))
            {
                nodePickerClient->set_node_picker(this);
            }
            if(ixy_to_3d_line_client* xyTo3dLineClient = dynamic_cast<ixy_to_3d_line_client*>(node))
            {
                xyTo3dLineClient->set_xy_to_3d_line(this);
            }
        }
    }
    
    void on_nodes_removed(const inode_collection::nodes_t& Nodes)
    {
        on_nodes<mouse_observer_nodes_t, mouse_observer_nodes_t::size_type>(Nodes, 
                m_mouse_observer_nodes, &mouse_observer_nodes_t::erase);
    }

	document_state& m_document_state;
	/// Provides interactive navigation behavior
	navigation_input_model m_navigation_model;
	/// Dispatches incoming user input events
	basic_viewport_input_model m_input_model;
    
    mouse_observer_nodes_t m_mouse_observer_nodes;
};

/////////////////////////////////////////////////////////////////////////////
// raw_input_tool

raw_input_tool::raw_input_tool(document_state& DocumentState, const std::string& Name) :
	base(DocumentState, Name),
	m_implementation(new implementation(DocumentState))
{
}

raw_input_tool::~raw_input_tool()
{
	delete m_implementation;
}

void raw_input_tool::on_activate()
{

}

void raw_input_tool::on_deactivate()
{

}

k3d::iproperty_collection* raw_input_tool::get_property_collection()
{
	return m_implementation;
}

viewport_input_model& raw_input_tool::get_input_model()
{
	return m_implementation->m_input_model;
}

} // namespace ngui

} // namespace k3d

