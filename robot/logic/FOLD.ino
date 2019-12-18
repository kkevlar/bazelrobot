#include "FOLD.h"


void setup()
{
	#if defined(TEST_NO_GAME)
		test_setup();
	#elif defined(GAME_A)
		main_setup();
	#else
		#error "NO OPTION"
	#endif
}

void loop()
{
	#if defined(TEST_NO_GAME)
		test_loop();
	#elif defined(GAME_A)
		main_loop();
	#else
		#error "NO OPTION"
	#endif
}
