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
#include <k3dsdk/interface_list.h>
#include <k3dsdk/node.h>
#include <k3dsdk/nodes/memorization.h>
#include <k3dsdk/value_demand_storage.h>

using namespace std;
using namespace k3d;
using namespace k3d::nodes;

namespace module
{
namespace matrix
{

/////////////////////////////////////////////////////////////////////////////
// memorization

struct the_node_info { string name = "MatrixMemorization"; string description = "Memorizes input matrix";
    uuid id = uuid(0xc071766b, 0x79a6406f, 0xa1041714, 0xc5766d83); string category = "Matrix";};

struct the_type_info { matrix4 default_value = identity3();};

typedef memorization<the_node_info, matrix4, the_type_info, interface_list<imatrix_source,
        interface_list<imatrix_sink>>> memorization_base;

class memorization :
	public memorization_base,
	public imatrix_source,
	public imatrix_sink
{
    typedef memorization_base base;
public:
	memorization(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document)
	{
	}

	iproperty& matrix_source_output()
	{
		return m_output;
	}

	iproperty& matrix_sink_input()
	{
		return m_input;
	}
};

/////////////////////////////////////////////////////////////////////////////
// memorization_factory

iplugin_factory& memorization_factory()
{
	return memorization_base::get_factory();
}

} // namespace matrix
} // namespace module


