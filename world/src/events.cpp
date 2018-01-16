#include <stdexcept>
#include <world/include/events.h>

namespace wumpus {
namespace world {

bool CheckEvent(int field_value, Events event) {
	if(field_value > 63) {
		throw new std::runtime_error("Field value incorrect");
	}
	int sense_value = GetEventNumber(event);
	int current_sense = 32;
	do{
		if(field_value >= current_sense) {
			if(current_sense == sense_value) {
				return true;
			}
			field_value -= current_sense;
		}
	}while(field_value > 0);
	return false;
}

} // namespace world
} // namespace wumpus
