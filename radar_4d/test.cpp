#include <iostream>
#include <string>

// 1. read_bin
// 2. adc or 1dfft（实数 -> 复数） vector<double>(3) or data[size]
// 3. 1dfft() -> 点云选取

// input:  binary file （param sys and input data and comensate_mat （ adc or
// 1dfft）） output: r, v, theta, snr, point_num

// 根据sysparam选择
// coarse
// fine

// libs: fft, blas

struct ParamSys {
  int type;
};

struct BinFile {
  ParamSys param_sys;
  float *data;
  float *mat;
};

BinFile get_info(std::string file) {
  BinFile bin_file;
  ParamSys sys;
  sys.type = 1;
  bin_file.param_sys = sys;
  return bin_file;
}

int main(int argc, char *argv[]) {
  // 1. get info
  auto bin_info = get_info("test");
  auto &param_sys = bin_info.param_sys;
  if (param_sys.type == 1) {
  } else {
  }
  // 2. deal
  // Result fun(Binfile &info);

  std::cout << param_sys.type << std::endl;
  return 0;
}
