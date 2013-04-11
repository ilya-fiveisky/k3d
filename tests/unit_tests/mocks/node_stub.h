#ifndef K3D_TESTS_UNIT_TESTS_MOCKS_NODE_STUB_H
#define	K3D_TESTS_UNIT_TESTS_MOCKS_NODE_STUB_H

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

#include <k3dsdk/idocument.h>
#include <k3dsdk/iproperty.h>
#include <k3dsdk/ipersistent.h>
#include <k3dsdk/iproperty_collection.h>
#include <k3dsdk/ipersistent_collection.h>
#include <k3dsdk/signal_system.h>
#include <k3dsdk/ipersistent.h>

namespace k3d
{
namespace tests
{

class node_stub : 
    public iproperty_collection, 
    public ipersistent_collection
{
public:
    node_stub(idocument& Document) : m_document(Document) {}
    virtual ~node_stub(){}
    
    idocument& document() {return m_document;}
	void register_property(iproperty& Property) {}
	void register_properties(const properties_t& Properties) {}
	void unregister_property(iproperty& Property) {}
	void unregister_properties(const properties_t& Properties) {}
	const properties_t& properties() {return m_properties;}
	sigc::connection connect_properties_changed_signal(const sigc::slot<void, ihint*>& Slot) {return sigc::connection();}

	void enable_serialization(const string_t& Name, ipersistent& Object) {}
	void disable_serialization(ipersistent& Object) {}
	const std::vector<std::pair<string_t, ipersistent*> > persistent_objects() {return std::vector<std::pair<string_t, ipersistent*> >();}

private:
    idocument& m_document;
    properties_t m_properties = properties_t();
};

} // namespace tests
} // namespace k3d
#endif // !K3D_TESTS_UNIT_TESTS_MOCKS_NODE_STUB_H

