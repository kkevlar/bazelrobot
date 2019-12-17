
#ifndef COLLECT_H
#define COLLECT_H

#include "testoptions.h"
#include "wiring.h"
#include "control.h"
#include "drive.h"
#include "shoot.h"
#include "switch.h"

void collect_init(void);
void position_for_collection(direction_t dir_wall, direction_t dir_target, float mm_target);
void roomba(direction_t dir_wall);
void do_collection(direction_t dir_wall, direction_t dir_target, float mm_target);
void yeet_away_from_wall(direction_t dir_wall, float mm_target);
void collect_right();
void collect_back();
void collect_left();
void collection_victory_lap();



#endif
