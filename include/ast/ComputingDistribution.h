namespace ptk {
enum class ComputingUnit { NODE, CPU, CORE, ACCEL, TEAM, THREAD, VECTOR };

class ComputingDistribution {
public:
  ComputingUnit Source;
  ComputingUnit Target;
};

} // namespace ptk
