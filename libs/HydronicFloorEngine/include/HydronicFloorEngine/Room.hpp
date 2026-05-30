#pragma once
#include "Primitives/Polygon.hpp"
#include <optional>
namespace LF::HydronicFloorEngine {
class Room {
  Primitives::Polygon room;
  std::optional<Primitives::Polygon> usable_area;
};
} // namespace LF::HydronicFloorEngine
