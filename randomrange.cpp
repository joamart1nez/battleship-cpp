#include "randomrange.h"

RandomRange::RandomRange() { this->inicializar(); }

void RandomRange::inicializar() { srand(time(NULL)); }

int RandomRange::get(int min, int max) { return rand() % ((max + min) + min); }
