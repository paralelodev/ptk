#include "c++/Generator.h"

using namespace ptk;
using namespace std;

int main() {
  string Name = "test";
  ComputingDistribution CU = {ComputingUnit::CPU, ComputingUnit::THREAD};
  std::vector<std::pair<std::string, Range>> Ranges = {
      {"i", {0, 100, 1, RangeType::SPACE, RangeWidth::INTEGER}}};

  Kernel K(Name, CU, Ranges);

  GenerateKernel(K);
}
