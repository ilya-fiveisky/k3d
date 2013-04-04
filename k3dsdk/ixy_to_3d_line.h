#ifndef K3DSDK_XY_TO_3D_LINE_H
#define K3DSDK_XY_TO_3D_LINE_H

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
#include <k3dsdk/line3.h>

namespace k3d
{

/////////////////////////////////////////////////////////////////////////////
// ixy_to_3d_line

/// Abstract interface for converting 2D coordinates to 3D line.
class ixy_to_3d_line
{
public:
	virtual ~ixy_to_3d_line() {}

    /// Converts 2D coordinates to 3D line.
	virtual line3 convert(const k3d::point2&) = 0;

protected:
    ixy_to_3d_line() {}
	ixy_to_3d_line(const ixy_to_3d_line& Other) {}
	ixy_to_3d_line& operator=(const ixy_to_3d_line&) { return *this; }
};

/// Abstract interface for xy_to_3d_line user.
class ixy_to_3d_line_client
{
public:
	virtual ~ixy_to_3d_line_client() {}

    /// Sets node picker for client.
	virtual void set_xy_to_3d_line(ixy_to_3d_line*) = 0;

protected:
    ixy_to_3d_line_client() {}
	ixy_to_3d_line_client(const ixy_to_3d_line_client& Other) {}
	ixy_to_3d_line_client& operator=(const ixy_to_3d_line_client&) { return *this; }
};

} // namespace k3d

#endif // !K3DSDK_XY_TO_3D_LINE_H


