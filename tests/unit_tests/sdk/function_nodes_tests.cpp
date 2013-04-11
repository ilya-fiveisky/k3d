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

#include <k3dsdk/algebra.h>
#include <k3dsdk/data.h>
#include <k3dsdk/document.h>
#include <k3dsdk/iproperty.h>
#include <k3dsdk/node.h>
#include <k3dsdk/state_change_set.h>
#include <k3dsdk/stdx/tuple/misc.h>
#include <k3dsdk/uuid.h>
#include <k3dsdk/vector3.h>
#include <k3dsdk/vector4.h>

#include <fixture.h>
#include <mocks/idocument_mock.h>
#include <mocks/iplugin_factory_mock.h>
#include <mocks/istate_recorder_mock.h>
#include <mocks/node_mock.h>
#include <mocks/node_stub.h>
#include <mocks/property_stub.h>

using namespace std;
using namespace stdx;
using namespace boost;
using namespace sigc;
using namespace k3d;
using namespace k3d::tests;
using namespace k3d::function_nodes;

BOOST_AUTO_TEST_SUITE( function_nodes_suite )
        
category_t category("Category1");

node_info the_node_info(name_t("NodeInfo"), description_t("Node description"), 
        uuid(0x835bb1af, 0x95a04399, 0x856afa74, 0x92a2bda4), category);
property_info<vector3> input1_info(name_t("a"), label_t("A"), description_t("A"));
property_info<vector3> input2_info(name_t("b"), label_t("B"), description_t("B"));
property_info<vector3> output_info(name_t("output"), label_t("Output"), description_t("Output"));

typedef function_node<the_node_info, std::minus<vector3>, output_property<vector3, output_info>, 
        input_property<vector3, input1_info>, input_property<vector3, input2_info>> binary_node_t;

typedef function_node<the_node_info, std::negate<vector3>, output_property<vector3, output_info>, 
        input_property<vector3, input1_info>> negate_node_t;
typedef negate_node_t unary_node_t;

struct constant { 
    vector3 operator()() const {return vector3();}
};
typedef function_node<the_node_info, constant, output_property<vector3, output_info>> constant_node_t;

BOOST_AUTO_TEST_SUITE( initialization_suite )

BOOST_FIXTURE_TEST_CASE( construct_binary_node, fixture )
{
    BOOST_CHECK_NO_THROW( binary_node_t(plugin_factory(), doc_mock()) );
}

BOOST_FIXTURE_TEST_CASE( construct_unary_node, fixture )
{
    BOOST_CHECK_NO_THROW( unary_node_t(plugin_factory(), doc_mock()) );
}

BOOST_FIXTURE_TEST_CASE( construct_constant_node, fixture )
{
    BOOST_CHECK_NO_THROW( constant_node_t(plugin_factory(), doc_mock()) );
}

BOOST_FIXTURE_TEST_CASE( construct_binary_node_with_quasi_real_context, fixture )
{
    BOOST_CHECK_NO_THROW( binary_node_t(binary_node_t::get_factory(), doc_real()) );
}

typedef input_property<vector3, input1_info> prop_t;

BOOST_FIXTURE_TEST_CASE( construct_property_with_node_mock, fixture )
{
    BOOST_CHECK_NO_THROW( (prop_t(mock_node())) );
}

BOOST_FIXTURE_TEST_CASE( copy_construct_property_with_node_mock, fixture )
{
    BOOST_CHECK_NO_THROW( prop_t(prop_t(mock_node())) );
}

BOOST_FIXTURE_TEST_CASE( copy_construct_property_with_real_node, fixture )
{
    node realNode(plugin_factory(), doc_mock());
    BOOST_CHECK_NO_THROW( prop_t(prop_t(realNode)) );
}

template<typename... Args> struct node_test : node {
    node_test(iplugin_factory& Factory, idocument& Document) : 
        node(Factory, Document),
		m_args(variadic_id<Args>(*this)...) {}
    
    tuple<Args...> m_args;
};

typedef node_test<prop_t> node_test_t;

BOOST_FIXTURE_TEST_CASE( construct_node_test_node, fixture )
{
    BOOST_CHECK_NO_THROW( node_test_t(plugin_factory(), doc_mock()) );
}

template<typename... Args> struct segfault_node : node {
    segfault_node(iplugin_factory& Factory, idocument& Document) : 
        node(Factory, Document),
		m_args(Args(*this)...) {}
    
    tuple<Args...> m_args;
};

typedef segfault_node<prop_t> segfault_node_t;

BOOST_FIXTURE_TEST_CASE( construct_segfault_node, fixture )
{
    BOOST_CHECK_NO_THROW( segfault_node_t(plugin_factory(), doc_mock()) );
}

BOOST_AUTO_TEST_SUITE_END() // initialization_suite


BOOST_AUTO_TEST_SUITE( properties_usage_suite )

BOOST_FIXTURE_TEST_CASE( get_output_pipeline_value, fixture )
{
    unary_node_t unaryNode(plugin_factory(), doc_mock());
    BOOST_CHECK_NO_THROW( unaryNode.output_property().pipeline_value() );
}

BOOST_FIXTURE_TEST_CASE( negate_node, fixture )
{
    negate_node_t negateNode(plugin_factory(), doc_mock());
    get<0>(negateNode.inputs()).set_value(vector3(1, 1, 1));
    BOOST_CHECK_EQUAL( 
            negateNode.output_property().pipeline_value(), 
            -get<0>(negateNode.inputs()).pipeline_value() );
}

BOOST_AUTO_TEST_SUITE_END() // properties_usage_suite
        
BOOST_AUTO_TEST_SUITE_END() // function_nodes_suite
