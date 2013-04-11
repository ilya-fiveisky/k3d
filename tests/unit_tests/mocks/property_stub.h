#ifndef K3D_TESTS_UNIT_TESTS_MOCKS_PROPERTY_STUB_H
#define	K3D_TESTS_UNIT_TESTS_MOCKS_PROPERTY_STUB_H

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

#include <sigc++/signal.h>

#include <k3dsdk/node.h>
#include <k3dsdk/ihint.h>

namespace k3d
{
namespace tests
{
    
template<typename value_t> class property_stub
{
    typedef sigc::signal<void, ihint*> changed_signal_t;

public:
    typedef value_t data_type;
    
    template<typename owner_t> property_stub(owner_t& Owner){}
    const value_t pipeline_value() const {return value_t();}
    changed_signal_t& changed_signal(){return m_changed_signal;}

private:
    changed_signal_t m_changed_signal = changed_signal_t();
};

} // namespace tests
} // namespace k3d
#endif // !K3D_TESTS_UNIT_TESTS_MOCKS_PROPERTY_STUB_H

