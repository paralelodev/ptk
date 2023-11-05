#include <string>
#include <vector>

namespace ptk {
enum class RangeType { SPACE, DIMENSION };

enum class RangeWidth { INTEGER, LONG };

class Range {
private:
  long Lowerbound;
  long Upperbound;
  long Stride;
  RangeType Type;
  RangeWidth Width;

public:
  Range(long lowerbound, long upperbound, long stride, RangeType type,
        RangeWidth width)
      : Lowerbound(lowerbound), Upperbound(upperbound), Stride(stride),
        Type(type), Width(width) {}

  long GetLowerbound() const { return Lowerbound; }
  long GetUpperbound() const { return Upperbound; }
  long GetStride() const { return Stride; }
  RangeType GetType() const { return Type; }
  RangeWidth GetWidth() const { return Width; }
};

using RangeVector = std::vector<std::pair<std::string, Range>>;

class RangeContainer {
private:
  RangeVector Ranges;

public:
  void Insert(std::string, Range);
  const RangeVector &GetRanges() const { return Ranges; }
};

} // namespace ptk
