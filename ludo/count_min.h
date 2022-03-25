#ifndef STORAGE_LEVELDB_COUNT_MIN_H_
#define STORAGE_LEVELDB_COUNT_MIN_H_

#include <ctime>
#include <limits>
#include <cmath>
#include "util/hash.h"

namespace leveldb {

template <class Counter> 
class CountMinSketch {
public:
  explicit CountMinSketch (double ep, double gamma){
    if (!(0.009 <= ep && ep < 1)) { //eps must be in this range: [0.01, 1).
        exit(EXIT_FAILURE);
    } else if (!(0 < gamma && gamma < 1)) { //gamma must be in this range: (0,1).
        exit(EXIT_FAILURE);
    }
    
    ep_ = ep;
    gamma_ = gamma;
    total_ = 1;
    w_ = ceil(exp(1)/ep_);
    d_ = ceil(log10(1/gamma_)/log10(2));
    
    std::vector<Counter> tmp(w_); 
    Cnt_.clear();
    for (uint32_t i = 0; i < d_; i++){
        Cnt_.push_back(tmp);
    }
    // std::cout << "w and d are: " << w_ << " : " << d_ << std::endl;
  }
  explicit CountMinSketch (uint32_t w, uint32_t d, bool Width) {
    w_ = w;
    d_ = d;
    total_ = 1;
    
    std::vector<Counter> tmp(w_); 
    Cnt_.clear();
    for (uint32_t i = 0; i < d_; i++){
        Cnt_.push_back(tmp);
    }
    // std::cout << "w and d are: " << w_ << " : " << d_ << std::endl;
  }

  void Update (const char *item, const size_t n, Counter c) {
    total_ += c;
    uint32_t h = hashstr(item, n);
    const uint32_t delta = (h >> 17) | (h << 15);  // Rotate right 17 bits
    for (size_t j = 0; j < d_; j ++) {
        Cnt_[j][h % w_] += c;
        h += delta;
        if (Cnt_[j][h % w_] == 0) {
          Reset();
          break;  
        }
    }
  }

  Counter Estimate (const char *item, const size_t n) {
    Counter minval = std::numeric_limits<Counter>::max();
    uint32_t h = hashstr(item, n);
    const uint32_t delta = (h >> 17) | (h << 15);
    for (size_t j = 0; j < d_; j ++) {
        minval = minval < Cnt_[j][h % w_]? minval : Cnt_[j][h % w_];
        h += delta;
    }
    return minval;
  }

  double EstimateRate(const char *item, const size_t n) {
    Counter minval = std::numeric_limits<Counter>::max();
    uint32_t h = hashstr(item, n);
    const uint32_t delta = (h >> 17) | (h << 15);
    for (size_t j = 0; j < d_; j ++) {
        minval = minval < Cnt_[j][h % w_]? minval : Cnt_[j][h % w_];
        h += delta;
    }
    return minval/(double) total_;
  }

  void Reset () {
    total_ = 1;
    for (uint32_t i = 0; i < d_; i++) {
      Cnt_[i].assign(w_, 0);
    }
  }

  inline Counter totalcnt () {
      return total_;
  }

  inline uint32_t hashstr (const char *str, size_t n = 1) {
      return Hash(str, n, 0xbc9f1d34);
  }

  ~CountMinSketch() {};

private:
  // width, depth 
  uint32_t w_, d_;

  double ep_;
  double gamma_;
  
  uint64_t total_; 

  std::vector<std::vector<Counter>> Cnt_;
};
}

#endif
