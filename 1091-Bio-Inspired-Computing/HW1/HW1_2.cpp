/*
Representation: Bit String
Crossover: Uniform
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
    bitset<L> chromosome;
    double fitness;
    Individual() {}
    Individual(bitset<L> _chromosome);
    void evaluate_fitness();
    bool operator<(const Individual &rhs) const;
};

Individual::Individual(bitset<L> _chromosome)
{
    chromosome = _chromosome;
    evaluate_fitness();
}

void Individual::evaluate_fitness()
{
    // 10 bits tot a Xi, Xi = -32 * 10 cnt(number of bit 1)
    x.clear();
    FOR(i, 0, 10)
    {
        int cnt = 0;
        FOR(j, 0, 10) if (chromosome[i * 10 + j]) { ++cnt; }
        x.PB(-32 + 6.4 * (double)cnt);
    }
    // Ackley’s function
    fitness = 20 + exp(1);
    double tmp1 = 0, tmp2 = 0;
    FOR(i, 0, x.size())
    {
        tmp1 += x[i] * x[i];
        tmp2 += cos(2 * acos(-1.0) * x[i]);
    }
    fitness -= 20 * exp(-0.2 * sqrt(tmp1 / double(10)));
    fitness -= exp(tmp2 / double(10));
    if (fitness < 1e-8) // error fix
    {
        fitness = 0;
    }
}

bool Individual::operator<(const Individual &rhs) const
{
    return fitness < rhs.fitness;
}

bitset<L> generate_chromosome()
{
    bitset<L> chromosome;
    FOR(i, 0, L) chromosome[i] = rand() % 2;
    return chromosome;
}

Individual selection(vector<Individual> &parent)
{
    int SZ = (int)parent.size();
    int r = rand() % SZ;
    Individual tmp = parent[r];
    parent.erase(parent.begin() + r);
    return tmp;
}

bool isCrossover() // pc = 0.9
{
    int rate = rand() % 100;
    return rate < 90;
}

void crossover(Individual &lhs, Individual &rhs) // Uniform selection
{
    int SZ = L;
    FOR(i, 0, SZ)
    {
        if (rand() % 2)
            continue;
        int tmp = lhs.chromosome[i];
        lhs.chromosome[i] = rhs.chromosome[i];
        rhs.chromosome[i] = tmp;
    }
    return;
}

bool isMutation() // pm = 0.1
{
    int rate = rand() % 100;
    return rate < 10;
}

void mutation(Individual &individual) // bit-filp
{
    FOR(i, 0, L) if (isMutation())
    {
        if (individual.chromosome[i])
        {
            individual.chromosome[i] = false;
        }
        else
        {
            individual.chromosome[i] = true;
        }
    }
    return;
}

vector<int> res(G);
int main()
{
    IOS;
    srand(time(nullptr)); // set random seed
    FOR(ti, 0, 30)
    {
        vector<Individual> population;
        FOR(i, 0, L) // generate L individual
        {
            bitset<L> chromosome = generate_chromosome();
            population.PB(Individual(chromosome));
        }
        FOR(i, 0, G) // generation
        {
            vector<Individual> parent = population, selected(2), tmp;
            while (!parent.empty())
            {
                FOR(i, 0, 2) // parent select
                {
                    tmp.clear();
                    FOR(i, 0, K) { tmp.PB(selection(parent)); }
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
            res[i] += population[0].fitness;
        }
    }
    FOR(i,0,G){cout << i << " " << res[i] / 30 << '\n';}
}
