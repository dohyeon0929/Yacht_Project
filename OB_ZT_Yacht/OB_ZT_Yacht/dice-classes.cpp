#include "dice-classes.h"

int Dice::Roll() {
	return dice_num = dice_num_set[RandRange(0, dice_num_set.size() - 1)];
}
