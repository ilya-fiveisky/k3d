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
#include <k3dsdk/line3.h>
#include <k3dsdk/ixy_to_3d_line.h>
#include <k3dsdk/value_demand_storage.h>
#include <k3dsdk/single_source.h>

using namespace k3d;
using namespace k3d::data;

namespace module
{

namespace object_pickers
{

/// Calculates 3d line from 2d coordinates.
class xy_to_3d_line :
	public single_source<line3>,
    public ixy_to_3d_line_client
{
	typedef single_source<line3> base;
public:
	xy_to_3d_line(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document, _("Calculates 3d line from 2d coordinates.")),
		m_xy(init_owner(*this) + init_name("xy") + init_label(_("(X, Y)")) + init_description(_("X,Y coordinates")) + init_value(point2())),
        m_xy_to_3d_line(NULL)
	{
            m_xy.changed_signal().connect(make_update_value_slot());
	}
        
    void set_xy_to_3d_line(k3d::ixy_to_3d_line* XyTo3dLine)
    {
        m_xy_to_3d_line = XyTo3dLine;
    }
    
	static iplugin_factory& get_factory()
	{
		static document_plugin_factory<xy_to_3d_line > factory(
			uuid(0x81c3303a, 0x470745f8, 0xabb0d488, 0x65dc6b19),
			"XyTo3dLine",
			_("Calculates 3d line from 2d coordinates"),
			"ObjectPickers",
			iplugin_factory::EXPERIMENTAL);

		return factory;
	}

private:
    void on_update_value(line3& Output)
	{
        if(m_xy_to_3d_line)
            Output = m_xy_to_3d_line->convert(m_xy.pipeline_value());
	}

    k3d_data(point2, immutable_name, change_signal, with_undo, local_storage, no_constraint, writable_property, with_serialization) m_xy;
    
    k3d::ixy_to_3d_line* m_xy_to_3d_line;
};

iplugin_factory& xy_to_3d_line_factory()
{
	return xy_to_3d_line::get_factory();
}

} //namespace object_pickers

} // namespace module



