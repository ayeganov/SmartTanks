#include "globals.h"
#include "neuralnet.h"
#include "utils.h"

#include <numeric>
#include <stdexcept>

Neuron::Neuron(int num_inputs)
 : m_num_inputs(num_inputs),
   m_weights()
{
    // adding 1 extra weight to account for the bias
    for(int i = 0; i < num_inputs + 1; ++i)
    {
        m_weights.append(rand_float_n1_to_1());
    }
}

double Neuron::process_input(QVector<double>& input)
{
    // subtract 1 to account for the bias unit
    if(m_num_inputs - 1!= input.size())
    {
        throw std::invalid_argument("Neuron input doesn't match number of weights.");
    }

    double neuron_output = std::inner_product(input.begin(), input.end(), m_weights.begin(), 0.0);
    // don't forget the bias weight
    auto bias_weight = m_weights.end();
    neuron_output += *(--bias_weight) * Globs::BIAS;
    return sigmoid(neuron_output, Globs::RESPONSE);
}

Layer::Layer(int num_neurons, int input_size)
 : m_num_neurons(num_neurons),
   m_neurons()
{
    for(int i = 0; i < num_neurons; ++i)
    {
        m_neurons.append(std::make_shared<Neuron>(input_size));
    }
}

QVector<double> Layer::process_input(QVector<double>& input)
{
    QVector<double> output;
    for(Neuron::Ptr n : m_neurons)
    {
        output.append(n->process_input(input));
    }
    return std::move(output);
}

NeuralNet::NeuralNet()
 : m_layers(),
   m_topology(Globs::TOPOLOGY),
   m_num_inputs(Globs::NUM_INPUTS),
   m_num_outputs(0),
   m_num_hidden_layers(0)
{
    if(m_topology.size())
    {
        int input_size = m_num_inputs;
        for(int layer_size : m_topology)
        {
            if(layer_size <= 0)
            {
                throw std::invalid_argument("Topology must contain positive integer values");
            }
            m_layers.append(std::make_shared<Layer>(layer_size, input_size));
            input_size = layer_size;
        }
    }
    else
    {
        throw std::invalid_argument("Topology must contain positive integer values");
    }
}

QVector<double> NeuralNet::process_input(QVector<double>& inputs)
{
    QVector<double> output = inputs;
    for(Layer::Ptr l : m_layers)
    {
        output = l->process_input(output);
    }
    return std::move(output);
}

Layer::NeuronVector NeuralNet::get_neurons() const
{
    Layer::NeuronVector neurons;
    for(Layer::Ptr l : m_layers)
    {
        for(Neuron::Ptr n : l->m_neurons)
        {
            neurons.append(n);
        }
    }
    return std::move(neurons);
}
