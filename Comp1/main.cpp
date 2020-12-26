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
const double PI = acos(-1.0);
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define FOR(i, L, R) for (int i = L; i < (int)R; ++i)
#define FORD(i, L, R) for (int i = L; i > (int)R; --i)
#define IOS                                                                    \
  cin.tie(nullptr);                                                            \
  cout.tie(nullptr);                                                           \
  ios_base::sync_with_stdio(false);
const int D = 100; // popultion size
const int G = 500; // generation
const int K = 2;   // K-tourment
const int CR = 90; // CrossOver Rate
const int MR = 30; // Mutation Rate
vector<double> x;

class Problem {
private:
  int function_idx;
  double f1(double *arr) {
    double ret = 0, tmp;
    ret += arr[0];
    tmp = 0;
    FOR(i, 1, D) { tmp += arr[i] * arr[i]; }
    tmp *= 1000000;
    ret += tmp;
    return ret;
  }

  double f2(double *arr) {
    double ret = 0;
    FOR(i, 0, D) { ret += arr[i] * arr[i] - 10 * cos(2 * PI * arr[i]) + 10; }
    return ret;
  }

  double f3(double *arr) {
    double ret = 0;
    FOR(i, 0, D) { ret += pow(1000000, i / (D - 1)) * arr[i] * arr[i]; }
    return ret;
  }

  double f4(double *arr) {
    double ret = 0;
    FOR(i, 0, D - 1) {
      ret += 100 * (arr[i] * arr[i] - arr[i + 1]) *
                 (arr[i] * arr[i] - arr[i + 1]) +
             (arr[i] - 1) * (arr[i] - 1);
    }
    return ret;
  }

  double f5(double *arr) {
    double ret = 0, tmp;
    tmp = 0;
    FOR(i, 0, D) { tmp += arr[i] * arr[i] / 4000.0; }
    ret += tmp;
    tmp = 1;
    FOR(i, 0, D) { tmp *= cos(arr[i] / sqrt(i + 1)) + 1; }
    ret -= tmp;
    return ret;
  }

  double f6(double *arr) {
    double ret = 0, tmp;
    tmp = 0;
    FOR(i, 0, D) { tmp += arr[i] * arr[i]; }
    tmp /= (double)D;
    tmp = -0.2 * sqrt(tmp);
    tmp = -20 * exp(tmp);
    ret += tmp;
    tmp = 0;
    FOR(i, 0, D) { tmp += cos(2 * PI * arr[i]); }
    tmp /= (double)D;
    tmp = exp(tmp);
    ret -= tmp;
    ret += 20 + exp(1);
    return ret;
  }

  double f7(double *arr) {
    double ret = 0, tmp, tmp2;
    tmp = 0;
    FOR(i, 0, D) { tmp += arr[i] * arr[i]; }
    tmp = sqrt(sqrt(abs(tmp - (double)D)));
    ret += tmp;
    tmp = tmp2 = 0;
    FOR(i, 0, D) { tmp += arr[i] * arr[i]; }
    FOR(i, 0, D) { tmp2 += arr[i]; }
    ret += (0.5 * tmp + tmp2) / (double)D + 0.5;
    return ret;
  }

  double f8(double *arr) {
    double ret = 0, tmp;
    ret += 1000000 * arr[0] * arr[0];
    tmp = 0;
    FOR(i, 1, D) { tmp += arr[i] * arr[i]; }
    ret += tmp;
    return ret;
  }

  double f9(double *arr) {
    double ret = 0, tmp;
    ret += 418.9829 * (double)D;
    tmp = 0;
    FOR(i, 1, D) { tmp += sin(sqrt(abs(arr[i]))); }
    ret -= tmp;
    return ret;
  }

  double f10(double *arr) {
    double ret = 0, tmp;
    tmp = 0;
    FOR(i, 1, D) {
      FOR(j, 0, 20) {
        tmp += pow(0.5, j) * cos(2 * pow(3, j) * PI * (arr[i] + 0.5));
      }
    }
    ret += tmp;
    tmp = 0;
    FOR(j, 0, 20) { tmp += pow(0.5, j) * cos(pow(3, j) * PI); }
    ret -= (double)D * tmp;
    return ret;
  }

public:
  double selection(double *arr) {
    switch (function_idx) {
    case 1:
      return f1(arr);
      break;

    case 2:
      return f2(arr);
      break;

    case 3:
      return f3(arr);
      break;

    case 4:
      return f4(arr);
      break;

    case 5:
      return f5(arr);
      break;

    case 6:
      return f6(arr);
      break;

    case 7:
      return f7(arr);
      break;

    case 8:
      return f8(arr);
      break;

    case 9:
      return f9(arr);
      break;

    case 10:
      return f10(arr);
      break;

    default:
      break;
    }
    return 0.0;
  }
  void set_function(int idx) { function_idx = idx; }
};

