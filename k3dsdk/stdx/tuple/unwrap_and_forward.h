#ifndef STDX_UNWRAP_AND_FORWARD_H
#define STDX_UNWRAP_AND_FORWARD_H

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

#include <tuple>

namespace stdx {
namespace detail {

template<int...> struct int_tuple {};

// make_indexes_impl is a helper for make_indexes
template<int I, typename IntTuple, typename... Types>
struct make_indexes_impl;

template<int I, int... Indexes, typename T, typename... Types>
struct make_indexes_impl<I, int_tuple<Indexes...>, T, Types...>
{
    typedef typename make_indexes_impl<I+1, int_tuple<Indexes..., I>, Types...>::type type;
};

template<int I, int... Indexes>
struct make_indexes_impl<I, int_tuple<Indexes...> > {
    typedef int_tuple<Indexes...> type;
};

} // namespace detail

template<typename... Types>
struct make_indexes : detail::make_indexes_impl<0, detail::int_tuple<>, Types...> { };

template<typename F, typename Convert, int... Indexes, typename... Args>
inline auto
unwrap_and_forward(const F& f, const Convert& convert, detail::int_tuple<Indexes...>, 
        std::tuple<Args...>& args) 
-> decltype(f(convert(std::get<Indexes>(args))...))
{
    return f(convert(std::get<Indexes>(args))...);
}

} // namespace stdx

#endif // !STDX_UNWRAP_AND_FORWARD_H