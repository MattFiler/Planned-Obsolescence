#ifndef PO_GEOMETRY
#define PO_GEOMETRY

/**
 **   Represents a point in 2d space
 */
struct Point
{
  Point(float px, float py);
  Point(){};
  float x = 0;
  float y = 0;

  static float distanceBetween(Point a, Point b);
};

/**
 **   Represents a vector in 2d space
 */
struct Vector
{
  Vector(float px, float py);
  Vector(){};

  void normalise();
  void set(float new_x, float new_y);
  void flip();
  Vector reflectVector(Vector target_vector);
  Vector normal();

  static float angleBetweenVectors(Vector a, Vector b);
  static float dotProduct(Vector a, Vector b);

  float x = 0;
  float y = 0;
  float magnitude = 0;
};

/**
 **   Represents a line in 2d space
 */
struct Line
{
  Line(float gradient, float y_intersect, bool verticle = false, float x_intersect = 0);
  Line(){};

  bool intersects(Line line, Point& point);
  Vector vector();

  static bool pointBetweenPoints(Point a, Point b, Point c);

  float m = 0;
  float c = 0;
  bool verticle_line = false;
  float y = 0;
};

#endif