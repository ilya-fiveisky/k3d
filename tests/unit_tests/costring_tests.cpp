#include <boost/test/unit_test.hpp>
#include <constexpr_string/costring.h>

using namespace std;
using namespace boost;
using namespace constexpr_string;

BOOST_AUTO_TEST_SUITE( costring_suite )

BOOST_AUTO_TEST_CASE( test1 )
{
    costring costr("zzz");
    BOOST_CHECK( costr.size() == 3 );
}

BOOST_AUTO_TEST_SUITE_END()
        