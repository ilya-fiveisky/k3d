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

#include <k3dsdk/nodes/functional/single.h>
#include <k3dsdk/nodes/property.h>

#include <exception>
#include <string>
#include <tuple>

#include <boost/test/unit_test.hpp>

#include <turtle/mock.hpp>

#include <k3dsdk/algebra.h>
#include <k3dsdk/data.h>
#include <k3dsdk/document.h>
#include <k3dsdk/iproperty.h>
#include <k3dsdk/node.h>
#include <k3dsdk/stdx/tuple/misc.h>
#include <k3dsdk/uuid.h>
#include <k3dsdk/vector3.h>
#include <k3dsdk/vector4.h>

#include <fixture.h>

using namespace std;
using namespace stdx;
using namespace boost;
using namespace sigc;
using namespace k3d;
using namespace k3d::tests;
using namespace k3d::nodes;
using namespace k3d::nodes::functional;

BOOST_AUTO_TEST_SUITE( functional_nodes_suite )
        
struct the_node_info { string name = "NodeInfo"; string description = "Node description";
        uuid id = uuid(0x835bb1af, 0x95a04399, 0x856afa74, 0x92a2bda4); string category = "Category1";};

struct input1_info { string name = "a"; string label = "A"; string description = "A"; vector3 default_value = vector3();};
struct input2_info { string name = "b"; string label = "B"; string description = "B"; vector3 default_value = vector3();};

struct output_info { string name = "output"; string label = "Output"; string description = "Output"; vector3 default_value = vector3();};

typedef single<the_node_info, std::minus<vector3>, output_property<vector3, output_info>, 
        input_property<vector3, input1_info>, input_property<vector3, input2_info>> binary_node_t;

typedef single<the_node_info, std::negate<vector3>, output_property<vector3, output_info>, 
        input_property<vector3, input1_info>> negate_node_t;
typedef negate_node_t unary_node_t;


struct int_input_info { string name = "int"; string label = "Int"; string description = "Int input"; 
    int default_value = 12345;};
struct double_input_info { string name = "double"; string label = "Double"; 
    string description = "Double input"; double default_value = 1.2345;};

struct string_output_info { string name = "string"; string label = "String"; 
    string description = "String Output"; string default_value = "";};

struct str_concat { string operator()(const int& I, const double& D) const
    {return to_string(I) + to_string(D);} };
    
typedef single<the_node_info, str_concat, output_property<string, string_output_info>, 
        input_property<int, int_input_info>, input_property<double, double_input_info>> hetero_node_t;


struct constant { 
    vector3 operator()() const {return vector3();}
};
typedef single<the_node_info, constant, output_property<vector3, output_info>> constant_node_t;

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

BOOST_FIXTURE_TEST_CASE( check_property_names, fixture )
{
    binary_node_t binaryNode(plugin_factory(), doc_mock());
    BOOST_CHECK_EQUAL( binaryNode.output_property().property_name(), "output" );
    BOOST_CHECK_EQUAL( get<0>(binaryNode.inputs()).property_name(), "a" );
    BOOST_CHECK_EQUAL( get<1>(binaryNode.inputs()).property_name(), "b" );
}

BOOST_FIXTURE_TEST_CASE( check_hetero_node_property_names, fixture )
{
    hetero_node_t heteroNode(plugin_factory(), doc_mock());
    BOOST_CHECK_EQUAL( heteroNode.output_property().property_name(), "string" );
    BOOST_CHECK_EQUAL( get<0>(heteroNode.inputs()).property_name(), "int" );
    BOOST_CHECK_EQUAL( get<1>(heteroNode.inputs()).property_name(), "double" );
}

BOOST_FIXTURE_TEST_CASE( check_hetero_node_property_values, fixture )
{
    hetero_node_t heteroNode(plugin_factory(), doc_mock());
    BOOST_CHECK_EQUAL( heteroNode.output_property().pipeline_value(), "123451.234500" );
    BOOST_CHECK_EQUAL( get<0>(heteroNode.inputs()).pipeline_value(), 12345 );
    BOOST_CHECK_EQUAL( get<1>(heteroNode.inputs()).pipeline_value(), 1.2345 );
}

BOOST_FIXTURE_TEST_CASE( check_hetero_node_property_types, fixture )
{
    hetero_node_t heteroNode(plugin_factory(), doc_mock());
    BOOST_CHECK_EQUAL( heteroNode.output_property().property_type().name(), typeid(string).name() );
    BOOST_CHECK_EQUAL( get<0>(heteroNode.inputs()).property_type().name(), typeid(int).name() );
    BOOST_CHECK_EQUAL( get<1>(heteroNode.inputs()).property_type().name(), typeid(double).name() );
}

BOOST_AUTO_TEST_SUITE_END() // properties_usage_suite
        
BOOST_AUTO_TEST_SUITE_END() // functional_nodes_suite
