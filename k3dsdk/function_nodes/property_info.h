#ifndef K3DSDK_FUNCTION_NODE_PROPERTY_INFO_H
#define K3DSDK_FUNCTION_NODE_PROPERTY_INFO_H

// K-3D
// Copyright (c) 1995-2009, Timothy M. Shead
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

#include <k3dsdk/data.h>

namespace k3d
{

namespace function_nodes
{
    
template<typename value_t> struct property_info
{
    property_info(const name_t& Name, const label_t& Label, const description_t& Description, const value_t& DefaultValue = value_t()):
    m_name(Name.name()), m_label(Label.label()), m_description(Description.description()), m_default_value(DefaultValue) {}
    
    virtual ~property_info(){}
    
    const char* name() const {return m_name;}
    const char* label() const {return m_label;}
    const char* description() const {return m_description;}
    value_t default_value() const {return m_default_value;}
    
private:
    const char* m_name;
    const char* m_label;
    const char* m_description;
    value_t m_default_value;
};

} //namespace function_node

} // namespace k3d

#endif // !K3DSDK_FUNCTION_NODE_PROPERTY_INFO_H

