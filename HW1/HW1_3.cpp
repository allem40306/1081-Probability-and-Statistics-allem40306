/*
Representation: Real Value
Crossover: Whole arithmetic
*/
#pragma GCC optimize("O2")
#include <bits/stdc++.h>
using namespace std;
using LL = long long;
using ULL = unsigned long long;
using PII = pair<int, int>;
using PLL = pair<LL, LL>;
using VI = vector<int>;
using VVI = vector<vector<int>>;
const int INF = 1e9;
const int MXN = 0;
const int MXV = 0;
const double EPS = 1e-9;
const int MOD = 1e9 + 7;
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define FOR(i, L, R) for (int i = L; i < (int)R; ++i)
#define FORD(i, L, R) for (int i = L; i > (int)R; --i)
#define IOS                                                                    \
    cin.tie(nullptr);                                                          \
    cout.tie(nullptr);                                                         \
    ios_base::sync_with_stdio(false);
const int L = 100;
const int G = 500;
const int K = 2;
const int MU = 100;
vector<double> x;

class Individual
{
  public:
    double *chromosome;
    double fitness;
    Individual() {}
    Individual(double *_chromosome);
    void evaluate_fitness();
    void print_chromosome();
    bool operator<(const Individual &rhs) const;
};

Individual::Individual(double *_chromosome)
{
    chromosome = _chromosome;
    evaluate_fitness();
}

void Individual::evaluate_fitness()
{
    // Ackley’s function
    fitness = 20 + exp(1);
    double tmp1 = 0, tmp2 = 0;
    FOR(i, 0, 10)
    {
        tmp1 += chromosome[i] * chromosome[i];
        tmp2 += cos(2 * acos(-1.0) * chromosome[i]);
    }
    fitness -= 20 * exp(-0.2 * sqrt(tmp1 / double(10)));
    fitness -= exp(tmp2 / double(10));
    if (fitness < 1e-8) // error fix
    {
        fitness = 0;
    }
}

void Individual::print_chromosome()
{
    FOR(i, 0, 10) { cout << chromosome[i] << " \n"[i == 9]; }
}

bool Individual::operator<(const Individual &rhs) const
{
    return fitness < rhs.fitness;
}

double *generate_chromosome()
{
    double *chromosome = (double *)calloc(10, sizeof(double));
    FOR(i, 0, 10)
    {
        chromosome[i] = (-32 + ((double)(rand() % 6400) / (double)100));
    }
    return chromosome;
}

bitset<L> isSelected;
Individual selection(const vector<Individual> &parent)
{
    int SZ = (int)parent.size();
    int r;
    do
    {
        r = rand() % SZ;
    } while (isSelected[r]);
    isSelected[r] = true;
    return parent[r];
}

bool isCrossover() // pc = 0.9
{
    int rate = rand() % 100;
    return rate < 90;
}

void crossover(Individual &lhs, Individual &rhs) // Whole arithmetic
{
    int SZ = 10;
    FOR(i, 0, SZ)
    {
        int tmp1 = 0.7 * lhs.chromosome[i] + 0.3 * rhs.chromosome[i];
        int tmp2 = 0.3 * lhs.chromosome[i] + 0.7 * rhs.chromosome[i];
        lhs.chromosome[i] = tmp1;
        rhs.chromosome[i] = tmp2;
    }
    return;
}

bool isMutation() // pm = 0.1
{
    int rate = rand() % 100;
    return rate < 10;
}

void mutation(Individual &individual) // Random resetting
{
    FOR(i, 0, 10) if (isMutation())
    {
        individual.chromosome[i] =
            (-32 + ((double)(rand() % 6400) / (double)100));
    }
    return;
}

vector<double> res(G);
int main()
{
    // IOS;
    srand(time(nullptr)); // set random seed
    FOR(ti, 0, 30)
    {
        vector<Individual> population;
        FOR(i, 0, L) // generate L individual
        {
            double *chromosome = generate_chromosome();
            population.PB(Individual(chromosome));
        }
        FOR(i, 0, G) // generation
        {
            vector<Individual> parent = population, selected(2), tmp(2);
            isSelected.reset();
            for (int i = 0; i < (int)parent.size(); i += 4)
            {
                FOR(i, 0, 2) // parent select
                {
                    FOR(i, 0, K) { tmp[i] = selection(parent); }
                    sort(tmp.begin(), tmp.end());
                    selected[i] = tmp[0];
                }

                // crossover
                if (!isCrossover())
                {
                    continue;
                }
                crossover(selected[0], selected[1]);
                // mutation
                FOR(i, 0, 2)
                {
                    mutation(selected[i]);
                    selected[i].evaluate_fitness();
                    population.PB(selected[i]);
                }
            }
            // surivor selection
            sort(population.begin(), population.end());
            population.resize(L);
            sort(population.begin(), population.end());
            // population[0].print_chromosome();
            res[i] += population[0].fitness;
        }
    }
    FOR(i, 0, G) { cout << i << " " << res[i] / 30 << '\n'; }
}
