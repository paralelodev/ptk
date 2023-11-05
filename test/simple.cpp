#include "c++/Generator.h"

using namespace ptk;
using namespace std;

int main() {
  string Name = "test";
  ComputingDistribution CU = {ComputingUnit::CPU, ComputingUnit::THREAD};
  std::vector<std::pair<std::string, Range<int>>> Ranges = {
      {"i", {0, 100, 1, RangeType::SPACE}}};

  Kernel<int> K(Name, CU, Ranges);

  GenerateKernel(K);
}
