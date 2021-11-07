#include <iostream>
#include <istream>
#include <tuple>
#include <vector>

const int64_t INF_ll = 1000000000000000000LL;

struct InputData {
 public:
  size_t D;
  std::vector<int64_t> c;
  std::vector<std::vector<int64_t>> s;
  InputData(size_t D, std::vector<int64_t> c,
            std::vector<std::vector<int64_t>> s)
      : D(D), s(s), c(c){};
};

namespace optimizer::io {

InputData Input(std::istream &is) {
  size_t D;
  is >> D;

  std::vector<int64_t> c(26);
  for (size_t i = 0; i < 26; i++) {
    is >> c[i];
  }

  std::vector<std::vector<int64_t>> s(D, std::vector<int64_t>(26));
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

void Output(std::ostream &os, std::vector<int64_t> &score) {
  for (size_t i = 0; i < score.size(); i++) {
    os << score[i] << std::endl;
  }
}

}  // namespace optimizer::io

namespace optimizer::logic {

int64_t CalDissatisfy(size_t d, InputData &inputdata,
                      std::vector<int16_t> &last) {
  int64_t dissatisfy = 0;

  for (size_t i = 0; i < 26; i++) {
    dissatisfy += inputdata.c[i] * (d - last[i]);
  }

  return dissatisfy;
}

std::vector<int64_t> CalScore(InputData &inputdata, std::vector<int16_t> &t) {
  std::vector<int64_t> score(inputdata.D + 1);
  std::vector<int16_t> last(26, 0);

  score[0] = 0;
  for (size_t d = 1; d <= inputdata.D; d++) {
    score[d] = score[d - 1] + inputdata.s[d - 1][t[d - 1]];

    last[t[d - 1]] = d;

    score[d] -= CalDissatisfy(d, inputdata, last);
  }

  score.erase(score.begin());

  return score;
}

/*
std::vector<int16_t> CalGreedyScore(InputData &inputdata) {
  std::vector<int16_t> t(inputdata.D);
  std::vector<int16_t> last(26, 0);

  for (size_t d = 1; d <= inputdata.D; d++) {
    int64_t best = -INF_ll;
    int16_t best_i = -1;

    for (int i = 0; i < 26; i++) {
      // 貪欲
      int16_t last_tmp = last[i];
      last[i] = d;
      int64_t tmp = inputdata.s[d - 1][i] - CalDissatisfy(d, inputdata, last);

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
*/

int64_t Evaluate(InputData &inputdata, std::vector<int16_t> &t, size_t k) {
  int64_t evaluate = 0;
  std::vector<int16_t> last(26, 0);

  for (size_t d = 1; d <= inputdata.D; d++) {
    int64_t best = -INF_ll;
    int16_t best_i = -1;

    for (int i = 0; i < 26; i++) {
      // 貪欲
      int16_t last_tmp = last[i];
      last[i] = d;
      int64_t tmp = inputdata.s[d - 1][i] - CalDissatisfy(d, inputdata, last);

      if (best < tmp) {
        best = tmp;
        best_i = i;
      }

      last[i] = last_tmp;
    }

    t[d - 1] = best_i;
    last[best_i] = d;
  }
}

std::vector<int16_t> CalGreedyScore(InputData &inputdata) {
  std::vector<int16_t> t(inputdata.D);
  std::vector<int16_t> last(26, 0);

  for (size_t d = 1; d <= inputdata.D; d++) {
    int64_t best = -INF_ll;
    int16_t best_i = -1;

    for (int i = 0; i < 26; i++) {
      // 貪欲
      int16_t last_tmp = last[i];
      last[i] = d;
      int64_t tmp = inputdata.s[d - 1][i] - CalDissatisfy(d, inputdata, last);

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

}  // namespace optimizer::logic

namespace optimizer {

void CalAns(std::istream &is, std::ostream &os) {
  InputData inputdata = io::Input(is);

  // std::vector<int16_t> t = io::Inputschedule(inputdata.D, is);
  // std::vector<int64_t> score = logic::CalScore(inputdata, t);

  std::vector<int16_t> t = logic::CalGreedyScore(inputdata);

  io::Output(os, t);
}

}  // namespace optimizer

int main() {
  optimizer::CalAns(std::cin, std::cout);
  return 0;
}