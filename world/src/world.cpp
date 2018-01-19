#include <algorithm>
#include <stdexcept>
#include <world/include/world.h>
#include <world/include/actions.h>
#include <world/include/events.h>

namespace wumpus {
namespace world {

World::World(std::vector<std::vector<int> > world_map,
						int starting_x,
						int starting_y,
						int wumpus_x,
						int wumpus_y)
		:	world_map_(world_map),
			current_x_(starting_x),
			current_y_(starting_y),
			wumpus_x_(wumpus_x),
			wumpus_y_(wumpus_y),
			current_orientation_(0)
		{}

bool World::Action(int action) {
	if(action == GetActionNumber(Actions::ClimbLadder )){
		return HandleLadderClimb();
	}
	else if(action == GetActionNumber(Actions::PickUpGold)) {
		return HandleGoldPickup();
	}
	else if(action == GetActionNumber(Actions::ShootArrow)) {
		return HandleArrowShoot();
	}
	else if(action == GetActionNumber(Actions::DropGold)) {
		return HandleGoldDrop();
	}
}

int World::Move(bool forward) {
	// get new and old values for x and y
	int x_pos = current_x_;
	int y_pos = current_y_;

	//Determine the coordinated of the field agent is moving to
	if(current_orientation_ == 0){
		forward ? ++x_pos : --x_pos;
	}
	if(current_orientation_ == 1){
		forward ? --y_pos : ++y_pos;
	}
	if(current_orientation_ == 2){
		forward ? --x_pos : ++x_pos;
	}
	if(current_orientation_ == 3){
		forward ? ++y_pos : --y_pos;
	}

	//Return bump if new position is out of bounds
	if((x_pos < 0 || x_pos > world_map_.size())
			|| (y_pos < 0 || y_pos > world_map_[0].size())) {
		int event = world_map_[current_x_][current_x_];
		return event + GetEventNumber(Events::Bump);
	}

	//Return the senses on the new position and memorise the position
	current_x_ = x_pos;
	current_y_ = y_pos;
	if(CheckEvent(world_map_[x_pos][y_pos], Events::Wumpus)
			|| CheckEvent(world_map_[x_pos][y_pos], Events::Hole)){
		throw new std::logic_error("Agent was eaten by the wumpus or"
				"fallen into the pit");
	} else {
		return world_map_[x_pos][y_pos];
	}
}

int World::Turn(bool right) {
	current_orientation_ ++;
	if(current_orientation_ > 3) {
		current_orientation_ = 0;
	}
	if(current_orientation_ < 0) {
		current_orientation_ = 3;
	}

	return current_orientation_;
}


bool World::HandleArrowShoot() {
	if(arrow_shot_)
		return false;
	bool wumpus_hit = false;
	arrow_shot_ = true;
	if(current_orientation_ == 0 ||
			current_orientation_ == 2) {
		if(current_orientation_ == 0) {
			wumpus_hit = current_y_ ==  wumpus_y_
					&& current_x_ < wumpus_x_;
		} else {
			wumpus_hit = current_y_ ==  wumpus_y_
								&& current_x_ > wumpus_x_;
		}
	} else {
		if(current_orientation_ == 3) {
			wumpus_hit = current_x_ ==  wumpus_x_
					&& current_y_ < wumpus_y_;
		} else {
			wumpus_hit = current_x_ ==  wumpus_x_
					&& current_y_ > wumpus_y_;
		}
	}
	// If wumpus is hit, remove the wumpus from the map and clear the stench
	if(wumpus_hit) {
		world_map_[wumpus_x_][wumpus_y_] -= GetEventNumber(Events::Wumpus);
		world_map_[wumpus_x_-1][wumpus_y_] -= GetEventNumber(Events::Stench);
		world_map_[wumpus_x_+1][wumpus_y_] -= GetEventNumber(Events::Stench);
		world_map_[wumpus_x_][wumpus_y_-1] -= GetEventNumber(Events::Stench);
		world_map_[wumpus_x_][wumpus_y_+1] -= GetEventNumber(Events::Stench);
		return true;
	} else {
		throw new std::logic_error("Agent has missed the wumpus");
	}
}

bool World::HandleGoldDrop() {
	world_map_[current_x_][current_y_] += GetEventNumber(Events::Glitter);
	return true;
}

bool World::HandleGoldPickup() {
	int& field_value = world_map_[current_x_][current_y_];
	if(CheckEvent(field_value, Events::Glitter)) {
		//There is gold, and after it is picked up, it's no longer there
		field_value -= GetEventNumber(Events::Glitter);
		return true;
	} else {
		return false;
	}
}

bool World::HandleLadderClimb() {
	int field_value = world_map_[current_x_][current_y_];
	if(CheckEvent(field_value, Events::Ladders)) {
		return true;
	} else {
		return false;
	}
}

} // namespace world
} // namespace wumpus

