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
#include <k3dsdk/node.h>
#include <k3dsdk/value_demand_storage.h>
#include <k3dsdk/point2.h>
#include <k3dsdk/imouse_observer.h>
#include <k3dsdk/function_node.h>

#include <boost/date_time/posix_time/posix_time.hpp>

#include <functional>

using namespace k3d;
using namespace k3d::function_node;
using namespace boost;
using namespace boost::posix_time;
using namespace std;

namespace module
{

namespace input_devices
{

/// If condition holds return fist input, otherwise second
class mouse_source :
	public node,
        public k3d::input_devices::imouse_observer
{
	typedef node base;
public:
	mouse_source(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document),
        m_xy_(point2()),
		m_xy(init_owner(*this) + init_name("xy") + init_label(_("(X, Y)")) + init_description(_("Mouse pointer coordinates")) + init_value(point2())),
        m_lbutton_click_time(0.0),
		m_lbutton_click(init_owner(*this) + init_name("lbutton_click") + init_label(_("Left Button Click")) + init_description(_("Left button click event")) + init_value(false)),
        m_lbutton_start_drag_time(0.0),
		m_lbutton_start_drag(init_owner(*this) + init_name("lbutton_start_drag") + init_label(_("Left Button Start Drag")) + init_description(_("Left button start drag event")) + init_value(false)),
        m_lbutton_drag_(false),
        m_lbutton_drag(init_owner(*this) + init_name("lbutton_drag") + init_label(_("Left Button Drag")) + init_description(_("Left button drag event")) + init_value(false)),
        m_lbutton_end_drag_time(0.0),
		m_lbutton_end_drag(init_owner(*this) + init_name("lbutton_end_drag") + init_label(_("Left Button End Drag")) + init_description(_("Left button end drag event")) + init_value(false))
        
	{
        m_xy.set_update_slot(make_update_value_slot(m_xy_));
        m_lbutton_click.set_update_slot(make_update_event_slot(m_lbutton_click_time));
        m_lbutton_start_drag.set_update_slot(make_update_event_slot(m_lbutton_start_drag_time));
        m_lbutton_drag.set_update_slot(make_update_value_slot(m_lbutton_drag_));
        m_lbutton_start_drag.set_update_slot(make_update_event_slot(m_lbutton_end_drag_time));
	}

	static iplugin_factory& get_factory()
	{
		static document_plugin_factory<mouse_source > factory(
			uuid(0x919ec483, 0x26e84975, 0xb8f58639, 0x20675873),
			"MouseSource",
			_("Provides mouse events for a K-3D document"),
			"InputDevices",
			iplugin_factory::EXPERIMENTAL);

		return factory;
	}
    
    void mouse_move(double_t x, double_t y)
    {
        m_xy_ = point2(x, y);
        m_xy.update();
    }
	
	void lbutton_down(){}
	void lbutton_up(){}
    
	void lbutton_click()
    {
        m_lbutton_click_time = get_current_time();
        m_lbutton_click.update();
    }
    
	void lbutton_double_click(){}
	void lbutton_triple_click(){}
    
	void lbutton_start_drag()
    {
        m_lbutton_start_drag_time = get_current_time();
        m_lbutton_drag_ = true;
        m_lbutton_start_drag.update();
        m_lbutton_drag.update();
    }
    
	void lbutton_drag(){}
    
	void lbutton_end_drag()
    {
        m_lbutton_end_drag_time = get_current_time();
        m_lbutton_drag_ = false;
        m_lbutton_drag.update();
        m_lbutton_end_drag.update();
    }

	void mbutton_down(){}
	void mbutton_up(){}
	void mbutton_click(){}
	void mbutton_double_click(){}
	void mbutton_triple_click(){}
	void mbutton_start_drag(){}
	void mbutton_drag(){}
	void mbutton_end_drag(){}

	void rbutton_down(){}
	void rbutton_up(){}
	void rbutton_click(){}
	void rbutton_double_click(){}
	void rbutton_triple_click(){}
	void rbutton_start_drag(){}
	void rbutton_drag(){}
	void rbutton_end_drag(){}

	void scroll(){}

private:
    point2 m_xy_;
	output_property_t<point2> m_xy;
    
    double_t m_lbutton_click_time;
	output_property_t<bool_t> m_lbutton_click;
    
    double_t m_lbutton_start_drag_time;
	output_property_t<bool_t> m_lbutton_start_drag;
    
    bool_t m_lbutton_drag_;
    output_property_t<bool_t> m_lbutton_drag;
    
    double_t m_lbutton_end_drag_time;
	output_property_t<bool_t> m_lbutton_end_drag;
    
    const double_t m_time_threshold = 0.01;
    
    double_t get_current_time()
    {
        const ptime epoch(gregorian::date(1970, 1, 1));
		const ptime current_time = microsec_clock::universal_time();
		const time_duration elapsed = current_time - epoch;

		double_t time = elapsed.total_seconds();
		time += static_cast<double_t>(elapsed.fractional_seconds()) 
                / static_cast<double_t>(elapsed.ticks_per_second());
        
        return time;
    }
    
    std::function<void(const vector<ihint*>&, bool_t&)> 
    make_update_event_slot(const double_t& EventTime)
    {
        return [this, &EventTime](const vector<ihint*>& Hint, bool_t& Event)
            {execute_event(EventTime, Hint, Event);};
    }
    
    template<typename value_t>
    function<void(const vector<ihint*>&, value_t&)> 
    make_update_value_slot(const value_t& ValueSource)
    {
        return [this, &ValueSource](const vector<ihint*>& Hint, value_t& Value)
            {execute_value(ValueSource, Hint, Value);};
    }
    
    /// Called whenever the output values have been modified and needs to be updated.
    template<typename value_t> 
    void execute_value(const value_t& ValueSource, const std::vector<ihint*>& Hints, value_t& Value)
	{
        Value = ValueSource;
    }
    
    /// Called whenever the output values have been modified and needs to be updated.
    void execute_event(const double_t& EventTime, const vector<ihint*>& Hints, bool_t& Event)
	{
        Event = get_current_time() - EventTime < m_time_threshold;
    }
};

iplugin_factory& mouse_source_factory()
{
	return mouse_source::get_factory();
}

} //namespace input_devices

} // namespace module



