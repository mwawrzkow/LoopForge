#pragma once

#include "Point.hpp"
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <vector>

namespace LF::Primitives {
class Polygon {
public:
  Polygon();
  Polygon(std::size_t size);
  Polygon(std::initializer_list<Point2D>);

  ~Polygon();
  Polygon(Polygon &&) noexcept;
  Polygon &operator=(Polygon &&) noexcept;

  Polygon(const Polygon &) = delete;
  Polygon &operator=(const Polygon &) = delete;

  const double &area() const;

private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

} // namespace LF::Primitives
