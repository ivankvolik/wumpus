#pragma once

#include <vector>
#include <tuple>

namespace wumpus {
namespace world {

/*
 * World returns following feedback for move:
 * ladders - 1
 * scream - 2
 * glitter - 4
 * bump - 8
 * breeze - 16
 * stench - 32
 *
 * Orientation is:
 * 0 - along x axis positive direction
 * 1 - along y axis negative direction
 * 2 - along x axis negative direction
 * 3 - along y axis positive direction
 *
 *
 */

class World {
public:
	World(std::vector<std::vector<int> > world_map,
			  int starting_x,
				int starting_y,
				int wumpus_x,
				int wumpus_y);

	int Move(bool forward);
	int Turn(bool cw);
	bool Action(int action);

private:
	bool HandleArrowShoot();
	bool HandleGoldPickup();
	bool HandleGoldDrop();
	bool HandleLadderClimb();

	std::vector<std::vector<int> > world_map_;
	int current_x_, current_y_;
	int current_orientation_;
	int wumpus_x_, wumpus_y_;
	bool wumpus_alive_, arrow_shot_, gold_picked_up_;
};
}
}
