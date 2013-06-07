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

#include <k3dsdk/function_nodes.h>

#include <exception>
#include <tuple>

#include <boost/test/unit_test.hpp>

#include <turtle/mock.hpp>

#include <k3dsdk/data.h>
#include <k3dsdk/document.h>
#include <k3dsdk/node.h>
#include <k3dsdk/vector3.h>

#include <fixture.h>

using namespace std;
using namespace stdx;
using namespace boost;
using namespace sigc;
using namespace k3d;
using namespace k3d::tests;
using namespace k3d::function_nodes;

BOOST_AUTO_TEST_SUITE( function_nodes_suite )
        
BOOST_AUTO_TEST_SUITE( fatal_errors_suite )

property_info<vector3> input1_info(name_t("a"), label_t("A"), description_t("A"));

typedef input_property<vector3, input1_info> prop_t;

template<typename... Args> struct segfault_node : node {
    segfault_node(iplugin_factory& Factory, idocument& Document) : 
        node(Factory, Document),
		m_args(Args(*this)...) {}
    
    tuple<Args...> m_args;
};

typedef segfault_node<prop_t> segfault_node_t;

BOOST_FIXTURE_TEST_CASE( construct_segfault_node, fixture )
{
    // It fails here because of copy ctor in the m_args initialization:
    // temporary property is registered in its ctor tnen deleted but not unregistered.
    // Hence we get access violation inside dynamic_cast in property_collection destructor.
    // It can be seen in gdb.
    // Though I can't undestand why it doesn't crash before in the temporary property destructor 
    // where we have uninitialized m_deleted_signal.
    BOOST_CHECK_NO_THROW( segfault_node_t(plugin_factory(), doc_mock()) );
}

BOOST_AUTO_TEST_SUITE_END() // fatal_errors_suite
       
BOOST_AUTO_TEST_SUITE_END() // function_nodes_suite
