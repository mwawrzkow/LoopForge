#pragma once

#include "Point.hpp"
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <optional>

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

  const std::optional<double> area() const;
  bool add(const Point2D &p);
  bool remove(std::size_t idx);
  bool update(std::size_t idx, const Point2D &p);
  void freeze();
  void unfreeze();

private:
  struct Impl;
  std::unique_ptr<Impl> impl_;
};

} // namespace LF::Primitives
