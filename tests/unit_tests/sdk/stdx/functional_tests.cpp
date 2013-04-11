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

#include <boost/test/unit_test.hpp>
#include <exception>

#include <k3dsdk/stdx/functional.h>

using namespace std;
using namespace stdx;
using namespace boost;

BOOST_AUTO_TEST_SUITE( functional_suite )
        
BOOST_AUTO_TEST_CASE( has_result_type_test )
{
    BOOST_CHECK( has_result_type<plus<int>>::value );
    BOOST_CHECK( !has_result_type<int>::value );
}
        
BOOST_AUTO_TEST_SUITE_END()
