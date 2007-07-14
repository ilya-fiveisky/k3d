// K-3D
// Copyright (c) 1995-2007, Timothy M. Shead
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
// License along with this program; if not, read to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

/** \file
	\author Timothy M. Shead
*/

#include "graph_operations.h"

#include <k3dsdk/ngui/document_state.h>

#include <k3dsdk/graph.h>

#include <boost/assign/list_of.hpp>
#include <boost/graph/circle_layout.hpp>
#include <boost/graph/connected_components.hpp>
#include <boost/graph/fruchterman_reingold.hpp>
#include <boost/graph/gursoy_atun_layout.hpp>
#include <boost/graph/random_layout.hpp>
#include <boost/random/mersenne_twister.hpp>

using namespace libk3dngui;

namespace module
{

namespace ngui_pipeline
{

namespace detail
{

class position_map
{
public:
	struct point_proxy
	{
		double x;
		double y;
	};

	position_map(k3d::typed_array<k3d::point2>& Storage) :
		storage(Storage)
	{
	}

	point_proxy& operator[](const size_t Index)
	{
		return reinterpret_cast<point_proxy&>(storage[Index]);
	}

private:
	k3d::typed_array<k3d::point2>& storage;
};

template<typename storage_t>
class property_map
{
public:
	typedef typename storage_t::size_type key_type;
	typedef typename storage_t::value_type value_type;
	typedef typename storage_t::reference reference;
	typedef boost::lvalue_property_map_tag category;

	property_map(storage_t& Storage) :
		storage(Storage)
	{
	}

	storage_t& storage;
};

template<typename property_map_t>
void put(property_map_t& Map, typename property_map_t::key_type Key, typename property_map_t::value_type Value)
{
	Map.storage[Key] = Value;
}

} // namespace detail

void create_graph(document_state& DocumentState, k3d::graph& Graph)
{
	const k3d::nodes_t nodes = DocumentState.document().nodes().collection();

	boost::shared_ptr<k3d::graph::topology_t> topology(new k3d::graph::topology_t());
	boost::shared_ptr<k3d::graph::strings_t> vertex_label(new k3d::graph::strings_t());

	// Insert nodes ...
	std::map<k3d::inode*, size_t> node_map;
	for(k3d::nodes_t::const_iterator node = nodes.begin(); node != nodes.end(); ++node)
	{
		size_t vertex_descriptor = boost::add_vertex(*topology);
		node_map[*node] = vertex_descriptor;
		vertex_label->push_back((*node)->name());
	}

	// Insert edges ...
	for(k3d::nodes_t::const_iterator node = nodes.begin(); node != nodes.end(); ++node)
	{
		if(k3d::iproperty_collection* const property_collection = dynamic_cast<k3d::iproperty_collection*>(*node))
		{
			const k3d::iproperty_collection::properties_t properties = property_collection->properties();
			for(k3d::iproperty_collection::properties_t::const_iterator property = properties.begin(); property != properties.end(); ++property)
			{
				if(typeid(k3d::inode*) == (*property)->property_type())
				{
					if(k3d::inode* const referenced_node = boost::any_cast<k3d::inode*>((*property)->property_value()))
					{
						boost::add_edge(node_map[referenced_node], node_map[*node], *topology);
//								stream << " [style=dotted,label=\"" << escaped_string((*property)->property_name()) << "\"]\n";
					}
				}
			}
		}
	}

	const k3d::idag::dependencies_t dependencies = DocumentState.document().dag().dependencies();
	for(k3d::idag::dependencies_t::const_iterator dependency = dependencies.begin(); dependency != dependencies.end(); ++dependency)
	{
		if(dependency->first && dependency->first->property_node() && dependency->second && dependency->second->property_node())
		{
			boost::add_edge(node_map[dependency->second->property_node()], node_map[dependency->first->property_node()], *topology);
//					stream << " [headlabel=\"" << escaped_string(dependency->first->property_name()) << "\" taillabel=\"" << escaped_string(dependency->second->property_name()) << "\"]\n";
		}
	}

	Graph.topology = topology;
	Graph.vertex_data["label"] = vertex_label;
}

void connected_components(k3d::graph& Graph)
{
	assert_not_implemented();
/*
	return_if_fail(Graph.topology);

	const k3d::graph::topology_t& topology = *Graph.topology;
	boost::shared_ptr<k3d::graph::indices_t> vertex_component(new k3d::graph::indices_t(boost::num_vertices(topology)));

	detail::property_map<k3d::graph::indices_t> component_map(*vertex_component);
	boost::connected_components(topology, component_map);

	Graph.vertex_data["component"] = vertex_component;
*/
}

void circular_layout(k3d::graph& Graph)
{
	return_if_fail(Graph.topology);

	const k3d::graph::topology_t& topology = *Graph.topology;
	boost::shared_ptr<k3d::graph::points_t> vertex_position(new k3d::graph::points_t(boost::num_vertices(topology)));

	detail::position_map position_map(*vertex_position);
	boost::circle_graph_layout(topology, position_map, 0.5);

	Graph.vertex_data["position"] = vertex_position;
}

void random_layout(k3d::graph& Graph)
{
	return_if_fail(Graph.topology);

	const k3d::graph::topology_t& topology = *Graph.topology;
	boost::shared_ptr<k3d::graph::points_t> vertex_position(new k3d::graph::points_t(boost::num_vertices(topology)));

	detail::position_map position_map(*vertex_position);
	boost::mt19937 rng;
	boost::random_graph_layout(topology, position_map, 0.0, 1.0, 0.0, 1.0, rng);
//			boost::fruchterman_reingold_force_directed_layout(topology, position_map, 1.0, 1.0);

	Graph.vertex_data["position"] = vertex_position;
}

void space_filling_layout(k3d::graph& Graph)
{
	assert_not_implemented();
/*
	return_if_fail(Graph.topology);

	const k3d::graph::topology_t& topology = *Graph.topology;
	boost::shared_ptr<k3d::graph::points_t> vertex_position(new k3d::graph::points_t(boost::num_vertices(topology)));

	detail::position_map position_map(*vertex_position);
	boost::gursoy_atun_layout(topology, boost::square_topology<>(), position_map);

	Graph.vertex_data["position"] = vertex_position;
*/
}

} // namespace ngui_pipeline

} // namespace module

