#ifndef K3DSDK_FUNCTION_NODE_PROPERTY_H
#define K3DSDK_FUNCTION_NODE_PROPERTY_H

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

#include <k3d-i18n-config.h>
#include <k3dsdk/data.h>
#include <k3dsdk/inode.h>
#include <k3dsdk/node.h>
#include <k3dsdk/value_demand_storage.h>
#include <k3dsdk/pointer_demand_storage.h>
#include <k3dsdk/function_node/property_info.h>

#include <boost/mpl/logical.hpp>

#include <type_traits>

namespace k3d
{

namespace function_node
{

namespace detail
{
    struct in_tag final {in_tag() = delete;};
    struct out_tag final {out_tag() = delete;};
    
    template<typename value_t, typename tag, class Enable = void> struct property_;
    
    template<typename value_t> struct property_<value_t, in_tag, typename std::enable_if<boost::mpl::not_<std::is_pointer<value_t>>::value>::type>
    {
        typedef k3d::data::container_t<value_t, immutable_name, change_signal, with_undo, local_storage, no_constraint, writable_property, with_serialization> type;
    };
    
    template<> struct property_<inode*, in_tag>
    {
        typedef k3d::data::container_t<inode*, immutable_name, change_signal, with_undo, node_storage, no_constraint, node_property, with_serialization> type;
    };
    
    template<typename value_t> struct property_<value_t, out_tag, typename std::enable_if<boost::mpl::not_<std::is_pointer<value_t>>::value>::type>
    {
        typedef k3d::data::container_t<value_t, immutable_name, change_signal, no_undo, value_demand_storage, no_constraint, read_only_property, no_serialization> type;
    };

    template<> struct property_<inode*, out_tag>
    {
        typedef k3d::data::container_t<inode*, immutable_name, change_signal, no_undo, node_storage, no_constraint, node_property, no_serialization> type;
    };

    template<typename T> struct property_<T*, out_tag, typename std::enable_if<std::is_default_constructible<T>::value>::type>
    {
        typedef k3d::data::container_t<T*, immutable_name, change_signal, no_undo, pointer_demand_storage, no_constraint, read_only_property, no_serialization> type;
    };
    
    template<typename value_t, typename tag> using property_t = typename property_<value_t, tag>::type;

    template<typename value_t, property_info<value_t>& Info, typename tag> class property : 
        public property_t<value_t, tag>
    {
        typedef property_t<value_t, tag> base;
    public:
        typedef value_t value_type;
        property(node& Owner) :
            base(init_owner(Owner) + init_name(Info.name()) + init_label(_(Info.label())) 
                + init_description(_(Info.description())) + init_value(Info.default_value()))
        {
        }
    };

} // namespace detail

template<typename value_t> using input_property_t = detail::property_t<value_t, detail::in_tag>;

template<typename value_t, property_info<value_t>& Info> using input_property = 
    detail::property<value_t, Info, detail::in_tag>;

template<typename value_t> using output_property_t = detail::property_t<value_t, detail::out_tag>;

template<typename value_t, property_info<value_t>& Info> using output_property =
    detail::property<value_t, Info, detail::out_tag>;

} //namespace function_node

} // namespace k3d

#endif // !K3DSDK_FUNCTION_NODE_PROPERTY_H

