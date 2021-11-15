#include <chrono>
#include <iostream>
#include <istream>
#include <random>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

constexpr double T0 = 2e3;
constexpr double T1 = 1e1;

struct InputData {
 public:
  size_t N;
  vector<int> a;
  vector<int> b;
  vector<int> c;
  vector<int> d;

  InputData(size_t N, vector<int> a, vector<int> b, vector<int> c,
            vector<int> d)
      : N(N), a(a), b(b), c(c), d(d){};
};

namespace io {

InputData InputReader(istream &is) {
  size_t N = 1000;

  vector<int> a(N);
  vector<int> b(N);
  vector<int> c(N);
  vector<int> d(N);
  for (size_t i = 0; i < N; i++) {
    is >> a[i] >> b[i] >> c[i] >> d[i];
  }

  return InputData(N, a, b, c, d);
}

void OutputWriter(ostream &os, vector<int> &r, vector<int> &x, vector<int> &y) {
  size_t m = r.size();
  os << m << " ";
  for (size_t i = 0; i < m; i++) {
    os << r[i] + 1 << " ";
  }
  os << endl;
  size_t n = x.size();
  os << n << " ";
  for (size_t i = 0; i < n; i++) {
    os << x[i] << " " << y[i] << " ";
  }
  os << endl;
}

}  // namespace io

namespace tool {

int GetDeriveryTime(vector<int> &x, vector<int> &y) {
  int T = 0;
  for (size_t i = 0; i < x.size() - 1; i++) {
    T += abs(x[i] - x[i + 1]) + abs(y[i] - y[i + 1]);
  }
  return T;
};

tuple<vector<int>, vector<int>, vector<int>, vector<int>,
      vector<tuple<int, int, bool>>>
Init(InputData &input) {
  vector<int> r(50);
  vector<int> s;

  // 商品を選ぶ
  unordered_set<int> st;
  for (size_t i = 0; i < 50; i++) {
    int candidate = rand() % 1000;

    while (st.count(candidate)) {
      candidate = rand() % 1000;
    }

    r[i] = candidate;
    st.insert(candidate);
  }

  for (size_t i = 0; i < 1000; i++) {
    if (!st.count(i)) {
      s.push_back(i);
    }
  }

  vector<int> x, y;
  vector<tuple<int, int, bool>> index;

  // 始点
  x.push_back(400);
  y.push_back(400);
  index.push_back(make_tuple(-1, -1, true));

  for (size_t i = 0; i < 50; i++) {
    // a,b
    x.push_back(input.a[r[i]]);
    y.push_back(input.b[r[i]]);
    index.push_back(make_tuple(2 * i + 2, r[i], true));
    // c,d
    x.push_back(input.c[r[i]]);
    y.push_back(input.d[r[i]]);
    index.push_back(make_tuple(2 * i + 1, r[i], false));
  }

  // 終点
  x.push_back(400);
  y.push_back(400);
  index.push_back(make_tuple(-1, -1, true));

  return make_tuple(r, s, x, y, index);
}

bool GetProb(int score, int score_new, double T) {
  double delta = score_new - score;

  if (delta <= 0) {
    return true;
  }

  double p = (double)rand() / (double)RAND_MAX;

  if (p < exp(-delta / T)) {
    return true;
  }

  return false;
}

bool GetSwap(size_t i, size_t j, vector<int> &x, vector<int> &y,
             vector<tuple<int, int, bool>> &index) {
  if (get<2>(index[i])) {
    if (get<2>(index[j])) {
      size_t next_i = static_cast<size_t>(get<0>(index[i]));
      size_t next_j = static_cast<size_t>(get<0>(index[j]));
      if (i < next_j && j < next_i) {
        swap(x[i], x[j]);
        swap(y[i], y[j]);
        swap(index[i], index[j]);
        return true;
      } else {
        return false;
      }
    } else {
      size_t next_i = static_cast<size_t>(get<0>(index[i]));
      size_t back_j = static_cast<size_t>(get<0>(index[j]));
      if (back_j < i && j < next_i) {
        swap(x[i], x[j]);
        swap(y[i], y[j]);
        swap(index[i], index[j]);
        return true;
      } else {
        return false;
      }
    }
  } else {
    if (get<2>(index[j])) {
      size_t back_i = static_cast<size_t>(get<0>(index[i]));
      size_t next_j = static_cast<size_t>(get<0>(index[j]));
      if (i < next_j && back_i < j) {
        swap(x[i], x[j]);
        swap(y[i], y[j]);
        swap(index[i], index[j]);
        return true;
      } else {
        return false;
      }
    } else {
      size_t back_i = static_cast<size_t>(get<0>(index[i]));
      size_t back_j = static_cast<size_t>(get<0>(index[j]));
      if (back_j < i && back_i < j) {
        swap(x[i], x[j]);
        swap(y[i], y[j]);
        swap(index[i], index[j]);
        return true;
      } else {
        return false;
      }
    }
  }
}

pair<int, int> SearchGoods(int r, vector<tuple<int, int, bool>> &index) {
  int i_ab = -1;
  int i_cd = -1;
  for (size_t i = 0; i < index.size(); i++) {
    if (get<1>(index[i]) == r) {
      if (get<2>(index[i])) {
        i_ab = i;
      } else {
        i_cd = i;
      }
    }
  }

  return make_pair(i_ab, i_cd);
}

}  // namespace tool

