#include "c++/Generator.h"

#include <fmt/core.h>

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

static void GenerateLoops(std::ostream &Out, Kernel &K) {
  for (auto &&[Ind, Range] : K.GetRanges()) {
    Out << fmt::format("  for ( {0} {1} = {2}; {1} < {3}; {1} += {4} ) {{\n"
                       "    \n",
                       GetWidthAsString(Range.GetWidth()), Ind,
                       Range.GetLowerbound(), Range.GetUpperbound(),
                       Range.GetStride());
  }

  for (int i = 0; i < K.GetRanges().size(); i++) {
    Out << "  }\n";
  }
}

static void GenerateCollapse(std::ostream &Out, Kernel &K) {
  short CollapseLevel = K.GetCollapseLevel();
  Out << (CollapseLevel > 1 ? fmt::format(" collapse({0})\n", CollapseLevel)
                            : "\n");
}

static void GenerateCollapsedLoops(std::ostream &Out, Kernel &K) {
  GenerateCollapse(Out, K);
  GenerateLoops(Out, K);
}

static void GenerateDirective(std::ostream &Out, std::string_view Directive) {
  Out << Directive;
}

static void GenerateCollapsedLoopsWithDirective(std::ostream &Out, Kernel &K,
                                                std::string_view Directive) {
  GenerateDirective(Out, Directive);
  GenerateCollapsedLoops(Out, K);
}

static void GenerateCPUCode(std::ostream &Out, Kernel &K,
                            ComputingUnit TargetCU) {
  switch (TargetCU) {
  case ComputingUnit::THREAD: {
    GenerateCollapsedLoopsWithDirective(Out, K, "#pragma omp parallel for");
    break;
  }
  default:
    break;
  }
}

static void GenerateAccelCode(std::ostream &Out, Kernel &K,
                              ComputingUnit TargetCU) {
  switch (TargetCU) {
  case ptk::ComputingUnit::TEAM: {
    GenerateCollapsedLoopsWithDirective(Out, K,
                                        "#pragma omp target teams distribute");
    break;
  }
  default:
    break;
  }
}

void GenerateKernel(std::ostream &Out, Kernel &K) {
  auto [SourceCU, TargetCU] = K.GetDistribution();

  Out << fmt::format("void {0} () {{\n", K.GetName());

  switch (SourceCU) {
  case ptk::ComputingUnit::CPU:
    GenerateCPUCode(Out, K, TargetCU);
    break;
  case ptk::ComputingUnit::ACCEL:
    GenerateAccelCode(Out, K, TargetCU);
    break;
  default:
    break;
  }

  Out << '}' << '\n';
}
} // namespace ptk
