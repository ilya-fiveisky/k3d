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

#include <algorithm>
#include <exception>
#include <string>

#include <k3dsdk/data.h>
#include <k3dsdk/iproperty.h>
#include <k3dsdk/iwritable_property.h>
#include <k3dsdk/node.h>

namespace k3d
{
namespace tests
{

iproperty* get_property_by_name(node& Node, const std::string& Name)
{
    auto props = Node.properties();
    
    auto it = std::find_if(props.begin(), props.end(), 
            [Name](iproperty* p){return Name == p->property_name();});
    if(it == props.end())
    {
        throw std::invalid_argument( "There is no '" + Name + "' property!" );
    }
            
    return *it;
}

iwritable_property* get_writable_property_by_name(node& Node, const std::string& Name)
{
    auto result = dynamic_cast<iwritable_property*>(get_property_by_name(Node, Name));
    if(!result)
    {
        throw std::logic_error( "'" + Name + "' isn't iwritable_property!" );
    }
    return result;
}

} // namespace tests
} // namespace k3d

