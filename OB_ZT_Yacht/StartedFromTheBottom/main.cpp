#include "essential.h"
#include "system-classes.h"
int main() {
	extern GameManager& gm;
	gm.SetScene("start");
	return 0;
}