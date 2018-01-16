#pragma once

#include <map>
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
	World(std::map<int, std::map<int, int> > map,
			  std::tuple<int, int> starting_position);

	int Move(bool forward);
	int Turn(bool cw);
	bool Action(int action);

private:
	bool HandleArrowShoot();
	bool HandleGoldPickup();
	bool HandleGoldDrop();
	bool HandleLadderClimb();

	std::map<int, std::map<int, int> > world_map_;
	std::tuple<int, int> current_position_;
	int current_orientation_;
	bool wumpus_alive, arrow_shot, gold_picked_up;
};
}
}
