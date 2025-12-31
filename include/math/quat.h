#pragma once

#include <cmath>

#include "math/vec3.h"

class Quat {
 public:
  Quat();
  Quat(float x, float y, float z, float w);

  Quat angle_axis(float angle, const Vec3f& axis);
  Quat from(const Vec3f& from, const Vec3f& to);

 private:
  float m_x;
  float m_y;
  float m_z;
  float m_w;
};

inline Quat::Quat() : m_x(0.f), m_y(0.f), m_z(0.f), m_w(1.f) {}

inline Quat::Quat(float x, float y, float z, float w)
    : m_x(x), m_y(y), m_z(z), m_w(w) {}

inline Quat Quat::angle_axis(float angle, const Vec3f& axis) {
  Vec3f norm(axis);
  norm.normalize();
  auto s = sinf(angle * 0.5f);
  return Quat(norm.x() * s, norm.y() * s, norm.z() * s, cosf(angle * 0.5f));
}

inline Quat Quat::from(const Vec3f& from, const Vec3f& to) {
  auto f(from);
  f.normalize();
  auto t(to);
  t.normalize();

  if (f == t) {
    return Quat();
  } else if (f == -t) {
    auto ortho = Vec3f(1.f, 0.f, 0.f);
    if (fabsf(f.y()) < fabsf(f.x())) {
      ortho = Vec3f(0.f, 1.f, 0.f);
    }
    if (fabsf(f.z()) < fabsf(f.y()) && fabsf(f.z()) < fabsf(f.x())) {
      ortho = Vec3f(0.f, 0.f, 1.f);
    }

    auto axis = cross(f, ortho);
    axis.normalize();
    return Quat(axis.x(), axis.y(), axis.z(), 0.f);
  }

  auto half = f + t;
  half.normalize();
  auto axis = cross(f, half);
  return Quat(axis.x(), axis.y(), axis.z(), dot(f, half));
}
