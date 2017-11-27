#ifndef RAILTRACK_H
#define RAILTRACK_H

#include "Engine/Entity.h"
class RailTrack
{
public:
    RailTrack();
    ~RailTrack();

struct sPoint2D
{
  float x;
  float y;
};

struct sSpline
{
std::vector<sPoint2D> points;

sPoint2D GetSplinePoint(float t, bool bLooped = false)
{
int p0, p1, p2, p3;
if (!bLooped)
{
  p1 = (int)t + 1;
  p2 = p1 + 1;
  p3 = p2 + 1;
  p0 = p1 - 1;
}
else
{
  p1 = (int)t;
  p2 = (p1 + 1) % points.size();
  p3 = (p2 + 1) % points.size();
  p0 = p1 >= 1 ? p1 - 1 : points.size() - 1;
}

t = t - (int)t;

float tt = t * t;
float ttt = tt * t;

float q1 = -ttt + 2.0f*tt - t;
float q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
float q3 = -3.0f*ttt + 4.0f*tt + t;
float q4 = ttt - tt;

float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

return{ tx, ty };
}

sPoint2D GetSplineGradient(float t, bool bLooped = false)
{
int p0, p1, p2, p3;
if (!bLooped)
{
  p1 = (int)t + 1;
  p2 = p1 + 1;
  p3 = p2 + 1;
  p0 = p1 - 1;
}
else
{
  p1 = (int)t;
  p2 = (p1 + 1) % points.size();
  p3 = (p2 + 1) % points.size();
  p0 = p1 >= 1 ? p1 - 1 : points.size() - 1;
}

t = t - (int)t;

float tt = t * t;
float ttt = tt * t;

float q1 = -3.0f * tt + 4.0f*t - 1;
float q2 = 9.0f*tt - 10.0f*t;
float q3 = -9.0f*tt + 8.0f*t + 1.0f;
float q4 = 3.0f*tt - 2.0f*t;

float tx = 0.5f * (points[p0].x * q1 + points[p1].x * q2 + points[p2].x * q3 + points[p3].x * q4);
float ty = 0.5f * (points[p0].y * q1 + points[p1].y * q2 + points[p2].y * q3 + points[p3].y * q4);

return{ tx, ty };
}



};
sSpline path;

};

#endif
