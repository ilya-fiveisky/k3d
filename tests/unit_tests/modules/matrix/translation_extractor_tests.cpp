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

#include <boost/any.hpp>
#include <boost/test/unit_test.hpp>

#include <sigc++/connection.h>

#include <turtle/mock.hpp>

#include <k3dsdk/algebra.h>
#include <k3dsdk/iproperty.h>
#include <k3dsdk/state_change_set.h>
#include <k3dsdk/vector3.h>
#include <k3dsdk/vector4.h>

#include <fixture.h>
#include <mocks/idocument_mock.h>
#include <mocks/istate_recorder_mock.h>

#include "tests/unit_tests/fixture.h"

using namespace std;
using namespace boost;
using namespace sigc;
using namespace k3d;
using namespace k3d::tests;
using namespace module::matrix;

BOOST_AUTO_TEST_SUITE( translation_extractor_suite )

BOOST_FIXTURE_TEST_CASE( test1, fixture )
{
    translation_extractor extractor(plugin_factory(), doc_mock());
    
    auto props = extractor.properties();
    
    auto it = find_if(props.begin(), props.end(), 
            [](iproperty* p){return typeid(matrix4) == p->property_type();});
    if(it == props.end())
    {
        BOOST_FAIL( "There is no matrix property!" );
    }
    auto matrixInput = dynamic_cast<iwritable_property*>(*it);
    if(!matrixInput)
    {
        BOOST_FAIL( "matrixInput isn't iwritable_property!" );
    }
    
    auto testMatrix = matrix4(
        vector4(1, 0, 0, 1), 
        vector4(0, 1, 0, 2), 
        vector4(0, 0, 1, 3), 
        vector4(0, 0, 0, 1));
    matrixInput->property_set_value(testMatrix);
    
    auto outputProp = *find_if(props.begin(), props.end(), 
            [](iproperty* p){return typeid(vector3) == p->property_type();});
            
    BOOST_CHECK( any_cast<vector3>(outputProp->property_internal_value()) == vector3(1, 2, 3) );
}

BOOST_AUTO_TEST_SUITE_END()
