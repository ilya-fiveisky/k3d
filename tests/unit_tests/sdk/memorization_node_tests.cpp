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

#include <k3dsdk/nodes/memorization.h>

#include <exception>
#include <string>

#include <boost/test/unit_test.hpp>

#include <turtle/mock.hpp>

#include <k3dsdk/algebra.h>
#include <k3dsdk/data.h>
#include <k3dsdk/document.h>
#include <k3dsdk/imatrix_sink.h>
#include <k3dsdk/imatrix_source.h>
#include <k3dsdk/interface_list.h>
#include <k3dsdk/iproperty.h>
#include <k3dsdk/node.h>
#include <k3dsdk/stdx/tuple/misc.h>
#include <k3dsdk/uuid.h>
#include <k3dsdk/vector3.h>
#include <k3dsdk/vector4.h>

#include <fixture.h>
#include <utils.h>

using namespace std;
using namespace stdx;
using namespace boost;
using namespace sigc;
using namespace k3d;
using namespace k3d::nodes;
using namespace k3d::tests;

BOOST_AUTO_TEST_SUITE( memorization_node_suite )
        
struct the_node_info { string name = "NodeInfo"; string description = "Node description";
        uuid id = uuid(0x835bb1af, 0x95a04399, 0x856afa74, 0x92a2bda4); string category = "Category1";};

struct the_type_info { matrix4 default_value = identity3();};

typedef memorization<the_node_info, matrix4, the_type_info, interface_list<imatrix_source,
        interface_list<imatrix_sink>>> memorization_node_t;

BOOST_AUTO_TEST_SUITE( initialization_suite )

BOOST_FIXTURE_TEST_CASE( construct_memorization_node, fixture )
{
    BOOST_CHECK_NO_THROW( memorization_node_t(plugin_factory(), doc_mock()) );
}

BOOST_AUTO_TEST_SUITE_END() // initialization_suite


BOOST_AUTO_TEST_SUITE( properties_usage_suite )

BOOST_FIXTURE_TEST_CASE( check_output_value, fixture )
{
    memorization_node_t memorization(plugin_factory(), doc_mock());
    
    auto inputProp = get_writable_property_by_name(memorization, "input");
    
    auto testMatrix = matrix4(
        vector4(1, 0, 0, 1), 
        vector4(0, 1, 0, 2), 
        vector4(0, 0, 1, 3), 
        vector4(0, 0, 0, 1));
    inputProp->property_set_value(testMatrix);

    auto outputProp = get_property_by_name(memorization, "output");
    
    BOOST_CHECK_EQUAL( any_cast<matrix4>(outputProp->property_internal_value()), identity3() );
    
    auto eventProp = get_writable_property_by_name(memorization, "event");
    
    eventProp->property_set_value(true);
    
    BOOST_CHECK_EQUAL( any_cast<matrix4>(outputProp->property_internal_value()), testMatrix );
}

BOOST_AUTO_TEST_SUITE_END() // properties_usage_suite
        
BOOST_AUTO_TEST_SUITE_END() // memorization_node_suite

