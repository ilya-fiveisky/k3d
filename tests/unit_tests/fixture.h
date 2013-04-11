#ifndef K3D_TESTS_UNIT_TESTS_FIXTURE_H
#define	K3D_TESTS_UNIT_TESTS_FIXTURE_H

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

#include <turtle/mock.hpp>

#include <k3dsdk/document.h>
#include <k3dsdk/signal_system.h>
#include <k3dsdk/state_change_set.h>

#include <mocks/idocument_mock.h>
#include <mocks/iplugin_factory_mock.h>
#include <mocks/istate_recorder_mock.h>
#include <mocks/node_mock.h>

namespace k3d
{
namespace tests
{

class fixture {
public:
    fixture() {
        MOCK_EXPECT( m_doc_mock.state_recorder ).returns( m_recorder );
        MOCK_EXPECT( m_recorder.current_change_set ).returns( &m_change_set );
        MOCK_EXPECT( m_recorder.connect_recording_done_signal ).returns( sigc::connection() );
        MOCK_EXPECT( m_mock_node.document ).returns( m_doc_mock );
        MOCK_EXPECT( m_mock_node.register_property );
        MOCK_EXPECT( m_mock_node.enable_serialization );
    }
    
    ~fixture(){ if(m_doc_real) close_document(*m_doc_real); }
    
    iplugin_factory_mock& plugin_factory() {return m_plugin_factory;}
    idocument_mock& doc_mock() {return m_doc_mock;}
    idocument& doc_real()
    {
        if(!m_doc_real) m_doc_real = create_document();
        return *m_doc_real;
    }
    node_mock& mock_node(){return m_mock_node;}
    
private:
    iplugin_factory_mock m_plugin_factory{};
    idocument_mock m_doc_mock{};
    idocument* m_doc_real{nullptr};
    node_mock m_mock_node{};
    istate_recorder_mock m_recorder{};
    state_change_set m_change_set{};
};

} // namespace tests
} // namespace k3d

#endif // !K3D_TESTS_UNIT_TESTS_FIXTURE_H

