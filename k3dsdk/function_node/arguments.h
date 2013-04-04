#ifndef K3DSDK_FUNCTION_NODE_ARGUMENTS_H
#define K3DSDK_FUNCTION_NODE_ARGUMENTS_H

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

#include <constexpr_string/costring.h>

namespace k3d
{

namespace function_node
{

namespace arguments
{
    
template<typename value_t> constexpr value_t id(const value_t& V) {return V;}

template<typename value_t> struct argument_base
{
    constexpr argument_base(const value_t& Value):
    m_value(Value) {}
    
    //virtual ~argument_base(){}
    
    constexpr value_t value() const {return m_value;}
    
private:
    value_t m_value;
};

typedef argument_base<constexpr_string::costring> string_argument;

struct name : string_argument
{
    constexpr name(const constexpr_string::costring& S) : string_argument(S) {}
};

struct label : string_argument
{
    constexpr label(const constexpr_string::costring& S) : string_argument(S) {}
};

struct description : string_argument
{
    constexpr description(const constexpr_string::costring& S) : string_argument(S) {}
};

struct category : string_argument
{
    constexpr category(const constexpr_string::costring& S) : string_argument(S) {}
};

} // namespace arguments

} // namespace function_node

} // namespace k3d

#endif // !K3DSDK_FUNCTION_NODE_ARGUMENTS_H

