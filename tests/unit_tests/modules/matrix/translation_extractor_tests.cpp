#include <boost/test/unit_test.hpp>
#include <boost/any.hpp>
#include <sigc++/connection.h>
#include <turtle/mock.hpp>

#include <k3dsdk/algebra.h>
#include <k3dsdk/vector3.h>
#include <k3dsdk/vector4.h>
#include <k3dsdk/iproperty.h>
#include <k3dsdk/state_change_set.h>
#include <modules/matrix/translation_extractor.h>
#include <idocument_mock.h>
#include <istate_recorder_mock.h>

using namespace std;
using namespace boost;
using namespace sigc;
using namespace k3d;
using namespace module::matrix;

BOOST_AUTO_TEST_SUITE( translation_extractor_suite )

BOOST_AUTO_TEST_CASE( test1 )
{
    idocument_mock doc;
    istate_recorder_mock recorder;
    MOCK_EXPECT( doc.state_recorder ).returns( recorder );
    state_change_set changeSet;
    MOCK_EXPECT( recorder.current_change_set ).returns( &changeSet );
    MOCK_EXPECT( recorder.connect_recording_done_signal ).returns( connection() );
    
    translation_extractor extractor(translation_extractor::get_factory(), doc);
    
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
