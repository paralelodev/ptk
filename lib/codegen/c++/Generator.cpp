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

static void GenerateLoops(Kernel &K) {
  for (auto &&[Ind, Range] : K.GetRanges()) {
    std::cout << fmt::format(
        "  for ( {0} {1} = {2}; {1} < {3}; {1} += {4} ) {{\n"
        "    \n",
        GetWidthAsString(Range.GetWidth()), Ind, Range.GetLowerbound(),
        Range.GetUpperbound(), Range.GetStride());
  }

  for (int i = 0; i < K.GetRanges().size(); i++) {
    std::cout << "  }\n";
  }
}

static void GenerateCollapse(Kernel &K) {
  short CollapseLevel = K.GetCollapseLevel();
  std::cout << (CollapseLevel > 1
                    ? fmt::format(" collapse({0})\n", CollapseLevel)
                    : "\n");
}

static void GenerateCollapsedLoops(Kernel &K) {
  GenerateCollapse(K);
  GenerateLoops(K);
}

static void GenerateCollapsedLoopsWithDirective(Kernel &K,
                                                std::string_view Directive) {
  std::cout << Directive;
  GenerateCollapsedLoops(K);
}

static void GenerateCPUCode(Kernel &K, ComputingUnit TargetCU) {
  switch (TargetCU) {
  case ComputingUnit::THREAD: {
    GenerateCollapsedLoopsWithDirective(K, "#pragma omp parallel for");
    break;
  }
  default:
    break;
  }
}

static void GenerateAccelCode(Kernel &K, ComputingUnit TargetCU) {
  switch (TargetCU) {
  case ptk::ComputingUnit::TEAM: {
    GenerateCollapsedLoopsWithDirective(K,
                                        "#pragma omp target teams distribute");
    break;
  }
  default:
    break;
  }
}

void GenerateKernel(Kernel &K) {
  auto [SourceCU, TargetCU] = K.GetDistribution();

  std::cout << fmt::format("void {0} () {{\n", K.GetName());

  switch (SourceCU) {
  case ptk::ComputingUnit::CPU:
    GenerateCPUCode(K, TargetCU);
    break;
  case ptk::ComputingUnit::ACCEL:
    GenerateAccelCode(K, TargetCU);
    break;
  default:
    break;
  }

  std::cout << '}' << '\n';
}
} // namespace ptk
