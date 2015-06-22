#ifndef NEURALNET_H
#define NEURALNET_H

#include "globals.h"

#include <QVector>

#include <memory>

struct Neuron
{
    typedef std::shared_ptr<Neuron> Ptr;

    int m_num_inputs;
    QVector<double> m_weights;
    Neuron(int num_inputs);
    double process_input(QVector<double>&);
};

struct Layer
{
    typedef QVector<Neuron::Ptr> NeuronVector;
    typedef std::shared_ptr<Layer> Ptr;

    int m_num_neurons;
    NeuronVector m_neurons;
    Layer(int num_neurons, int input_size);
    QVector<double> process_input(QVector<double>&);
};

class NeuralNet
{
public:
    typedef QVector<Layer::Ptr> LayerVector;

    NeuralNet();

    // Returns all weights from the NN in a single vector
    QVector<double> get_weights() const;

    // Returns all neurons from the NN in a single vector
    Layer::NeuronVector get_neurons() const;

    // Return total number of weights in this NN
    int get_number_of_weights() const;

    // Replace the weights with new ones
    void set_weights(QVector<double>& weights);

    // Calculate the output from the vector of inputs
    QVector<double> process_input(QVector<double>& inputs);

    // calculate the points which define the individual neurons
    QVector<int> calculate_split_points() const;

private:
    LayerVector m_layers;
    QVector<int> m_topology;
    int m_num_inputs;
    int m_num_outputs;
    int m_num_hidden_layers;
};

#endif // NEURALNET_H
