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

#include <modules/boolean/operations.h>

#include <boost/any.hpp>
#include <boost/test/unit_test.hpp>

#include <sigc++/connection.h>

#include <turtle/mock.hpp>

#include <k3dsdk/algebra.h>
#include <k3dsdk/iproperty.h>

#include <fixture.h>
#include <utils.h>

using namespace std;
using namespace boost;
using namespace sigc;
using namespace k3d;
using namespace k3d::tests;
using namespace module::boolean;

BOOST_AUTO_TEST_SUITE( boolean_suite )

BOOST_FIXTURE_TEST_CASE( conjunction_test, fixture )
{
    conjunction::type conj(plugin_factory(), doc_mock());
    
    auto aProp = get_writable_property_by_name(conj, "a");
    aProp->property_set_value(true);
    auto bProp = get_writable_property_by_name(conj, "b");
    bProp->property_set_value(true);
    
    auto outputProp = get_property_by_name(conj, "a_and_b");
            
    BOOST_CHECK( any_cast<bool_t>(outputProp->property_internal_value()) == true );
}

BOOST_AUTO_TEST_SUITE_END()
