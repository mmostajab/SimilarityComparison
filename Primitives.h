#pragma once

#include <glm/glm.hpp>

inline static bool rayTriangleIntersection(const glm::vec3& ray_origin, const glm::vec3& ray_dir, const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, float& t)
{
  glm::vec3 e1 = p1 - p0, e2 = p2 - p0;

  glm::vec3 h = cross(ray_dir, e2);
  float a = dot(e1, h);

  if (a > -0.00001 && a < 0.00001)
    return false;

  float f = 1 / a;
  glm::vec3 s = ray_origin - p0;
  float u = f * dot(s, h);

  if (u < 0.0 || u > 1.0)
    return(false);

  glm::vec3 q = cross(s, e1);
  float v = f * dot(ray_dir, q);

  if (v < 0.0 || u + v > 1.0)
    return(false);

  // at this stage we can compute t to find out where
  // the intersection point is on the line
  t = f * dot(e2, q);

  if (t > 0.00001) // ray intersection
    return true;
  else // this means that there is a line intersection
    // but not a ray intersection
    return false;
}
