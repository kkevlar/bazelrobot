#ifndef SWITCH_H
#define SWTICH_H

#include "robottypes.h"

void switch_init(void);
pin_t switch_test_all();
bool switch_test_up(direction_t dir);
bool switch_test_down(direction_t dir);

#endif
