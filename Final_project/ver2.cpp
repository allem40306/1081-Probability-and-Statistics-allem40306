/*
Representation: Real Value
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
const int MXN = 1000;
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
  cin.tie(nullptr);                                                            \
  cout.tie(nullptr);                                                           \
  ios_base::sync_with_stdio(false);
struct Mat {
  int N, M;
  double x[MXN];
  Mat() { memset(x, 0, sizeof(x)); }
  Mat(int _M, int _N) {
    M = _M;
    N = _N;
    FOR(i, 0, M) FOR(j, 0, N) x[i * M + j] = 0.0;
  }
  Mat(int _M, int _N, vector<double> arr) {
    M = _M;
    N = _N;
    int k = 0;
    FOR(i, 0, M) FOR(j, 0, N) x[i * M + j] = arr[k++];
  }
};

Mat operator*(Mat lhs, Mat rhs) {
  Mat res(lhs.M, rhs.N);
  assert(lhs.N == rhs.M);
  FOR(i, 0, lhs.M) FOR(j, 0, rhs.N) FOR(k, 0, lhs.N) {
    res.x[i * lhs.M + j] += lhs.x[i * lhs.M + k] * rhs.x[k * rhs.M + j];
  }
  return res;
}

Mat operator*(Mat mat, double c) {
  Mat res(mat.M, mat.N);
  FOR(i, 0, mat.M)
  FOR(j, 0, mat.N) res.x[i * mat.M + j] = mat.x[i * mat.M + j] * c;
  return res;
}

Mat operator*(double c, Mat mat) { return mat * c; }

Mat operator+(Mat lhs, Mat rhs) {
  Mat res(lhs.M, lhs.N);
  assert(lhs.M == rhs.M || lhs.N == rhs.N);
  FOR(i, 0, lhs.M) FOR(j, 0, rhs.N) {
    res.x[i * lhs.M + j] = lhs.x[i * lhs.M + j] + rhs.x[i * lhs.M + j];
  }
  return res;
}

Mat operator-(Mat lhs, Mat rhs) { return lhs + (-1 * rhs); }

Mat Mul(Mat lhs, Mat rhs) {
  Mat res(lhs.M, lhs.N);
  assert(lhs.M == rhs.M || lhs.N == rhs.N);
  FOR(i, 0, lhs.M) FOR(j, 0, rhs.N) {
    res.x[i * lhs.M + j] = lhs.x[i * lhs.M + j] * rhs.x[i * lhs.M + j];
  }
  return res;
}

vector<double> reshapeTmp;
Mat reshape(Mat mat, int _M, int _N) {
  assert(mat.M * mat.N == _M * _N);
  Mat res(_M, _N);
  reshapeTmp.clear();
  FOR(i, 0, mat.M)
  FOR(j, 0, mat.N) { reshapeTmp.push_back(mat.x[i * mat.M + j]); }
  int cnt = 0;
  FOR(i, 0, res.M)
  FOR(j, 0, res.N) { res.x[i * res.M + j] = reshapeTmp[cnt++]; }
  return res;
}

Mat T(Mat mat) {
  Mat res(mat.N, mat.M);
  FOR(i, 0, mat.M)
  FOR(j, 0, mat.N) { res.x[j * res.M + i] = mat.x[i * mat.M + j]; }
  return res;
}

void output(string name, Mat mat) {
  cout << name << '\n';
  cout << mat.M << ' ' << mat.N << '\n';
  FOR(i, 0, mat.M)
  FOR(j, 0, mat.N) cout << mat.x[i * mat.M + j] << " \n"[j == mat.N - 1];
}

Mat f(Mat mat) {
  FOR(i, 0, mat.M)
  FOR(j, 0, mat.N) {
    mat.x[i * mat.M + j] = 1.0 / (1 + exp(-mat.x[i * mat.M + j]));
  }
  return mat;
}

Mat abs(Mat mat) {
  FOR(i, 0, mat.M)
  FOR(j, 0, mat.N) { mat.x[i * mat.M + j] = abs(mat.x[i * mat.M + j]); }
  return mat;
}

double max(Mat mat) {
  double res = mat.x[0];
  FOR(i, 0, mat.M)
  FOR(j, 0, mat.N) { res = max(res, mat.x[i * mat.M + j]); }
  return res;
}

Mat activation(Mat mat) {
  FOR(i, 0, mat.M)
  FOR(j, 0, mat.N) {
    mat.x[i * mat.M + j] = mat.x[i * mat.M + j] * (1 - mat.x[i * mat.M + j]);
  }
  return mat;
}

int maxClass(Mat mat) {
  assert(mat.N == 1);
  int res = 0;
  FOR(i, 1, mat.M) {
    if (mat.x[res * mat.M] < mat.x[i * mat.M]) {
      res = i;
    }
  }
  return res;
}

struct Data {
  vector<double> p, t;
};

vector<Data> training, testing;

const int numOfInput = 4;
const int numOfOutput = 3;
const int numOfNeroun = 1;
double alpha = 0.1;
const int end_Epoch = 100;

Mat w1(numOfNeroun, numOfInput);
Mat b1(numOfNeroun, 1);
Mat w2(numOfOutput, numOfNeroun);
Mat b2(numOfOutput, 1);

void readData() {
  freopen("iris_training_data.txt", "r", stdin);
  string s;
  Data tmp;
  training.clear();
  testing.clear();
  tmp.p.resize(4);
  tmp.t.resize(3);
  int cnt = 0;
  while (cin >> tmp.p[0]) {
    FOR(i, 1, 4) { cin >> tmp.p[i]; }
    cin >> s;
    tmp.t[0] = tmp.t[1] = tmp.t[2] = 0.1;
    if (s == "setosa") {
      tmp.t[0] = 0.9;
    } else if (s == "versicolor") {
      tmp.t[1] = 0.9;
    } else {
      tmp.t[2] = 0.9;
    }
    if (cnt < 120)
      training.push_back(tmp);
    else
      testing.push_back(tmp);
    ++cnt;
  }
}

void trainData() {
  int epoch = 0;
  while (true) {
    ++epoch;
    FOR(ti, 0, training.size()) {
      Mat p = Mat(numOfInput, 1, training[ti].p);
      Mat t = Mat(numOfOutput, 1, training[ti].t);
      Mat ah1 = reshape(f(w1 * p + b1), numOfNeroun, 1);
      Mat o = reshape(f(w2 * ah1 + b2), numOfOutput, 1);
      Mat d2 = Mul((t - o), reshape(activation(o), numOfOutput, 1));
      Mat d1 = Mul(T(w2) * d2, reshape(activation(ah1), numOfNeroun, 1));
      w2 = w2 + (2 * alpha * (d2 * ah1));
      b2 = b2 + (2 * alpha * d2);
      w1 = w1 + (2 * alpha * (d1 * reshape(p, 1, numOfInput)));
      b1 = b1 + (2 * alpha * d1);
    }
    // Mat totalError(numOfOutput, 1);
    // Mat p, t, ah1, o;
    // FOR(i, 0, 100) {
    //   p = Mat(numOfInput, 1, training[i].p);
    //   t = Mat(numOfOutput, 1, training[i].t);
    //   ah1 = reshape(f(w1 * p + b1), numOfNeroun, 1);
    //   o = reshape(f(w2 * ah1 + b2), numOfOutput, 1);
    //   totalError = totalError + abs(t - o);
    // }
    // cout << ' ' << (double)max(totalError) / 120.0 << '\n';
    if (epoch >= end_Epoch)
      break;
  }
}

double testData(vector<Data> const &data) {
  int ok = 0;
  FOR(ti, 0, data.size()) {
    Mat p = Mat(numOfInput, 1, training[ti].p);
    Mat t = Mat(numOfOutput, 1, training[ti].t);
    Mat ah1 = reshape(f(w1 * p + b1), numOfNeroun, 1);
    Mat o = reshape(f(w2 * ah1 + b2), numOfOutput, 1);
    if (maxClass(o) == maxClass(t)) {
      ++ok;
    }
  }
  double accurate_rate = ((double)ok / double(data.size())) * 100;
  return accurate_rate;
}

const int L = 40;
const int G = 100;
const int K = 2;
const int MU = 100;
const int chormosome_size = 11;
vector<double> x;

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
  int cnt = 0;
  FOR(i, 0, w1.M) FOR(j, 0, w1.N) { w1.x[i * w1.M + j] = chromosome[cnt++]; }
  FOR(i, 0, b1.M) FOR(j, 0, b1.N) { b1.x[i * b1.M + j] = chromosome[cnt++]; }
  FOR(i, 0, w2.M) FOR(j, 0, w2.N) { w2.x[i * w2.M + j] = chromosome[cnt++]; }
  FOR(i, 0, b2.M) FOR(j, 0, b2.N) { b2.x[i * b2.M + j] = chromosome[cnt++]; }
  trainData();
  fitness = testData(training);
}

void Individual::print_chromosome() {
  FOR(i, 0, chormosome_size) {
    cout << chromosome[i] << " \n"[i == chormosome_size - 1];
  }
}

bool Individual::operator<(const Individual &rhs) const {
  return fitness > rhs.fitness;
}

double generate_value() {
  return (-100 + ((double)(rand() % 20000) / (double)100));
}

double *generate_chromosome() {
  double *chromosome = (double *)calloc(chormosome_size, sizeof(double));
  FOR(i, 0, chormosome_size) { chromosome[i] = generate_value(); }
  return chromosome;
}

bitset<L> isSelected;
Individual selection(const vector<Individual> &parent) {
  int SZ = (int)parent.size();
  int r;
  do {
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

void crossover(Individual &lhs, Individual &rhs) // Uniform selection
{
  FOR(i, 0, chormosome_size) {
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


bool isInRate(int tar) {
  int rate = rand() % 100;
  return rate < tar;
}


void mutation(Individual &individual) // Random resetting
{
  FOR(i, 0, 5) if (isInRate(20)) {
    individual.chromosome[i] = generate_value();
  }
  FOR(i, 5, chormosome_size) if (isInRate(5)) {
    individual.chromosome[i] = generate_value();
  }
  return;
}

int main(int argc, char *argv[]) {
  int seed = stoi(argv[1]);
  srand(seed); // set random seed
  string filename(argv[1]);
  filename = "ver2_" + filename + ".txt";
  readData();
  freopen(filename.c_str(), "a", stdout);
  vector<Individual> population;
  FOR(i, 0, L) // generate L individual
  {
    //   cout << "individual " << i + 1 << '\n';
    double *chromosome = generate_chromosome();
    population.PB(Individual(chromosome));
  }
  FOR(i, 0, G) // generation
  {
    cout << "Generation" << i + 1 << '\n';
    vector<Individual> parent = population, selected(2), tmp(2);
    isSelected.reset();
    for (int i = 0; i < (int)parent.size(); i += 4) {
      FOR(i, 0, 2) // parent select
      {
        FOR(i, 0, K) { tmp[i] = selection(parent); }
        sort(tmp.begin(), tmp.end());
        selected[i] = tmp[0];
      }

      // crossover
      if (!isCrossover()) {
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
    population.resize(L);
    sort(population.begin(), population.end());
    population[0].print_chromosome();
    cout << population[0].fitness << '\n';
  }
}
