#include <world/include/world.h>
#include <world/include/actions.h>
#include <world/include/events.h>

namespace wumpus {
namespace world {

World::World(std::map<int, std::map<int, int> > map,
						 std::tuple<int, int> starting_position)
		:	world_map_(map),
			current_position_(starting_position),
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
	int x_pos = std::get<0>(current_position_);
	int x_old = x_pos;
	int y_pos = std::get<1>(current_position_);
	int y_old = y_pos;

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
		int feeling = world_map_[x_old][y_old];
		return feeling + GetEventNumber(Events::Bump);
	}

	//Return the senses on the new position and memorise the position
	current_position_ = std::make_tuple(x_pos, y_pos);
	return world_map_[x_pos][y_pos];
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
	int x_pos = std::get<0>(current_position_);
	int y_pos = std::get<1>(current_position_);
	if(current_orientation_ == 0 ||
			current_orientation_ == 2) {
		//Handle horizontal shot

	} else {
		//Handle vertical shot
		auto& verical_row = world_map_[x_pos];
		auto vertical_field = verical_row.find(y_pos);
		vertical_field++;
		while (vertical_field != verical_row.end()) {
			if(CheckEvent(vertical_field->second, Events::Wumpus))
				return true;
		}
		return false;
	}
}

bool World::HandleGoldDrop() {
	int x_pos = std::get<0>(current_position_);
	int y_pos = std::get<1>(current_position_);
	int& field_value = world_map_[x_pos][y_pos];
	field_value += GetEventNumber(Events::Glitter);
	return true;
}

bool World::HandleGoldPickup() {
	int x_pos = std::get<0>(current_position_);
	int y_pos = std::get<1>(current_position_);
	int& field_value = world_map_[x_pos][y_pos];
	if(CheckEvent(field_value, Events::Ladders)) {
		//There is gold, and after it is picked up, it's no longer there
		field_value -= GetEventNumber(Events::Glitter);
		return true;
	} else {
		return false;
	}
}

bool World::HandleLadderClimb() {
	int x_pos = std::get<0>(current_position_);
	int y_pos = std::get<1>(current_position_);
	int field_value = world_map_[x_pos][y_pos];
	if(CheckEvent(field_value, Events::Ladders)) {
		return true;
	} else {
		return false;
	}
}

} // namespace world
} // namespace wumpus

