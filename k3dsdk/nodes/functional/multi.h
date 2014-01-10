#ifndef K3DSDK_NODES_FUNCTIONAL_MULTI_H
#define K3DSDK_NODES_FUNCTIONAL_MULTI_H

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

#include <functional>
#include <tuple>
#include <type_traits>

#include <boost/concept/assert.hpp>

#include <k3d-i18n-config.h>
#include <k3dsdk/data.h>
#include <k3dsdk/document_plugin_factory.h>
#include <k3dsdk/node.h>
#include <k3dsdk/nodes/NodeInfo.h>
#include <k3dsdk/nodes/property.h>
#include <k3dsdk/stdx/functional.h>
#include <k3dsdk/stdx/tuple.h>
#include <k3dsdk/uuid.h>

namespace k3d
{
namespace nodes
{
namespace functional
{

template<class function_t, class output_property_t> class output_pair
{
    static_assert(std::is_default_constructible<function_t>::value, 
            "Function type should be default constructible");
public:
    typedef function_t function_type;
    typedef output_property_t output_property_type;
    
    template<typename owner_t> output_pair(owner_t& Owner) :
        m_function(function_t()),
        m_output_property(Owner) {}
    
    function_t& function() {return m_function;}
    output_property_t& output_property() {return m_output_property;}
    
private:
    function_t m_function;
    output_property_t m_output_property;
};

template<typename... ts> struct parameter_pack
{
    typedef std::tuple<ts...> params_type;
    typedef typename stdx::make_indexes<ts...>::type indexes_type;
    
    template<typename owner_t> parameter_pack(owner_t& Owner):
        m_params(stdx::variadic_id<ts>(Owner)...) {}
    
    params_type& params() {return m_params;}
    
private:
    params_type m_params;
};

/// Functional node template with multiple outputs (multiple functions).
template<
        class node_info_t,
        class outputs_t,
        class inputs_t> 
class multi : public node
{
    BOOST_CONCEPT_ASSERT((NodeInfo<node_info_t>));
    
    static_assert(std::tuple_size<typename outputs_t::params_type>::value > 0, 
            "Number of outputs should be > 0.");
    
    typedef multi<node_info_t, outputs_t, inputs_t> this_t;
	typedef node base;

    class connect_changed_signal
    {
        template<class input_property_t> struct make_slot
        {
            make_slot(input_property_t& InProp) : m_input_property(InProp) {}

            template<class output_t> 
            void operator()(output_t& Output) const
            {
                m_input_property.changed_signal().connect(Output.output_property().make_slot());
            }

        private:
            input_property_t& m_input_property;
        };
        
    public:
        connect_changed_signal(typename outputs_t::params_type& Outputs) : m_outputs(Outputs) {}

        template<class input_property_t> 
        void operator()(input_property_t& InProp) const
        {
            stdx::iterate_over_tuple(make_slot<input_property_t>(InProp), m_outputs);
        }

    private:
        typename outputs_t::params_type& m_outputs;
    };

    struct get_pipeline_value
    {
        template<class input_property_t> 
        const typename input_property_t::data_type operator()(input_property_t& InProp) const
        {
            return InProp.pipeline_value();
        }
    };

    class set_update_slot
    {
    public:
        set_update_slot(typename inputs_t::params_type& InProps) : m_inputs(InProps) {}

        template<class output_t> 
        void operator()(output_t& Output) const
        {
            typename inputs_t::params_type* inputsPointer = &m_inputs;
            Output.output_property().set_update_slot(
                [&Output, inputsPointer](
                    const std::vector<ihint*>& Hints, 
                    typename output_t::output_property_type::data_type& Out)
                {
                    Out = stdx::unwrap_and_forward(Output.function(), get_pipeline_value(), 
                            typename inputs_t::indexes_type(), *inputsPointer);
                });
        }

    private:
        typename inputs_t::params_type& m_inputs;
    };
    
public:
	multi(iplugin_factory& Factory, idocument& Document) :
		base(Factory, Document),
		m_inputs(*this),
        m_outputs(*this)
	{
            stdx::iterate_over_tuple(connect_changed_signal(m_outputs.params()), m_inputs.params());
            stdx::iterate_over_tuple(set_update_slot(m_inputs.params()), m_outputs.params());
	}
    
    /// Tuple of input properties.
    typename inputs_t::params_type& inputs() {return m_inputs.params();}
    
	static iplugin_factory& get_factory()
	{
        static node_info_t ni;
		static document_plugin_factory<multi> factory(
			ni.id,
			ni.name.c_str(),
			_(ni.description.c_str()),
			ni.category.c_str(),
			iplugin_factory::EXPERIMENTAL);

		return factory;
	}

protected:
    inputs_t m_inputs;
    outputs_t m_outputs;
};

} // namespace functional
} // namespace nodes
} // namespace k3d

#endif // !K3DSDK_NODES_FUNCTIONAL_MULTI_H

