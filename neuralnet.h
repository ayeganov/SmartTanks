#ifndef NEURALNET_H
#define NEURALNET_H

#include "genalg.h"
#include "globals.h"

#include <QVector>

#include <memory>

struct Genome;

struct Neuron
{
    typedef std::shared_ptr<Neuron> Ptr;

    int num_inputs;
    QVector<double> weights;
    Neuron() : num_inputs(0), weights() {}
    Neuron(int num_inputs);
    double process_input(QVector<double>&);
};

struct Layer
{
    typedef QVector<Neuron::Ptr> NeuronVector;
    typedef std::shared_ptr<Layer> Ptr;

    int m_num_neurons;
    NeuronVector neurons;
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

    // Return total number of weights in this NN
    int get_number_of_weights() const;

    // Replace the weights with new ones
    void set_weights(QVector<double>& weights);

    // Calculate the output from the vector of inputs
    QVector<double> process_input(QVector<double>& inputs);
    QVector<double> process_input(std::initializer_list<double> args);

    void increment_fitness(double amount = 1) { m_fitness += amount; }

    Genome get_genome() const;
    void set_genome(Genome& genome);

    double get_fitness() const { return m_fitness; }

private:
    LayerVector m_layers;
    QVector<int> m_topology;
    int m_num_inputs;
    int m_num_outputs;
    int m_num_hidden_layers;
    double m_fitness;
};

#endif // NEURALNET_H
