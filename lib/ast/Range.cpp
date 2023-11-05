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

  Ranges.push_back({newInd, newRange});
}
} // namespace ptk
