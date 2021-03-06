
#ifndef AIM_H
#define AIM_H

#include "robottypes.h"

void aim_init(void);
aim_location_t aim_select_location(void);
void aim_pre(aim_location_t loc);
void aim_final(aim_location_t loc);
void aim(aim_location_t loc);


#endif
