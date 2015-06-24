#ifndef GENALG
#define GENALG

#include "neuralnet.h"

#include <QVector>

struct Neuron;

struct Genome
{
    QVector<Neuron> neurons;
    double fitness;
    Genome(Genome&& other);
    Genome(const Genome& other);
    Genome() : neurons(), fitness(0.0) {}
    Genome(QVector<Neuron> neurons, double fitness) : neurons(neurons), fitness(fitness){}

    Genome& operator=(const Genome& other);
    // overload '<' for sorting
    friend bool operator<(const Genome& lhs, const Genome& rhs)
    {
        return lhs.fitness < rhs.fitness;
    }
};

class GenAlg
{
private:
    //************ Member vars ********************
    // Probability that a genome bits will mutate
    double m_mutation_rate;
    // Probability of crossover
    double m_crossover_rate;
    // Size of the population in each generation
    int m_population_size;

    double m_total_fitness;
    double m_best_fitness;
    double m_average_fitness;

    // Generation counter
    int m_generation;
    // All genomes representing ANN's are held here
    QVector<Genome> m_population;

    //************ Member Functions *****************
    /**
     * @brief Picks out two cross over points in the list of neurons.
     * The baby genome will receive neurons from mom in the region
     * outside of the cross over points, while inside the crossover
     * points baby will get dad's neurons.
     * @param mom - genome
     * @param dad - genome
     * @return new genome which is a cross of mom and dad
     */
    Genome cross_over(Genome& mom, Genome& dad);
    void mutate(Genome& genome);
    Genome& select_roulette();
    void grab_N_best(int N, int copies, QVector<Genome>& population) const;
    void calculate_stats();
    void reset();

public:
    GenAlg(double mutation_rate, double crossover_rate, int population_size);
    QVector<Genome> epoch(QVector<Genome> prev_generation);
    void increment_generation() { ++m_generation; }
    double best_fitness() const { return m_best_fitness; }
    double average_fitness() const { return m_average_fitness; }
    int generation() const { return m_generation; }
};

#endif // GENALG
