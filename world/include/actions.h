#pragma once

namespace wumpus {
namespace world {
enum class Actions {
	 ClimbLadder = 1,
	 ShootArrow = 2,
	 PickUpGold = 4,
	 DropGold = 8};

static inline int GetActionNumber(Actions action) {
	return static_cast<int>(action);
}
} // namespace world
} // namespace wumpus
