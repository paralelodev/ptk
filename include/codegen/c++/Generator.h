#include "Kernel.h"
#include <iostream>

namespace ptk {
template <typename T> void GenerateKernel(Kernel<T> &K) {
  const ComputingDistribution &Distribution = K.GetDistribution();

  std::cout << "void " << K.GetName() << '{' << '\n';

  switch (Distribution.Source) {
  case ptk::ComputingUnit::CPU:
    switch (Distribution.Target) {
    case ptk::ComputingUnit::THREAD:
      for (auto [ind, range] : K.GetRanges()) {
        std::cout << "  for( " << ind << " = " << range.GetLowerbound() << "; "
                  << ind << " < " << range.GetUpperbound() << "; " << ind
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
