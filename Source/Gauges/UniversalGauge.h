#ifndef PLANNEDOBSOLESCENCE_UNIVERSALGAUGE_H
#define PLANNEDOBSOLESCENCE_UNIVERSALGAUGE_H

class UniversalGauge
{
 public:
  UniversalGauge() = default;
  ~UniversalGauge() = default;

  void update(double delta_time);

  static float project_progress;
  static float project_percent;
  static float npc_suspicion;
};

#endif // PLANNEDOBSOLESCENCE_UNIVERSALGAUGE_H
