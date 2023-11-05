namespace ptk {
enum class RangeType { SPACE, DIMENSION };

template <typename T> class Range {
private:
  T Lowerbound;
  T Upperbound;
  T Stride;
  RangeType Type;

public:
  Range(T lowerbound, T upperbound, T stride, RangeType type)
      : Lowerbound(lowerbound), Upperbound(upperbound), Stride(stride),
        Type(type) {}
  T GetLowerbound() const { return Lowerbound; }
  T GetUpperbound() const { return Upperbound; }
  T GetStride() const { return Stride; }
};
} // namespace ptk
