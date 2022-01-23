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
  cin.tie(nullptr);                                                            \
  cout.tie(nullptr);                                                           \
  ios_base::sync_with_stdio(false);
const int D = 100; // popultion size
const int G = 10;  // generation

string fun[2] = {"add", "mul"};    //  function
string ter[3] = {"1", "x", "x^2"}; // terminal

vector<vector<double>> Data(10000, vector<double>(11, 0));
void readData(string fileIndex) {
  string filename = "SRN" + fileIndex + ".csv";
  freopen(filename.c_str(), "r", stdin);
  char ch;
  FOR(i, 0, 10000) {
    FOR(j, 0, 10) { cin >> Data[i][j] >> ch; }
    cin >> Data[i][10];
  }
}

bool isInRate(int tar) {
  int rate = rand() % 100;
  return rate < tar;
}

struct Tree {
  string data;
  Tree *lc, *rc;
  Tree() : data(""), lc(nullptr), rc(nullptr) {}
};

int getSize(Tree *node) {
  if (node == nullptr) {
    return 0;
  }
  return max(getSize(node->lc), getSize(node->rc)) + 1;
}

Tree *randomTree(Tree *node, int depth) {
  if (node == nullptr) {
    node = new Tree();
  }
  if (depth != 0 && isInRate(60)) {
    node->data = fun[rand() % 2];
    node->lc = randomTree(node->lc, depth - 1);
    node->rc = randomTree(node->rc, depth - 1);
  } else {
    node->data = ter[rand() % 3];
    node->lc = node->rc = nullptr;
  }
  return node;
}

Tree *mutationTree(Tree *node) {
  if (node == nullptr) {
    return node;
  }
  int rate = rand() % 100;
  if (rate < 40) {
    node = randomTree(node, 3);
  } else if (rate < 70) {
    node->lc = mutationTree(node->lc);
  } else {
    node->rc = mutationTree(node->rc);
  }
  return node;
}

bool outputMode = false;
void crossOverTrees(Tree *&node1, Tree *&node2, int step) {
  if (step == 0) {
    int rate = rand() % 100;
    if (node1 == nullptr || node1->lc == nullptr || rate < 40) {
      crossOverTrees(node1, node2, 1);
    } else if (rate < 70) {
      crossOverTrees(node1->lc, node2, 0);
    } else {
      crossOverTrees(node1->rc, node2, 0);
    }
  } else {
    int rate = rand() % 100;
    if (node2 == nullptr || node2->lc == nullptr || rate < 40) {
      node1->rc = node2;
    } else if (rate < 70) {
      crossOverTrees(node1, node2->lc, 1);
    } else {
      crossOverTrees(node1, node2->rc, 1);
    }
  }
  return;
}

void printTree(Tree *node) {
  if (node == nullptr) {
    return;
  }
  cout << "(";
  printTree(node->lc);
  cout << node->data;
  printTree(node->rc);
  cout << ")";
}

double calcTree(Tree *node, int idx) {
  if (node->data == "1") {
    return 1;
  }
  if (node->data == "x") {
    double res = 0;
    FOR(i, 0, 10) res += Data[idx][i];
    return res;
  }
  if (node->data == "x^2") {
    double res = 0;
    FOR(i, 0, 10) res += Data[idx][i] * Data[idx][i];
    return res;
  }
  if (node->data == "add") {
    double Lres = calcTree(node->lc, idx);
    double Rres = calcTree(node->rc, idx);
    return Lres + Rres;
  }
  if (node->data == "mul") {
    double Lres = calcTree(node->lc, idx);
    double Rres = calcTree(node->rc, idx);
    return Lres * Rres;
  }
  assert(0);
  return 0.0;
}

int totalCnt;
struct Individual {
  Tree *tree;
  double fitness;
  Individual() : tree(nullptr) {}
  bool operator<(const Individual &rhs) const { return fitness < rhs.fitness; }
  void calcFitness(int L, int R) {
    ++totalCnt;
    fitness = 0.0;
    FOR(i, L, R) {
      // cout << calcTree(tree, i) << ' ' << Data[i][10] << '\n';
      fitness += abs(calcTree(tree, i) - Data[i][10]);
    }
    // cout << fitness << '\n';
    fitness /= R - L;
    fitness = sqrt(fitness);
  }
};

bitset<D> isSelected;
int selection(int SZ) {
  int r;
  do {
    r = rand() % SZ;
  } while (isSelected[r]);
  isSelected[r] = true;
  // cout << "selected: " << r << '\n';
  return r;
}

vector<double> res(30);
int main(int argc, char *argv[]) {
  int seed = stoi(argv[1]);
  readData(string(argv[1]));
  string filename(argv[1]);
  filename = "406261597_" + filename + ".csv";
  freopen(filename.c_str(), "a", stdout);
  FOR(ti, 0, 30) {
    srand(ti);
    vector<Individual> population;
    totalCnt = 0;
    FOR(i, 0, D) // generate D individual
    {
      Individual ind;
      ind.tree = randomTree(ind.tree, 5);
      population.PB(ind);
    }
    FOR(gi, 0, G) {
      // cout << gi << '\n';
      if (gi == 53)
        outputMode = true;
      if (totalCnt + 100 > 50000) {
        break;
      }
      vector<Individual> parent = population, selected(2), tmp(2);
      isSelected.reset();
      for (int i = 0; i < D;) {
        // cout << i << '\n';
        if (i + 2 > D ||
            isInRate(100)) // 100 % for mutation, crossOver isn't work
        {
          // cout << "mutation\n";
          tmp[0] = parent[selection(D)];
          tmp[0].tree = mutationTree(tmp[0].tree);
          tmp[0].calcFitness(0, 7000);
          i += 1;
        } else {
          tmp[0] = parent[selection(D)];
          tmp[1] = parent[selection(D)];
          crossOverTrees(tmp[0].tree, tmp[1].tree, 0);
          tmp[0].calcFitness(0, 7000);
          i += 2;
        }
      }
      // surivor selection
      sort(population.begin(), population.end());
      population.resize(D);
      sort(population.begin(), population.end());
    }
    population[0].calcFitness(7000, 10000);
    res[ti] = population[0].fitness;
    printTree(population[0].tree);
    cout << '\n';
  }
  freopen("406261597.csv", "a", stdout);
  FOR(ti, 0, 30) { cout << fixed << res[ti] << ",\n"[ti == 30 - 1]; }
}
