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

#include <csignal>

#include <exception>

struct access_violation : std::exception 
{
    const char* what() const noexcept {return "SIGSEGV";}
};

void signal_handler(int signal)
{
    throw access_violation();
}

typedef void (*signal_handler_pointer)(int);

// For catching access violation in order to run all tests.
signal_handler_pointer prev_handler = signal(SIGSEGV , signal_handler);
