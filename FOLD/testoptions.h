
#ifndef TESTOPTIONS_H
#define TESTOPTIONS_H

// #define TEST_DRIVE_STOP
// #define TEST_SWITCH
// #define TEST_LOGIC_SWITCH
// #define TEST_DRIVE_DIAG
// #define TEST_DRIVE_CARD
// #define TEST_ECHO
// #define TEST_LCD
// #define TEST_CONVEYORS_INDEXER
// #define TEST_FLYWHEEL
// #define TEST_PCONTROL


#define GAME_A


#if defined(TEST_DRIVE_STOP) || \
	defined(TEST_SWITCH) ||\
	defined(TEST_LOGIC_SWITCH) ||\
	defined(TEST_DRIVE_DIAG) ||\
	defined(TEST_DRIVE_CARD) ||\
	defined(TEST_ECHO) || \
	defined(TEST_CONVEYORS_INDEXER) || \
	defined(TEST_FLYWHEEL) || \
	defined(TEST_PCONTROL) || \
	defined(TEST_LCD)

#define TEST_NO_GAME

#endif



#endif

