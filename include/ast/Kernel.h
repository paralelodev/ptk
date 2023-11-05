#include "ComputingDistribution.h"
#include "Range.h"

#include <string>
#include <vector>

namespace ptk {
class Kernel {
private:
  std::string &Name;
  ComputingDistribution &Distribution;
  std::vector<std::pair<std::string, Range>> &Ranges;

public:
  Kernel(std::string &name, ComputingDistribution &distribution,
         std::vector<std::pair<std::string, Range>> &ranges)
      : Name(name), Distribution(distribution), Ranges(ranges) {}

  std::string &GetName() const { return Name; }
  ComputingDistribution &GetDistribution() const { return Distribution; }
  std::vector<std::pair<std::string, Range>> &GetRanges() const {
    return Ranges;
  }
};
} // namespace ptk
