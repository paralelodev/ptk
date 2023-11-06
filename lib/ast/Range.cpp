#include "Range.h"

#include <iostream>

namespace ptk {
void RangeContainer::Insert(std::string newInd, Range newRange) {
  for (auto &&[Ind, Range] : Ranges) {
    if (Ind == newInd) {
      std::cerr << "Error: The range identifier already exists\n";
      exit(0);
    }
  }

  if (newRange.GetType() == RangeType::SPACE) {
    if (!Ranges.empty() &&
        Ranges.back().second.GetType() == RangeType::DIMENSION) {
      std::cerr << "Error: The range must be a dimension\n";
      exit(0);
    }

    CollapseLevel++;
  }

  Ranges.push_back({newInd, newRange});
}
} // namespace ptk
