#ifndef K3DSDK_NODES_TYPEINFO_H
#define K3DSDK_NODES_TYPEINFO_H

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

#include <string>

#include <boost/concept_check.hpp>
#include <boost/concept/usage.hpp>

namespace k3d
{
namespace nodes
{

/// TypeInfo concept
template<class X, typename V> struct TypeInfo: boost::DefaultConstructible<X>
{
    BOOST_CONCEPT_USAGE(TypeInfo)
    {
        same_type(v, x.default_value);
    }
    
private:
    X x;
    V v;
    template <typename T>
    void same_type(T const&, T const&);
};

} // namespace nodes
} // namespace k3d

#endif // !K3DSDK_NODES_TYPEINFO_H
