#ifndef K3D_TESTS_UNIT_TESTS_MOCKS_IPLUGIN_FACTORY_H
#define	K3D_TESTS_UNIT_TESTS_MOCKS_IPLUGIN_FACTORY_H

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

#include <turtle/mock.hpp>
#include <k3dsdk/iplugin_factory.h>

namespace k3d
{
namespace tests
{

MOCK_BASE_CLASS( iplugin_factory_mock, iplugin_factory )
{
    MOCK_METHOD( factory_id, 0 )
    MOCK_METHOD( name, 0 )
    MOCK_METHOD( short_description, 0 )
    MOCK_METHOD( categories, 0 )
    MOCK_METHOD( quality, 0 )
    MOCK_METHOD( implements, 1 )
    MOCK_METHOD( interfaces, 0 )
    MOCK_METHOD( metadata, 0 )
};

} // namespace tests
} // namespace k3d
#endif // !K3D_TESTS_UNIT_TESTS_MOCKS_IPLUGIN_FACTORY_H

