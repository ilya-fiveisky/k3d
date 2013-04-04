#ifndef K3DSDK_SINGLE_SOURCE_H
#define K3DSDK_SINGLE_SOURCE_H

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
	\author Timothy M. Shead (tshead@k-3d.com)
    \author Ilya Fiveisky (ilya.five@gmail.com)
*/

#include <k3d-i18n-config.h>
#include <k3dsdk/hints.h>
#include <k3dsdk/node.h>
#include <k3dsdk/function_node/property.h>

#include <boost/type_traits.hpp>

namespace k3d
{

/// Convenience base template for sources that produce a single output value
template<typename value_t> class single_source :
	public node
{
	typedef node base;
    typedef k3d::single_source<value_t> this_t;
public:
	single_source(iplugin_factory& Factory, idocument& Document, const char* const OutputDescription) :
        base(Factory, Document),
        m_output(init_owner(*this) + init_name("output") + init_label(_("Output")) + init_description(OutputDescription) + init_value(value_t()))
    {
        m_output.set_update_slot(sigc::mem_fun(*this, &this_t::execute));
    }

	/// Returns a slot that should be connected to input properties to signal that the output value has changed.
	sigc::slot<void, ihint*> make_update_value_slot()
    {
        return m_output.make_slot();
    }

private:
	/// Stores the output value
	function_node::output_property_t<value_t> m_output;

	/// Called whenever the output value has been modified and needs to be updated.
	void execute(const std::vector<ihint*>& Hints, value_t& Output)
    {
        on_update_value(Output);
    }

	/// Override this in derived classes, to return a new / modified value
	virtual void on_update_value(value_t& Output)
    {
        Output = value_t();
    }
};

} // namespace k3d

#endif // !K3DSDK_SINGLE_SOURCE_H

