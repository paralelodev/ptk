#include "c++/Generator.h"

#include <fmt/core.h>
#include <iostream>

namespace ptk {

static std::string GetWidthAsString(RangeWidth Width) {
  switch (Width) {
  case RangeWidth::LONG:
    return "long";
  case RangeWidth::INTEGER:
  default:
    return "int";
  }
}

void GenerateKernel(Kernel &K) {
  auto [Source, Target] = K.GetDistribution();

  std::cout << "void " << K.GetName() << '{' << '\n';

  switch (Source) {
  case ptk::ComputingUnit::CPU:
    switch (Target) {
    case ptk::ComputingUnit::THREAD:
      for (auto [Ind, Range] : K.GetRanges()) {
        std::cout << fmt::format(
            "  #pragma omp parallel for\n"
            "  for ( {0} {1} = {2}; {1} < {3}; {1} += {4} ) {{\n"
            "  \n"
            "  }}\n",
            GetWidthAsString(Range.GetWidth()), Ind, Range.GetLowerbound(),
            Range.GetUpperbound(), Range.GetStride());
      }
      break;
    default:
      break;
    }
    break;
  case ptk::ComputingUnit::ACCEL:
    switch (Target) {
    case ptk::ComputingUnit::TEAM:
      for (auto [Ind, Range] : K.GetRanges()) {
        std::cout << fmt::format(
            "  #pragma omp target teams distribute\n"
            "  for ( {0} {1} = {2}; {1} < {3}; {1} += {4} ) {{\n"
            "  \n"
            "  }}\n",
            GetWidthAsString(Range.GetWidth()), Ind, Range.GetLowerbound(),
            Range.GetUpperbound(), Range.GetStride());
      }
      break;
    default:
      break;
    }
    break;
  default:
    break;
  }

  std::cout << '}' << '\n';
}
} // namespace ptk
