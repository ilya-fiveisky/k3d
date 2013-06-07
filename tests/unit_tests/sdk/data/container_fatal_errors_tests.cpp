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

#include <exception>

#include <boost/test/unit_test.hpp>

#include <turtle/mock.hpp>

#include <k3d-i18n-config.h>
#include <k3dsdk/data.h>
#include <k3dsdk/node.h>

#include <fixture.h>

using namespace std;
using namespace boost;
using namespace sigc;
using namespace k3d;
using namespace k3d::data;
using namespace k3d::tests;

BOOST_AUTO_TEST_SUITE( data_container_suite )
        
BOOST_AUTO_TEST_SUITE( fatal_errors_suite )
        
typedef container_t<bool_t, immutable_name, change_signal, no_undo, local_storage, no_constraint, 
        read_only_property, with_serialization> prop_t;

prop_t* create_prop(node& Node)
{
    return new prop_t(init_owner(Node) + init_name("x") + init_label(_("x")) + 
            init_description(_("x")) + init_value(false));
}

BOOST_FIXTURE_TEST_CASE( access_violation_in_property_destructor, fixture )
{
    node realNode(plugin_factory(), doc_mock());
    prop_t* prop(create_prop(realNode));
    // Access violation here because m_deleted_signal wasn't initialized
    BOOST_CHECK_NO_THROW( delete prop );
}

BOOST_FIXTURE_TEST_CASE( access_violation_in_properties, fixture )
{
    node realNode(plugin_factory(), doc_mock());
    prop_t* prop(create_prop(realNode));
    BOOST_CHECK_NO_THROW( delete prop );
    // Access violation here because read_only_property has been deleted in previous line
    BOOST_CHECK_NO_THROW( realNode.properties()[0]->property_name() );
}

BOOST_FIXTURE_TEST_CASE( access_violation_in_persistent_objects, fixture )
{
    node realNode(plugin_factory(), doc_mock());
    prop_t* prop = create_prop(realNode);
    BOOST_CHECK_NO_THROW( delete prop );
    // Access violation here because with_serialization has been deleted in previous line
    BOOST_CHECK_NO_THROW( realNode.persistent_objects()[0].first );
}

BOOST_AUTO_TEST_SUITE_END() // fatal_errors_suite
BOOST_AUTO_TEST_SUITE_END() // data_container_suite

