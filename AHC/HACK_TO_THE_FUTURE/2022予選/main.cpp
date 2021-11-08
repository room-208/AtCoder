#include <chrono>
#include <iostream>
#include <istream>
#include <random>
#include <vector>

using namespace std;

struct InputData {
 public:
  size_t N;
  size_t M;
  size_t K;
  size_t R;
  vector<vector<int>> d;
  vector<int> u;
  vector<int> v;
  InputData(size_t N, size_t M, size_t K, size_t R, vector<vector<int>> d,
            vector<int> u, vector<int> v)
      : N(N), M(M), K(K), R(R), d(d), u(u), v(v){};
};

namespace optimizer::io {
InputData InputReader(istream &is) {
  size_t N;
  size_t M;
  size_t K;
  size_t R;
  is >> N;
  is >> M;
  is >> K;
  is >> R;

  vector<vector<int>> d(N, vector<int>(K));
  for (size_t i = 0; i < N; i++) {
    for (size_t j = 0; j < K; j++) {
      is >> d[i][j];
    }
  }

  vector<int> u, v;
  for (size_t i = 0; i < R; i++) {
    is >> u[i] >> v[i];
    u[i]--;
    v[i]--;
  }

  return InputData(N, M, K, R, d, u, v);
}

void OutputWriter(ostream &os, vector<int16_t> &t) {
  for (size_t i = 0; i < t.size(); i++) {
    os << t[i] + 1 << endl;
  }
}

}  // namespace optimizer::io

namespace optimizer::logic {

int RandInt(int L, int U) { return rand() % (U - L) + L; };
double RandDouble(int L, int U) { return (double)(rand() % (U - L) + L); };

vector<vector<int>> RandGenerateS(InputData &input) {
  size_t M = input.M;
  size_t K = input.K;
  vector<vector<int>> s(M, vector<int>(K));
  vector<vector<double>> s_dash(M, vector<double>(K));

  // 乱数シード
  random_device seed_gen;
  default_random_engine engine(seed_gen());

  // 平均0.0、標準偏差1.0で分布させる
  normal_distribution<> dist(0.0, 1.0);

  // s_dashの計算
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < K; j++) {
      s_dash[i][j] = fabs(dist(engine));
    }
  }

  // sの分母
  vector<double> bunbo(M, 0.);
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < K; j++) {
      bunbo[i] += s_dash[i][j] * s_dash[i][j];
    }
  }
  for (size_t i = 0; i < M; i++) {
    bunbo[i] = sqrt(bunbo[i]);
  }

  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < K; j++) {
      s[i][j] = round(RandDouble(20, 60) * (s_dash[i][j] / bunbo[i]));
    }
  }

  return s;
}

int GetWij(InputData &input, vector<vector<int>> &s, size_t i, size_t j) {
  size_t K = input.K;
  int w = 0;

  for (size_t k = 0; k < K; k++) {
    w += max(0, input.d[i][k] - s[j][k]);
  }

  return w;
}

}  // namespace optimizer::logic

namespace optimizer {
void CalAns(istream &is, ostream &os) { InputData input = io::InputReader(is); }
}  // namespace optimizer

int main() {
  optimizer::CalAns(cin, cout);
  return 0;
}