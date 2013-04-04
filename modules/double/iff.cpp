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

#include <k3dsdk/scalar_source.h>

#include <k3d-i18n-config.h>
#include <k3dsdk/document_plugin_factory.h>

namespace module
{

namespace scalar
{

/// If condition holds return fist input, otherwise second
class iff :
	public k3d::scalar_source
{
	typedef k3d::scalar_source base;
public:
	iff(k3d::iplugin_factory& Factory, k3d::idocument& Document) :
		base(Factory, Document, _("'if then else' operator.")),
        m_condition(init_owner(*this) + init_name("condition") + init_label(_("Condition")) + init_description(_("Boolean condition")) + init_value(true)),
		m_input1(init_owner(*this) + init_name("input1") + init_label(_("Input 1")) + init_description(_("First input float")) + init_value(0.0)),
		m_input2(init_owner(*this) + init_name("input2") + init_label(_("Input 2")) + init_description(_("Second input float")) + init_value(0.0))
	{
        m_condition.changed_signal().connect(k3d::hint::converter<
			k3d::hint::convert<k3d::hint::any, k3d::hint::none> >(make_update_value_slot()));
		m_input1.changed_signal().connect(k3d::hint::converter<
			k3d::hint::convert<k3d::hint::any, k3d::hint::none> >(make_update_value_slot()));
		m_input2.changed_signal().connect(k3d::hint::converter<
			k3d::hint::convert<k3d::hint::any, k3d::hint::none> >(make_update_value_slot()));
	}

	static k3d::iplugin_factory& get_factory()
	{
		static k3d::document_plugin_factory<iff > factory(
			k3d::uuid(0x0338911f, 0x8f1749cf, 0xbeb3c4ee, 0x8967fc4f),
			"DoubleIff",
			_("If condition holds return fist input, otherwise second"),
			"Double",
			k3d::iplugin_factory::STABLE);

		return factory;
	}

private:
    k3d_data(k3d::bool_t, immutable_name, change_signal, with_undo, local_storage, no_constraint, writable_property, with_serialization) m_condition;
	k3d_data(k3d::double_t, immutable_name, change_signal, with_undo, local_storage, no_constraint, writable_property, with_serialization) m_input1;
	k3d_data(k3d::double_t, immutable_name, change_signal, with_undo, local_storage, no_constraint, writable_property, with_serialization) m_input2;

	void on_update_value(k3d::double_t& Output)
	{
		Output = m_condition.pipeline_value() ? m_input1.pipeline_value() : m_input2.pipeline_value();
	}
};

k3d::iplugin_factory& iff_factory()
{
	return iff::get_factory();
}

} //namespace scalar

} // namespace module



