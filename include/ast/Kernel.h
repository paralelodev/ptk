#include "ComputingDistribution.h"
#include "Range.h"

#include <string>
#include <vector>

namespace ptk {
template <typename T> class Kernel {
private:
  std::string &Name;
  ComputingDistribution &Distribution;
  std::vector<std::pair<std::string, Range<T>>> &Ranges;

public:
  Kernel<T>(std::string &name, ComputingDistribution &distribution,
            std::vector<std::pair<std::string, Range<T>>> &ranges)
      : Name(name), Distribution(distribution), Ranges(ranges) {}

  std::string &GetName() const { return Name; }
  ComputingDistribution &GetDistribution() const { return Distribution; }
  std::vector<std::pair<std::string, Range<T>>> &GetRanges() const {
    return Ranges;
  }
};
} // namespace ptk