Problem problem;

class Individual {
public:
  double *chromosome;
  double fitness;
  Individual() {}
  Individual(double *_chromosome);
  void evaluate_fitness();
  void print_chromosome();
  bool operator<(const Individual &rhs) const;
};

Individual::Individual(double *_chromosome) {
  chromosome = _chromosome;
  evaluate_fitness();
}

void Individual::evaluate_fitness() {
  fitness = problem.selection(chromosome);
  if (fitness < 1e-8) // error fix
  {
    fitness = 0;
  }
}

void Individual::print_chromosome() {
  FOR(i, 0, D) { cout << chromosome[i] << ",\n"[i == D - 1]; }
}

bool Individual::operator<(const Individual &rhs) const {
  return fitness < rhs.fitness;
}

double *generate_chromosome() {
  double *chromosome = (double *)calloc(D, sizeof(double));
  FOR(i, 0, D) {
    chromosome[i] = (-100 + ((double)(rand() % 20000) / (double)100));
  }
  return chromosome;
}

bitset<D> isSelected;
Individual selection(const vector<Individual> &parent) {
  int SZ = (int)parent.size();
  int r;
  do {
    r = rand() % SZ;
  } while (isSelected[r]);
  isSelected[r] = true;
  return parent[r];
}

bool isInRate(int tar) {
  int rate = rand() % 100;
  return rate < tar;
}

void crossover(Individual &lhs, Individual &rhs) // Whole arithmetic
{
  FOR(i, 0, D) {
    int tmp1 = 0.7 * lhs.chromosome[i] + 0.3 * rhs.chromosome[i];
    int tmp2 = 0.3 * lhs.chromosome[i] + 0.7 * rhs.chromosome[i];
    lhs.chromosome[i] = tmp1;
    rhs.chromosome[i] = tmp2;
  }
  return;
}

void mutation(Individual &individual) // Random resetting
{
  FOR(i, 0, D) if (!isInRate(MR)) {
    individual.chromosome[i] =
        (-100 + ((double)(rand() % 20000) / (double)100));
    ;
  }
  return;
}

vector<double> res(30);
int main(int argc, char *argv[]) {
  if (argc < 2) {
    cout << "too few argument!\n";
    return 0;
  }
  string filename(argv[1]);
  filename = "406261597_" + filename + ".csv";
  freopen(filename.c_str(), "a", stdout);
  int problem_idx = stoi(argv[1]);
  problem.set_function(problem_idx);
  FOR(ti, 0, 30) {
    srand(ti); // set random seed
    vector<Individual> population;
    FOR(i, 0, D) // generate L individual
    {
      double *chromosome = generate_chromosome();
      population.PB(Individual(chromosome));
    }
    FOR(i, 0, G) // generation
    {
      vector<Individual> parent = population, selected(2), tmp(2);
      isSelected.reset();
      for (int i = 0; i < (int)parent.size(); i += 4) {
        FOR(j, 0, 2) // parent select
        {
          FOR(k, 0, K) { tmp[k] = selection(parent); }
          sort(tmp.begin(), tmp.end());
          selected[j] = tmp[0];
        }

        // crossover
        if (!isInRate(CR)) {
          continue;
        }
        crossover(selected[0], selected[1]);
        // mutation
        FOR(i, 0, 2) {
          mutation(selected[i]);
          selected[i].evaluate_fitness();
          population.PB(selected[i]);
        }
      }
      // surivor selection
      sort(population.begin(), population.end());
      population.resize(D);
      sort(population.begin(), population.end());
    }
    res[ti] = population[0].fitness;
    population[0].print_chromosome();
  }
  freopen("406261597.csv", "a", stdout);
  FOR(ti, 0, 30) { cout << fixed << res[ti] << ",\n"[ti == 30 - 1]; }
}
