// K-3D
// Copyright (c) 1995-2008, Timothy M. Shead
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

#include <modules/matrix/translation_extractor.h>

#include <k3d-i18n-config.h>
#include <k3dsdk/algebra.h>
#include <k3dsdk/document_plugin_factory.h>
#include <k3dsdk/imatrix_sink.h>
#include <k3dsdk/nodes/property.h>
#include <k3dsdk/single_source.h>
#include <k3dsdk/vector3.h>

using namespace std;
using namespace k3d;
using namespace k3d::data;
using namespace k3d::nodes;

namespace module
{
namespace matrix
{

/////////////////////////////////////////////////////////////////////////////
// translation_extractor

translation_extractor::translation_extractor(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document, _("Translation vector from the input transform matrix.")),
        m_input(init_owner(*this) + init_name("input_matrix") + init_label(_("Input matrix")) 
            + init_description(_("Input matrix")) + init_value(identity3()))
{
    m_input.changed_signal().connect(hint::converter<
        hint::convert<hint::any, hint::none> >(make_update_value_slot()));
}
        
iproperty& translation_extractor::matrix_sink_input()
{
    return m_input;
}

void translation_extractor::on_update_value(vector3& Output)
{
    Output = k3d::extract_translation(m_input.pipeline_value());
}

} // namespace matrix
} // namespace module



