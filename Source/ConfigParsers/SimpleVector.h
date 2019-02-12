#ifndef PLANNEDOBSOLESCENCE_SIMPLEVECTOR_H
#define PLANNEDOBSOLESCENCE_SIMPLEVECTOR_H

/* A super simple vector */
struct SimpleVector
{
  SimpleVector(int new_x, int new_y)
  {
    x = new_x;
    y = new_y;
  }
  int x;
  int y;
};

#endif // PLANNEDOBSOLESCENCE_SIMPLEVECTOR_H
