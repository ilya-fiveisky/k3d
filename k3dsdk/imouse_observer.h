#ifndef K3DSDK_INPUT_DEVICES_IMOUSE_OBSERVER_H
#define K3DSDK_INPUT_DEVICES_IMOUSE_OBSERVER_H

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

namespace k3d
{

namespace input_devices
{

/////////////////////////////////////////////////////////////////////////////
// imouse_observer

class imouse_observer
{
public:
	virtual ~imouse_observer() {}

	virtual void mouse_move(double_t x, double_t y) = 0;
	
	virtual void lbutton_down() = 0;
	virtual void lbutton_up() = 0;
	virtual void lbutton_click() = 0;
	virtual void lbutton_double_click() = 0;
	virtual void lbutton_triple_click() = 0;
	virtual void lbutton_start_drag() = 0;
	virtual void lbutton_drag() = 0;
	virtual void lbutton_end_drag() = 0;

	virtual void mbutton_down() = 0;
	virtual void mbutton_up() = 0;
	virtual void mbutton_click() = 0;
	virtual void mbutton_double_click() = 0;
	virtual void mbutton_triple_click() = 0;
	virtual void mbutton_start_drag() = 0;
	virtual void mbutton_drag() = 0;
	virtual void mbutton_end_drag() = 0;

	virtual void rbutton_down() = 0;
	virtual void rbutton_up() = 0;
	virtual void rbutton_click() = 0;
	virtual void rbutton_double_click() = 0;
	virtual void rbutton_triple_click() = 0;
	virtual void rbutton_start_drag() = 0;
	virtual void rbutton_drag() = 0;
	virtual void rbutton_end_drag() = 0;

	virtual void scroll() = 0;

protected:
    imouse_observer() {}
	imouse_observer(const imouse_observer& Other) {}
	imouse_observer& operator=(const imouse_observer&) { return *this; }
};

} // namespace input_devices

} // namespace k3d

#endif // !K3DSDK_INPUT_DEVICES_IMOUSE_OBSERVER_H


