#ifndef K3D_ISTATE_RECORDER_MOCK_H
#define	K3D_ISTATE_RECORDER_MOCK_H

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

#include <turtle/mock.hpp>
#include <k3dsdk/istate_recorder.h>

namespace k3d
{
    
MOCK_BASE_CLASS( istate_recorder_mock, istate_recorder )
{
    MOCK_METHOD( start_recording, 2 )
	MOCK_METHOD( current_change_set, 0 )
	MOCK_METHOD( stop_recording, 1 )
	MOCK_METHOD( commit_change_set, 3 )
	MOCK_METHOD( root_nodes, 0 )
	MOCK_METHOD( current_node, 0 )
	MOCK_METHOD( newest_node, 0 )
	MOCK_METHOD( last_saved_node, 0 )
	MOCK_METHOD( set_current_node, 1 )
	MOCK_METHOD( mark_saved, 0 )
	MOCK_METHOD( connect_recording_done_signal, 1 )
	MOCK_METHOD( connect_node_added_signal, 1 )
	MOCK_METHOD( connect_current_node_changed_signal, 1 )
	MOCK_METHOD( connect_last_saved_node_changed_signal, 1 )
};

} // namespace k3d
#endif // !K3D_ISTATE_RECORDER_MOCK_H

