#include "c++/Generator.h"
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
  const ComputingDistribution &Distribution = K.GetDistribution();

  std::cout << "void " << K.GetName() << '{' << '\n';

  switch (Distribution.Source) {
  case ptk::ComputingUnit::CPU:
    switch (Distribution.Target) {
    case ptk::ComputingUnit::THREAD:
      for (auto [ind, range] : K.GetRanges()) {
        std::cout << "  for( " << GetWidthAsString(range.GetWidth()) << ' '
                  << ind << " = " << range.GetLowerbound() << "; " << ind
                  << " < " << range.GetUpperbound() << "; " << ind
                  << " += " << range.GetStride() << " ){\n  \n  }\n";
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
