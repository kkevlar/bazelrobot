#ifndef DRIVE_H
#define DRIVE_H

#include <inttypes.h>
#include "robot/logic/robottypes.h"

struct _drive_vector_t_
{
	int32_t degrees; 
	int32_t speed;
	// uint8_t maxspeed; 
};
typedef struct _drive_vector_t_ drive_vector_t;

void drive_init(void);
int16_t direction_to_degrees(direction_t dir);
int16_t drive_easy_atan(int16_t fb, int16_t lr);
drive_vector_t drive_combine_vecs(drive_vector_t a, drive_vector_t b, int speed_max);
void go_front(void);
void go_back(void);
void go_right(void);
void go_left(void);
void go_stop(void);
void go(drive_vector_t vec);

#endif
