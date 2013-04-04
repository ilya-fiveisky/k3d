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
#include <k3dsdk/hints.h>
#include <k3dsdk/imatrix_sink.h>
#include <k3dsdk/imatrix_source.h>
#include <k3dsdk/node.h>
#include <k3dsdk/value_demand_storage.h>

using namespace std;
using namespace k3d;

namespace module
{

namespace matrix
{

/////////////////////////////////////////////////////////////////////////////
// memorization

class memorization :
	public node,
	public imatrix_source,
	public imatrix_sink
{
	typedef node base;

public:
	memorization(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document),
		m_input(init_owner(*this) + init_name("input_matrix") + init_label(_("Input matrix")) + init_description(_("Input matrix")) + init_value(identity3())),
		m_event(init_owner(*this) + init_name("event") + init_label(_("Event")) + init_description(_("Event on which to memorize")) + init_value(false)),
		m_output(init_owner(*this) + init_name("output_matrix") + init_label(_("Output Matrix")) + init_description(_("Output matrix (read only)")) + init_value(identity3()))
	{
		m_event.changed_signal().connect(sigc::mem_fun(*this, &memorization::on_event));
		m_output.set_update_slot(sigc::mem_fun(*this, &memorization::execute));
	}

	iproperty& matrix_source_output()
	{
		return m_output;
	}

	iproperty& matrix_sink_input()
	{
		return m_input;
	}

	static iplugin_factory& get_factory()
	{
		static document_plugin_factory<memorization,
			interface_list<imatrix_source,
			interface_list<imatrix_sink > > > factory(
				uuid(0xc071766b, 0x79a6406f, 0xa1041714, 0xc5766d83),
				"MatrixMemorization",
				_("Memorizes an arbitrary [transformation] matrix"),
				"Matrix",
				iplugin_factory::EXPERIMENTAL);

		return factory;
	}

private:
	k3d_data(matrix4, immutable_name, change_signal, with_undo, local_storage, no_constraint, writable_property, with_serialization) m_input;
	k3d_data(bool_t, immutable_name, change_signal, with_undo, local_storage, no_constraint, writable_property, with_serialization) m_event;
	k3d_data(matrix4, immutable_name, change_signal, no_undo, value_demand_storage, no_constraint, read_only_property, no_serialization) m_output;
    matrix4 m_matrix;

	/// Called whenever the output matrix has been modified and needs to be updated.
	void execute(const vector<ihint*>& Hints, matrix4& Matrix)
	{
		Matrix = m_matrix;
	}
    
    void on_event(ihint* Hints)
	{
        if(m_event.internal_value())
        {
            m_matrix = m_input.internal_value();
            m_output.update();
        }
	}

};

/////////////////////////////////////////////////////////////////////////////
// memorization_factory

iplugin_factory& memorization_factory()
{
	return memorization::get_factory();
}

} // namespace matrix

} // namespace module


