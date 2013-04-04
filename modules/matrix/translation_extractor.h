#ifndef MODULE_MATRIX_EXTRACT_TRANSLATION_H
#define	MODULE_MATRIX_EXTRACT_TRANSLATION_H

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

#include <k3dsdk/document_plugin_factory.h>
#include <k3dsdk/vector3.h>
#include <k3dsdk/imatrix_sink.h>
#include <k3dsdk/single_source.h>
#include <k3dsdk/function_node/property.h>

namespace module
{

namespace matrix
{

using namespace k3d;
    
/////////////////////////////////////////////////////////////////////////////
// extract_translation

class translation_extractor :
    public single_source<vector3>,
	public imatrix_sink
{
	typedef single_source<vector3> base;

public:
	translation_extractor(iplugin_factory& Factory, idocument& Document);

    iproperty& matrix_sink_input();

	static iplugin_factory& get_factory()
    {
        static document_plugin_factory<translation_extractor,
            interface_list<imatrix_sink > > factory(
            uuid(0x760e5465, 0xaba1413b, 0xa7d08f2d, 0x6bf682ab),
            "MatrixTranslationExtractor",
            _("Extract translation from a transformation matrix."),
            "Matrix",
            iplugin_factory::EXPERIMENTAL);

        return factory;
   }

private:
	function_node::input_property_t<matrix4> m_input;
    
    void on_update_value(vector3& Output);
};

} // namespace matrix

} // namespace module

#endif // !MODULE_MATRIX_EXTRACT_TRANSLATION_H

