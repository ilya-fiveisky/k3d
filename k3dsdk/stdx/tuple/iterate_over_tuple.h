#ifndef STDX_ITERATE_OVER_TUPLE_H
#define STDX_ITERATE_OVER_TUPLE_H

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

template <int I, int TSize, typename Tuple>
struct iterate_over_tuple_impl
    : public iterate_over_tuple_impl<I + 1, TSize, Tuple>
{
    template <typename Function>
        void operator () (const Function& f, Tuple& t)
        {
            f(std::get<I>(t));
            iterate_over_tuple_impl<I + 1, TSize, Tuple>::operator () (f, t);
        }
};

template <int I, typename Tuple>
struct iterate_over_tuple_impl<I, I, Tuple> {
    template <typename Function>
        void operator () (const Function& f, Tuple& t) {}
};

} // namespace detail

template <typename Function, typename... Args>
void iterate_over_tuple(const Function& f, std::tuple<Args...>& t)
{
    detail::iterate_over_tuple_impl<0, sizeof...(Args), std::tuple<Args...>>() (f, t);
}

} // namespace stdx

#endif // !STDX_ITERATE_OVER_TUPLE_H