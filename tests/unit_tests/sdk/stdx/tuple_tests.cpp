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

#include <k3dsdk/stdx/tuple.h>

#include <exception>
#include <functional>
#include <tuple>

#include <boost/test/unit_test.hpp>

using namespace std;
using namespace stdx;
using namespace boost;

BOOST_AUTO_TEST_SUITE( tuple_suite )
        
struct accum { 
    int operator()(const int& a, const int& b) {
        acc += a + b;
        return acc;
    }
    int acc{0};
};

BOOST_AUTO_TEST_CASE( unwrap_and_forward_test )
{
    auto t = make_tuple(1, 2);
    BOOST_CHECK_EQUAL( -3, unwrap_and_forward(plus<int>(), negate<int>(), 
            typename make_indexes<int, int>::type(), t) );
    auto acc = accum();
    BOOST_CHECK_EQUAL( -3, unwrap_and_forward(acc, negate<int>(), 
            typename make_indexes<int, int>::type(), t) );
    BOOST_CHECK_EQUAL( -3, acc.acc );
}
        
BOOST_AUTO_TEST_SUITE_END()

