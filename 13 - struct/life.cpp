#include <iostream>
#include <windows.h>
using namespace std;
enum life_type { poultry, cattle, human };
union life_chara { // characteristic
	float speed;
	int	iq;
	int cloven_woof;
};
struct life {
	float speed;
	char color[15];
	life_type type;
	life_chara chara;
};

void fill(life &l, float speed, char color[], life_type type, life_chara chara) {
	l.speed = speed;
	strcpy(l.color, color);
	l.type = type;
}

main() {
}
