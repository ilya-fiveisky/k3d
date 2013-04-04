#ifndef K3DSDK_INODE_PICKER_H
#define K3DSDK_INODE_PICKER_H

// K-3D
// Copyright (c) 1995-2005, Timothy M. Shead
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

#include <k3dsdk/point2.h>

namespace k3d
{

/////////////////////////////////////////////////////////////////////////////
// inode_picker

/// Abstract interface for user friendly node picking.
class inode_picker
{
public:
	virtual ~inode_picker() {}

    /// Picks node by given viewport coordinates.
	virtual inode* pick_node(const k3d::point2&) = 0;

protected:
    inode_picker() {}
	inode_picker(const inode_picker& Other) {}
	inode_picker& operator=(const inode_picker&) { return *this; }
};

/// Abstract interface for inode_picker user.
class inode_picker_client
{
public:
	virtual ~inode_picker_client() {}

    /// Sets node picker for client.
	virtual void set_node_picker(inode_picker*) = 0;

protected:
    inode_picker_client() {}
	inode_picker_client(const inode_picker_client& Other) {}
	inode_picker_client& operator=(const inode_picker_client&) { return *this; }
};

} // namespace k3d

#endif // !K3DSDK_INODE_PICKER_H