namespace logic {}  // namespace logic

int main() {
  // 入力データの読み込み
  InputData input = io::InputReader(cin);

  vector<int> r, s, x, y;
  vector<tuple<int, int, bool>> index;

  // r,x,yの初期化
  tie(r, s, x, y, index) = tool::Init(input);

  // 時間管理
  std::chrono::milliseconds deadline(1900);
  auto start = std::chrono::system_clock::now();
  auto end = std::chrono::system_clock::now();
  auto dur = end - start;

  // 焼きなまし
  double T = T1;
  int cnt = 0;
  int score = tool::GetDeriveryTime(x, y);

  while (dur < deadline) {
    cnt++;

    // 温度の更新
    if (cnt % 100 == 0) {
      auto end = std::chrono::system_clock::now();
      double time = (end - start).count() / (1000000. * deadline.count());
      T = pow(T0, 1. - time) * pow(T1, time);
    }

    // 順番の入れ替え
    if (rand() % 2 == 0) {
      // swapの対象
      size_t i = (rand() % 100) + 1;
      size_t j = (rand() % 100) + 1;

      if (tool::GetSwap(i, j, x, y, index)) {
        int score_new = tool::GetDeriveryTime(x, y);

        if (tool::GetProb(score, score_new, T)) {
          // 更新する
          score = score_new;
        } else {
          // 戻す
          swap(x[i], x[j]);
          swap(y[i], y[j]);
          swap(index[i], index[j]);
        }
      }
    }
    // 商品の入れ替え
    else {
      // swapの対象
      size_t i_r = (rand() % (int)r.size());
      size_t i_s = (rand() % (int)s.size());

      auto p = tool::SearchGoods(r[i_r], index);

      auto r_old = r[i_r];
      auto r_x_f = x[p.first];
      auto r_y_f = y[p.first];
      auto r_x_s = x[p.second];
      auto r_y_s = y[p.second];
      auto index_f = index[p.first];
      auto index_s = index[p.second];

      swap(r[i_r], s[i_s]);
      x[p.first] = input.a[r[i_r]];
      y[p.first] = input.b[r[i_r]];
      x[p.second] = input.c[r[i_r]];
      y[p.second] = input.d[r[i_r]];
      get<1>(index[p.first]) = r[i_r];
      get<1>(index[p.second]) = r[i_r];

      int score_new = tool::GetDeriveryTime(x, y);

      if (tool::GetProb(score, score_new, T)) {
        // 更新する
        score = score_new;
      } else {
        // 戻す
        swap(r[i_r], s[i_s]);
        x[p.first] = r_x_f;
        y[p.first] = r_y_f;
        x[p.second] = r_x_s;
        y[p.second] = r_y_s;
        index[p.first] = index_f;
        index[p.second] = index_s;
      }
    }

    // 時間の更新
    end = std::chrono::system_clock::now();
    dur = end - start;
  }

  // 出力データの書き出し
  io::OutputWriter(cout, r, x, y);
}