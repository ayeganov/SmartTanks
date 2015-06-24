#include "genalg.h"
#include "globals.h"
#include "utils.h"

#include <algorithm>

Genome::Genome(Genome&& other)
{
    neurons = std::move(other.neurons);
    fitness = other.fitness;
}

Genome::Genome(const Genome& other)
{
    neurons = other.neurons;
    fitness = other.fitness;
}

Genome& Genome::operator=(const Genome& other)
{
    if(this != &other)
    {
        neurons = other.neurons;
        fitness = other.fitness;
    }
    return *this;
}

GenAlg::GenAlg(double mutation_rate, double crossover_rate, int population_size)
 : m_mutation_rate(mutation_rate),
   m_crossover_rate(crossover_rate),
   m_population_size(population_size),
   m_total_fitness(0),
   m_best_fitness(0),
   m_average_fitness(0),
   m_generation(0),
   m_population()
{
}

void GenAlg::reset()
{
    m_total_fitness = 0;
    m_best_fitness = 0;
    m_average_fitness = 0;
}

QVector<Genome> GenAlg::epoch(QVector<Genome> prev_generation)
{
    m_population = prev_generation;
    reset();
    std::sort(m_population.begin(), m_population.end());

    calculate_stats();

    QVector<Genome> new_pop;

    grab_N_best(Globs::NUM_ELITES, Globs::NUM_COPIES, new_pop);

    while(new_pop.size() < m_population_size)
    {
        Genome mom = select_roulette();
        Genome dad = select_roulette();
        Genome baby = cross_over(mom, dad);
        mutate(baby);
        new_pop.append(baby);
    }
    return std::move(new_pop);
}

void GenAlg::mutate(Genome& genome)
{
    for(Neuron neuron : genome.neurons)
    {
        for(int i = 0; i < neuron.num_inputs + 1; ++i)
        {
            if(rand_float() < m_mutation_rate)
            {
                neuron.weights[i] += (rand_float_n1_to_1() * Globs::MAX_PERTURBATION);
            }
        }
    }
}

Genome& GenAlg::select_roulette()
{
    double slice = rand_float() * m_total_fitness;

    double fitness_accum;
    for(Genome& g : m_population)
    {
        fitness_accum += g.fitness;
        if(fitness_accum >= slice)
        {
            return g;
        }
    }
}

void GenAlg::grab_N_best(int N, int copies, QVector<Genome> &population) const
{
    while(N--)
    {
        for(int i = 0; i < copies; ++i)
        {
            // Genomes are sorted in ascending order based on their fitness.
            // Grab genomes from end, which holds the best genomes.
            population.append(m_population[m_population_size - 1 - N]);
        }
    }
}

void GenAlg::calculate_stats()
{
    m_total_fitness = 0.0;
    double best_so_far = 0.0;
    for(Genome& g : m_population)
    {
        if(g.fitness > best_so_far)
        {
            best_so_far = g.fitness;
            m_best_fitness = g.fitness;
        }
        m_total_fitness += g.fitness;
    }
    m_average_fitness = m_total_fitness / m_population_size;
}

Genome GenAlg::cross_over(Genome &mom, Genome &dad)
{
    Genome baby;
    if(rand_float() > m_crossover_rate || (&mom == &dad))
    {
        baby = mom;
        return baby;
    }
    int cp1 = rand_int(0, m_population.size() - 2);
    int cp2 = rand_int(cp1, m_population.size() - 1);

    for(int i = 0; i < mom.neurons.size(); ++i)
    {
       if(i < cp1 || i >= cp2)
       {
           baby.neurons.append(mom.neurons[i]);
       }
       else
       {
           baby.neurons.append(dad.neurons[i]);
       }
    }
    return baby;
}
