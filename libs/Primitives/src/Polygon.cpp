#include "Polygon.hpp"
#include "Point.hpp"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Polygon_2.h>
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <ranges>
#include <vector>

using namespace LF::Primitives;

struct Polygon::Impl {
  using Kernel = CGAL::Exact_predicates_inexact_constructions_kernel;
  using CGALPoint = Kernel::Point_2;
  using CGALPolygon = CGAL::Polygon_2<Kernel>;
  std::unique_ptr<CGALPolygon> polygon = nullptr;
  std::vector<Point2D> points;
  Impl() = default;
  Impl(std::initializer_list<Point2D> data) : points(data) {}
  Impl(std::size_t reserve) { points.reserve(reserve); }

  bool add(const Point2D &p) {
    if (locked())
      return false;
    points.push_back(p);
    return true;
  }

  bool update(std::size_t idx, const Point2D &p) {
    if (locked())
      return false;
    if (idx >= points.size())
      return false;
    points[idx] = p;
    return true;
  }
  std::size_t size() const { return points.size(); }
  bool locked() const { return polygon.get(); }
  void lock() {
    if (locked())
      return;

    auto cgal_points = points | std::views::transform([](const Point2D &p) {
                         return CGALPoint{p.x, p.y};
                       }) |
                       std::ranges::to<std::vector>();
    polygon =
        std::make_unique<CGALPolygon>(cgal_points.begin(), cgal_points.end());
  }

  void release() { polygon.reset(); }
};

Polygon::Polygon() : impl_(std::make_unique<Impl>()) {}
Polygon::~Polygon() = default;
Polygon::Polygon(std::size_t size) : impl_(std::make_unique<Impl>(size)) {}

Polygon::Polygon(std::initializer_list<Point2D> points)
    : impl_(std::make_unique<Impl>(points)) {}

Polygon::Polygon(Polygon &&) noexcept = default;
Polygon &Polygon::operator=(Polygon &&) noexcept = default;
