#include <iostream>
#include <random>

#include "nlohmann/json.hpp"
#include <openblas/cblas.h>
#include <plot-cpp/plot.hpp>

// RANDOM NUMBER GENERATION
int rmin = -1, rmax = 1;
std::random_device rd;
std::default_random_engine re = std::default_random_engine(rd());
std::uniform_real_distribution<float> urd =
    std::uniform_real_distribution<float>(rmin, rmax);
float rng() { return urd(re); }
////

float mean(std::vector<float> f) {
  int len = f.size();
  std::vector<float> ones(len, 1.0f);

  return cblas_sdot(len, f.data(), 1, ones.data(), 1) / len;
}

float sample_covariance(std::vector<float> f1, std::vector<float> f2) {
  int len = f1.size();
  std::vector<float> ones(len, 1.0f);

  // calculate means of vectors
  float mean_f1 = mean(f1);
  float mean_f2 = mean(f2);

  // intermediates for f1 and f2
  // f[n] = f[n] - mean_f
  cblas_saxpy(len, -1 * mean_f1, ones.data(), 1, f1.data(), 1);
  cblas_saxpy(len, -1 * mean_f2, ones.data(), 1, f2.data(), 1);

  // sum of element multiplication of f1 and f2
  float sum = cblas_sdot(len, f1.data(), 1, f2.data(), 1);

  return sum / (len - 1);
}

int main() {
  int len = 1e3;          // length of random walk
  float initial = 1000.f; // starting value for each walk

  // create x axis
  std::vector<float> x(len, 0.f);
  for (int i = 0; i < len; i++) {
    x[i] = i;
  }

  // create two rw for y axis
  std::vector<float> r1(len, initial), r2(len, initial);
  for (int i = 1; i < len; i++) {
    r1[i] = r1[i - 1] + rng();
    r2[i] = r2[i - 1] + rng();
  }

  int window_len = 50; // sample cov will consider the last 50 elements only
  std::vector<float> cov;
  std::vector<float> cov_ax;

  for (int i = 0; i < r1.size(); i += window_len) {
    cov.push_back(
        // sample_covariance(std::span<float>(r1).subspan(i, window_len),
        //                   std::span<float>(r2).subspan(i, window_len)));
        // SPAN PASSES BY REFERENCE IT SEEMS

        sample_covariance(
            std::vector<float>(r1.begin() + i, r1.begin() + i + window_len),
            std::vector<float>(r2.begin() + i, r2.begin() + i + window_len)));
    cov_ax.push_back(i + window_len);
  }

  nlohmann::json data_dict;
  data_dict["main_title"] = "Random Walks";

  data_dict["vp_title"] = "Value Plot";
  data_dict["vp_xlabel"] = "Time";
  data_dict["vp_ylabel"] = "Value";
  data_dict["vp_x"] = x;
  data_dict["vp_y1"] = r1;
  data_dict["vp_y2"] = r2;

  data_dict["cp_title"] = " Covariance Plot";
  data_dict["cp_xlabel"] = "Time";
  data_dict["cp_ylabel"] = "Covariance";
  data_dict["cp_x"] = cov_ax;
  data_dict["cp_y"] = cov;

  Plot plot_o("shaders/overlapped.py", data_dict.dump(), true);
  Plot plot_s("shaders/side_by_side.py", data_dict.dump(), true);

  return 0;
}