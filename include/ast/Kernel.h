#include "ComputingDistribution.h"
#include "Range.h"

#include <string>

namespace ptk {
class Kernel {
private:
  std::string &Name;
  ComputingDistribution &Distribution;
  RangeContainer &Ranges;

public:
  Kernel(std::string &name, ComputingDistribution &distribution,
         RangeContainer &ranges)
      : Name(name), Distribution(distribution), Ranges(ranges) {}

  std::string &GetName() const { return Name; }
  ComputingDistribution &GetDistribution() const { return Distribution; }
  const RangeVector &GetRanges() const { return Ranges.GetRanges(); }
  short GetCollapseLevel() const { return Ranges.GetCollapseLevel(); }
};
} // namespace ptk
