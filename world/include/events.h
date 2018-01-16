#pragma once

namespace wumpus {
namespace world {
enum class Events {
	 Ladders = 1,
	 Scream = 2,
	 Glitter = 4,
	 Wumpus = 8,
	 Hole = 16,
	 Bump = 32,
	 Breeze = 64,
	 Stench = 128 };

static inline int GetEventNumber(Events event) {
	return static_cast<int>(event);
}

bool CheckEvent(int field, Events event);
} // namespace world
} // namespace wumpus

