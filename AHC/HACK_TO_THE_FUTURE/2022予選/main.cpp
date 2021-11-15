#include <chrono>
#include <iostream>
#include <istream>
#include <random>
#include <unordered_map>
#include <unordered_set>
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

namespace io {

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

void StartTaskWriter(ostream &os, vector<int> &a, vector<int> &b) {
  size_t m = a.size();
  os << m << " ";
  for (size_t i = 0; i < m; i++) {
    os << a[i] + 1 << " " << b[i] + 1 << " ";
  }
  os << endl;
}

vector<int> EndTaskReader(istream &is, bool &flag) {
  size_t n;
  is >> n;

  vector<int> f;
  if (n == -1) {
    flag = false;
    return f;
  }

  f.reserve(n);
  for (size_t i = 0; i < n; i++) {
    int member;
    is >> member;
    f.push_back(member);
  }

  return f;
}

}  // namespace io

namespace tool {

int RandInt(int L, int U) { return rand() % (U - L) + L; };
double RandDouble(int L, int U) { return (double)(rand() % (U - L) + L); };

vector<vector<int>> InitTechniqueLevel(InputData &input) {
  size_t M = input.M;
  size_t K = input.K;
  vector<vector<int>> s(M, vector<int>(K));
  vector<vector<double>> s_(M, vector<double>(K));

  // 乱数シード
  random_device seed_gen;
  default_random_engine engine(seed_gen());

  // 平均0.0、標準偏差1.0で分布させる
  normal_distribution<> dist(0.0, 1.0);

  // s_dashの計算
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < K; j++) {
      s_[i][j] = fabs(dist(engine));
    }
  }

  // sの分母
  vector<double> standard(M, 0.);
  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < K; j++) {
      standard[i] += s_[i][j] * s_[i][j];
    }
  }
  for (size_t i = 0; i < M; i++) {
    standard[i] = sqrt(standard[i]);
  }

  for (size_t i = 0; i < M; i++) {
    for (size_t j = 0; j < K; j++) {
      s[i][j] = round(RandDouble(20, 60) * (s_[i][j] / standard[i]));
    }
  }

  return s;
}

int GetTaskWeight(InputData &input, vector<vector<int>> &s, size_t i,
                  size_t j) {
  size_t K = input.K;
  int w = 0;

  for (size_t k = 0; k < K; k++) {
    w += max(0, input.d[i][k] - s[j][k]);
  }

  return w;
}

void CalStartDate(vector<int> a, vector<int> b, int now_date,
                  vector<pair<int, int>> &start_date) {
  size_t m = a.size();
  for (size_t i = 0; i < m; i++) {
    start_date[a[i]] = make_pair(b[i], now_date);
  }
}

void CalEndDate(vector<int> &f, int now_date, vector<int> &end_date) {
  size_t n = f.size();
  for (size_t i = 0; i < n; i++) {
    end_date[f[i]] = now_date;
  }
}

void CalTaskDate(vector<int> &start_date, vector<int> &end_date,
                 vector<vector<int>> &t) {}

}  // namespace tool

namespace logic {

void UpdateTechniqueLevel(vector<vector<int>> &s, vector<vector<int>> &t,
                          InputData &input, size_t i, size_t j) {
  int w = tool::GetTaskWeight(input, s, i, j);

  while (w != t[i][j]) {
    if (w < t[i][j]) {
    } else if (w > t[i][j]) {
    }
  }
}

void InsertCanMember(vector<int> &f, unordered_set<int> &can_member) {
  for (size_t i = 0; i < f.size(); i++) {
    can_member.insert(f[i]);
  }
};
void EraseCanMember(vector<int> &a, unordered_set<int> &can_member) {
  for (size_t i = 0; i < a.size(); i++) {
    can_member.erase(a[i]);
  }
};
void InsertCanTask(){};
void EraseCanTask(){};

vector<pair<int, int>> SelectMember(InputData input, vector<vector<int>> &s,
                                    unordered_set<int> can_member,
                                    unordered_set<int> can_task) {
  vector<pair<int, int>> member_task;
  for (size_t i = 0; i < input.N; i++) {
    if (can_task.count(i)) {
      //　初期値
      int w = numeric_limits<int>::max();
      int member = -1;

      for (size_t j = 0; j < input.M; j++) {
        if (can_member.count(j)) {
          int w_ = tool::GetTaskWeight(input, s, i, j);
          if (w < w_) {
            member = j;
          }
        }
      }

      // 該当者がいるなら更新
      if (member != -1) {
        member_task.push_back(make_pair((int)i, member));
      }
    }
  }

  return member_task;
};

}  // namespace logic

int main() {
  // 入力データの読み込み
  InputData input = io::InputReader(cin);

  bool flag = true;
  vector<vector<int>> s = tool::InitTechniqueLevel(input);
  vector<pair<int, int>> start_date(input.M);
  vector<int> end_date(input.M);
  vector<int> a, b;
  vector<int> f;
  unordered_set<int> can_member;
  unordered_set<int> can_task;

  // 現在日時
  int now_date = 0;

  while (flag) {
    // 開始日の保存
    tool::CalStartDate(a, b, now_date, start_date);

    //　開始タスクの書き出し
    io::StartTaskWriter(cout, a, b);

    // 一日経過
    now_date++;

    // 終了タスクの読み込み
    f = io::EndTaskReader(cin, flag);

    // 終了日の保存
    tool::CalEndDate(f, now_date, end_date);
  }

  return 0;
}