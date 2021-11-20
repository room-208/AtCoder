#include <chrono>
#include <iostream>
#include <istream>
#include <queue>
#include <random>
#include <tuple>
#include <vector>

constexpr size_t K = 60;

struct InputData {
 public:
  size_t D;
  std::vector<int> c;
  std::vector<std::vector<int>> s;
  InputData(size_t D, std::vector<int> c, std::vector<std::vector<int>> s)
      : D(D), s(s), c(c){};
};

namespace optimizer::io {

InputData ReadInput(std::istream &is) {
  size_t D;
  is >> D;

  std::vector<int> c(26);
  for (size_t i = 0; i < 26; i++) {
    is >> c[i];
  }

  std::vector<std::vector<int>> s(D, std::vector<int>(26));
  for (size_t i = 0; i < D; i++) {
    for (size_t j = 0; j < 26; j++) {
      is >> s[i][j];
    }
  }

  return InputData(D, c, s);
}

void WriteOutput(std::ostream &os, std::vector<int16_t> &t) {
  for (size_t i = 0; i < t.size(); i++) {
    os << t[i] + 1 << std::endl;
  }
}

}  // namespace optimizer::io

namespace optimizer::logic {

int GetDissatisfy(size_t d, InputData &input, std::vector<int16_t> &last) {
  int dissatisfy = 0;

  for (size_t i = 0; i < 26; i++) {
    dissatisfy += input.c[i] * (d - last[i]);
  }

  return dissatisfy;
}

int GetScore(InputData &input, std::vector<int16_t> &t) {
  int score = 0;
  std::vector<int16_t> last(26, 0);

  score = 0;
  for (size_t d = 1; d <= t.size(); d++) {
    score += input.s[d - 1][t[d - 1]];

    last[t[d - 1]] = d;

    score -= GetDissatisfy(d, input, last);
  }

  return score;
}

std::vector<int16_t> BeamSearch(InputData &input) {
  // ビームサーチのための優先度付きキュー
  std::priority_queue<std::pair<int, std::vector<int16_t>>> pq, pq_new;

  // 初期値
  pq.push(std::make_pair(0, std::vector<int16_t>()));

  // 全期間シミュレーション
  for (size_t d = 1; d <= input.D; d++) {
    // 解候補を全探索
    pq_new = std::priority_queue<std::pair<int, std::vector<int16_t>>>();
    for (size_t itr = 0; itr < K && !pq.empty(); itr++) {
      // 状態を確保
      const auto &state = pq.top();
      // 解候補に対してコンテストを全探索
      for (size_t i = 0; i < 26; i++) {
        std::vector<int16_t> t = state.second;
        t.push_back(static_cast<int16_t>(i));
        int score_new = GetScore(input, t);
        pq_new.push(std::make_pair(score_new, std::move(t)));
      }
      pq.pop();
    }

    pq = std::move(pq_new);
  }

  return pq.top().second;
}

}  // namespace optimizer::logic

namespace optimizer {

void CalAns(std::istream &is, std::ostream &os) {
  // 入力データを読み込む
  InputData inputdata = io::ReadInput(is);

  // ビームサーチで解を探索
  std::vector<int16_t> t = logic::BeamSearch(inputdata);

  // 出力を書き出す
  io::WriteOutput(os, t);
}

}  // namespace optimizer

int main() {
  optimizer::CalAns(std::cin, std::cout);
  return 0;
}