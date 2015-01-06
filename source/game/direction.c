
#include <math.h>

#include "direction.h"

#include "../utility/math.h"

Direction get_random_direction() {
	return rand_between(NORTH, WEST);
}
