#include <chrono>
#include <iostream>
#include <istream>
#include <random>
#include <tuple>
#include <vector>

const int INF_ll = 1000000000000000000LL;

struct InputData {
 public:
  size_t D;
  std::vector<int> c;
  std::vector<std::vector<int>> s;
  InputData(size_t D, std::vector<int> c, std::vector<std::vector<int>> s)
      : D(D), s(s), c(c){};
};

namespace optimizer::io {

InputData Input(std::istream &is) {
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

std::vector<int16_t> Inputschedule(size_t D, std::istream &is) {
  std::vector<int16_t> t(D);
  for (size_t i = 0; i < D; i++) {
    is >> t[i];
    t[i]--;
  }

  return t;
}

void Output(std::ostream &os, std::vector<int16_t> &t) {
  for (size_t i = 0; i < t.size(); i++) {
    os << t[i] + 1 << std::endl;
  }
}

void Output(std::ostream &os, std::vector<int> &score) {
  for (size_t i = 0; i < score.size(); i++) {
    os << score[i] << std::endl;
  }
}

}  // namespace optimizer::io

namespace optimizer::logic {

int CalDissatisfy(size_t d, InputData &inputdata, std::vector<int16_t> &last) {
  int dissatisfy = 0;

  for (size_t i = 0; i < 26; i++) {
    dissatisfy += inputdata.c[i] * (d - last[i]);
  }

  return dissatisfy;
}

int CalScore(InputData &inputdata, std::vector<int16_t> &t) {
  std::vector<int> score(inputdata.D + 1);
  std::vector<int16_t> last(26, 0);

  score[0] = 0;
  for (size_t d = 1; d <= inputdata.D; d++) {
    score[d] = score[d - 1] + inputdata.s[d - 1][t[d - 1]];

    last[t[d - 1]] = d;

    score[d] -= CalDissatisfy(d, inputdata, last);
  }

  // score.erase(score.begin());

  return score.back();
}

std::vector<int16_t> CalGreedyScore(InputData &inputdata) {
  std::vector<int16_t> t(inputdata.D);
  std::vector<int16_t> last(26, 0);

  for (size_t d = 1; d <= inputdata.D; d++) {
    int best = -INF_ll;
    int16_t best_i = -1;

    for (int i = 0; i < 26; i++) {
      // 貪欲
      int16_t last_tmp = last[i];
      last[i] = d;
      int tmp = inputdata.s[d - 1][i] - CalDissatisfy(d, inputdata, last);

      if (best < tmp) {
        best = tmp;
        best_i = i;
      }

      last[i] = last_tmp;
    }

    t[d - 1] = best_i;
    last[best_i] = d;
  }

  return t;
}

int Evaluate(InputData &inputdata, std::vector<int16_t> &t, size_t k) {
  int evaluate = 0;
  std::vector<int16_t> last(26, 0);

  // t.size()までの評価
  for (size_t d = 1; d <= t.size(); d++) {
    last[t[d - 1]] = d;
    evaluate +=
        inputdata.s[d - 1][t[d - 1]] - CalDissatisfy(d, inputdata, last);
  }

  // t.size()+1からt.size()+k日後までの不満足度
  for (size_t d = t.size() + 1; d <= t.size() + k; d++) {
    evaluate -= CalDissatisfy(d, inputdata, last);
  }

  return evaluate;
}

std::vector<int16_t> CalGreedyEvaluateScore(InputData &inputdata, size_t k) {
  std::vector<int16_t> t;

  for (size_t d = 1; d <= inputdata.D; d++) {
    int best = -INF_ll;
    int16_t best_i = -1;

    for (int16_t i = 0; i < 26; i++) {
      t.push_back(i);
      int tmp = Evaluate(inputdata, t, k);

      // 貪欲
      if (best < tmp) {
        best = tmp;
        best_i = i;
      }

      t.pop_back();
    }

    t.push_back(best_i);
  }

  return t;
}

std::vector<int16_t> CalGreedyEvaluateAllScore(InputData &inputdata) {
  int score = -INF_ll;
  std::vector<int16_t> t;

  for (size_t k = 0; k <= 26; k++) {
    // kのときの貪欲
    std::vector<int16_t> t_tmp = CalGreedyEvaluateScore(inputdata, k);
    int score_tmp = CalScore(inputdata, t_tmp);

    if (score_tmp > score) {
      score = score_tmp;
      t = t_tmp;
    }
  }

  return t;
}

std::vector<int16_t> HillClimb(InputData &inputdata) {
  std::chrono::milliseconds deadline(1900);
  auto start = std::chrono::system_clock::now();
  auto end = std::chrono::system_clock::now();
  auto dur = end - start;

  std::vector<int16_t> t;
  for (size_t i = 0; i < inputdata.D; i++) {
    t.push_back(rand() % 26);
  }
  int score = CalScore(inputdata, t);

  while (dur < deadline) {
    size_t d = (rand() % inputdata.D) + 1;
    int16_t q = rand() % 26;

    int16_t t_old = t[d - 1];
    t[d - 1] = q;
    int score_new = CalScore(inputdata, t);

    if (score > score_new) {
      t[d - 1] = t_old;
    } else {
      score = score_new;
    }

    end = std::chrono::system_clock::now();
    dur = end - start;
  }

  return t;
}

std::vector<int16_t> HillClimbMixSwap(InputData &inputdata) {
  std::chrono::milliseconds deadline(1900);
  auto start = std::chrono::system_clock::now();
  auto end = std::chrono::system_clock::now();
  auto dur = end - start;

  std::vector<int16_t> t = CalGreedyScore(inputdata);
  int score = CalScore(inputdata, t);

  while (dur < deadline) {
    if (rand() % 2 == 0) {
      size_t d = (rand() % inputdata.D) + 1;
      int16_t q = rand() % 26;

      int16_t t_old = t[d - 1];
      t[d - 1] = q;
      int score_new = CalScore(inputdata, t);

      if (score > score_new) {
        t[d - 1] = t_old;
      } else {
        score = score_new;
      }

    } else {
      size_t d1 = (rand() % inputdata.D) + 1;
      size_t d2 = (rand() % inputdata.D) + 1;

      std::swap(t[d1 - 1], t[d2 - 1]);
      int score_new = CalScore(inputdata, t);

      if (score > score_new) {
        std::swap(t[d1 - 1], t[d2 - 1]);
      } else {
        score = score_new;
      }
    }
    end = std::chrono::system_clock::now();
    dur = end - start;
  }

  return t;
}

bool GetProb(int delta, double T) {
  if (delta >= 0) {
    return true;
  }

  double p = (double)rand() / (double)RAND_MAX;
  double d = delta;

  if (p < exp(d / T)) {
    return true;
  }

  return false;
}

std::vector<int16_t> SA(InputData &inputdata) {
  std::chrono::milliseconds deadline(1900);
  auto start = std::chrono::system_clock::now();
  auto end = std::chrono::system_clock::now();
  auto dur = end - start;

  const double T0 = 2e3;
  const double T1 = 6e2;
  double T = T1;

  std::vector<int16_t> t = CalGreedyScore(inputdata);
  int score = CalScore(inputdata, t);

  int cnt = 0;
  while (dur < deadline) {
    cnt++;

    // 確率の更新
    if (cnt % 100 == 0) {
      auto end = std::chrono::system_clock::now();
      double time = (end - start).count() / (1000000. * deadline.count());
      T = pow(T0, 1 - time) * pow(T1, time);
    }

    //場合分け
    if (rand() % 2 == 0) {
      size_t d = (rand() % inputdata.D) + 1;
      int16_t q = rand() % 26;

      int16_t t_old = t[d - 1];
      t[d - 1] = q;
      int score_new = CalScore(inputdata, t);

      if (GetProb(score_new - score, T)) {
        score = score_new;
      } else {
        t[d - 1] = t_old;
      }

    } else {
      size_t d1 = (rand() % inputdata.D) + 1;
      size_t d2 = (rand() % inputdata.D) + 1;

      std::swap(t[d1 - 1], t[d2 - 1]);
      int score_new = CalScore(inputdata, t);

      if (GetProb(score_new - score, T)) {
        score = score_new;
      } else {
        std::swap(t[d1 - 1], t[d2 - 1]);
      }
    }
    end = std::chrono::system_clock::now();
    dur = end - start;
  }

  return t;
}

}  // namespace optimizer::logic

namespace optimizer {

void CalAns(std::istream &is, std::ostream &os) {
  InputData inputdata = io::Input(is);

  // std::vector<int16_t> t = io::Inputschedule(inputdata.D, is);
  // std::vector<int64_t> score = logic::CalScore(inputdata, t);

  std::vector<int16_t> t = logic::SA(inputdata);
  io::Output(os, t);
}

}  // namespace optimizer

int main() {
  optimizer::CalAns(std::cin, std::cout);
  return 0;
}