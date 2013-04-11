#ifndef K3D_TESTS_UNIT_TESTS_MOCKS_NODE_MOCK_H
#define	K3D_TESTS_UNIT_TESTS_MOCKS_NODE_MOCK_H

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
#include <mocks/inode_mock.h>
#include <mocks/ipersistent_collection_mock.h>
#include <mocks/iproperty_collection_mock.h>

namespace k3d
{
namespace tests
{

struct node_mock : inode_mock, ipersistent_collection_mock, iproperty_collection_mock
{
};

} // namespace tests
} // namespace k3d
#endif // !K3D_TESTS_UNIT_TESTS_MOCKS_NODE_MOCK_H

