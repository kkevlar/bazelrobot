#include "test.h"

#ifdef TEST_NO_GAME


void test_setup()
{
	lcd_init();

	lcd_print_top("Initing test...");


	#if defined(TEST_DRIVE_STOP)
		drive_init();
	#elif defined(TEST_DRIVE_DIAG)
		drive_init();

	#elif defined(TEST_DRIVE_CARD)
		drive_init();

	#elif defined(TEST_SWITCH)
		switch_init();

	#elif defined(TEST_LOGIC_SWITCH)
		switch_init();

	#elif defined(TEST_ECHO)
		echo_init();

	#elif defined(TEST_CONVEYOR_INDEXER)
		shoot_init();
	#elif defined(TEST_LCD)

	#elif defined(TEST_FLYWHEEL)
		shoot_init();	
	#elif defined(TEST_PCONTROL)
		echo_init();	
		drive_init();
	#endif

	// switch_init();
	// echo_init();
	// Serial.begin(9600);
}

void lcd_test()
{
	lcd_hello_world();
}

void switch_test()
{
	int i;
	char buf[17];

	i = 0;

	i += sprintf(buf + i, "FL=");
	#ifdef PIN_SWITCH_FRONT_L
	i += sprintf(buf + i, digitalRead(PIN_SWITCH_FRONT_L) == LOW ? "L" : " ");
	#else
	i += sprintf(buf + i, "?");
	#endif

	i += sprintf(buf + i, " ");

	i += sprintf(buf + i, "LF=");
	#ifdef PIN_SWITCH_LEFT_F
	i += sprintf(buf + i, digitalRead(PIN_SWITCH_LEFT_F) == LOW ? "L" : " ");
	#else
	i += sprintf(buf + i, "?");
	#endif

	i += sprintf(buf + i, " ");

	i += sprintf(buf + i, "LB=");
	#ifdef PIN_SWITCH_LEFT_B
	i += sprintf(buf + i, digitalRead(PIN_SWITCH_LEFT_B) == LOW ? "L" : " ");
	#else
	i += sprintf(buf + i, "?");
	#endif

	lcd_print_top(buf);

	i = 0;

	i += sprintf(buf + i, "BL=");
	#ifdef PIN_SWITCH_BACK_L
	i += sprintf(buf + i, digitalRead(PIN_SWITCH_BACK_L) == LOW ? "L" : " ");
	#else
	i += sprintf(buf + i, "?");
	#endif

	i += sprintf(buf + i, " ");

	i += sprintf(buf + i, "RF=");
	#ifdef PIN_SWITCH_RIGHT_F
	i += sprintf(buf + i, digitalRead(PIN_SWITCH_RIGHT_F) == LOW ? "L" : " ");
	#else
	i += sprintf(buf + i, "?");
	#endif

	i += sprintf(buf + i, " ");

	i += sprintf(buf + i, "RB=");
	#ifdef PIN_SWITCH_RIGHT_B
	i += sprintf(buf + i, digitalRead(PIN_SWITCH_RIGHT_B) == LOW ? "L" : " ");
	#else
	i += sprintf(buf + i, "?");
	#endif

	lcd_print_bot(buf);

}


void logic_switch_test()
{
	int i;
	char buf[17];

	i = 0;

	i += sprintf(buf + i, switch_test_up(DIRECTION_ID_FRONT) ? "FRONT " : "F---- ");
	i += sprintf(buf + i, switch_test_up(DIRECTION_ID_BACK) ? "BACK  " : "B---  ");
	lcd_print_top(buf);
	i = 0;
	i += sprintf(buf + i, switch_test_up(DIRECTION_ID_LEFT) ? "LEFT  " : "L---  ");
	i += sprintf(buf + i, switch_test_up(DIRECTION_ID_RIGHT) ? "RIGHT " : "R---- ");
	lcd_print_bot(buf);

	

}


void diag_test()
{
	drive_vector_t vec;
	vec.speed = 255;

	for(int i = 0; i < 4; i++)
	{
		vec.degrees = 45 + 90*i;
		go(vec);
		delay(1000);
		go_stop();
		delay(1000);
	}
	delay(5000);
}

char* deg_to_str(int n)
{
	if(n == DEGREES_FRONT)
		return "Front";
	if(n == DEGREES_BACK)
		return "Back";
	if(n == DEGREES_LEFT)
		return "Left";
	if(n == DEGREES_RIGHT)
		return "Right";

	return "None";
}

void card_test()
{
	// drive_vector_t vec;
	// vec.speed = 255;
	// char buf[32];

	// // Serial.println("immacard");
	// lcd_print_top("Testing Cardinal");

	// for(int i = 0; i < 4; i++)
	// {
	// 	vec.degrees = 90*i;
	// 	go(vec);
	// 	sprintf(buf, "%d", vec.degrees);
	// 	lcd_print_bot(buf);
	// 	delay(200);
	// 	go_stop();
	// 	lcd_print_bot("Stop!");
	// 	delay(200);
	// }
	// delay(1000);

	// set_speed(WHEEL_FL,255,0);
	// set_speed(WHEEL_FR,255,0);
	// set_speed(WHEEL_BL,255,0);
	// set_speed(WHEEL_BR,255,0);

	go_right();


	delay(100);
}

void echo_test()
{
	float f_front = -1;
	float f_back = -1;
	float f_left = -1;
	float f_right = -1;
	char buf[128];
	int16_t i_front = -1;
	int16_t i_back = -1;
	int16_t i_left = -1;
	int16_t i_right = -1;
	int i = 0;

	go_stop();

	while(true)
	{

		i++;

	// f_front = echo_test_mm(PIN_ULTRASONIC_ECHO_FRONT);
	
	// f_back = echo_test_mm(PIN_ULTRASONIC_ECHO_BACK);
	f_left = echo_test_mm(PIN_ULTRASONIC_ECHO_LEFT);
	delay(20);
	f_right = echo_test_mm(PIN_ULTRASONIC_ECHO_RIGHT);

	// i_front = ((int16_t )f_front);
	// i_back = f_back;
	i_left = f_left;
	i_right = f_right;

	sprintf(buf,"LEFT:  %5d", i_left);
	lcd_print_top(buf);
	sprintf(buf,"RIGHT: %5d", i_right);
	lcd_print_bot(buf);

	
	delay(100);
	}

	/*while(true)
	{

		i++;

	f_front = echo_test_mm(PIN_ULTRASONIC_ECHO_FRONT);
	delay(20);
	f_back = echo_test_mm(PIN_ULTRASONIC_ECHO_BACK);
	// f_left = echo_test_mm(PIN_ULTRASONIC_ECHO_LEFT);
	// f_right = echo_test_mm(PIN_ULTRASONIC_ECHO_RIGHT);

	i_front = ((int16_t )f_front);
	i_back = f_back;
	// i_left = f_left;
	// i_right = f_right;

	sprintf(buf,"FRONT: %5d", i_front);
	lcd_print_top(buf);
	sprintf(buf,"BACK:  %5d", i_back);
	lcd_print_bot(buf);

	
	delay(100);
	}*/
}

void flywheel_test()
{
	// go_stop();
	shoot_flywheel_left_stop();
	shoot_conveyor_left_stop();
	shoot_indexer_stop();
	lcd_print_top("zzzz  :)  zzzzzzzzz");
	delay(2000); 
	shoot_flywheel_left_start();
	shoot_conveyor_left_start();
	shoot_indexer_start();
	lcd_print_top("WHeeeeee           ");
	delay(5000);

}

void conveyors_indexer_test()
{
	lcd_print_bot(":))");
	shoot_conveyor_both_stop();
	shoot_indexer_stop();
	lcd_print_top("cs and i stopped");
	delay(2000);
	shoot_conveyor_both_start();
	shoot_indexer_start();
	lcd_print_top("SPPINNNNNNNN");
	delay(2000);
}

void pcontrol_test_print_update(float curr, float target)
{
	char buf[32];
	int i_curr;
	int i_target;


	i_curr = curr;
	i_target = target;

	snprintf(buf, 32, "%5d -> %5d", i_curr, i_target);

	lcd_print_bot(buf);
}

void pcontrol_test_helper(float mm_target)
{

	direction_t dir_target = DIRECTION_ID_FRONT;
	direction_t dir_wall = DIRECTION_ID_RIGHT;

	struct p_control_result result_target;
	struct p_control_args args_target;

	drive_vector_t vec_wall;
	drive_vector_t vec_target;
	drive_vector_t vec_result;


	vec_wall.degrees = direction_to_degrees(dir_wall);
	vec_target.degrees = direction_to_degrees(dir_target);

	control_clear_result(&result_target);

	vec_wall.speed = 30;

	args_target.pin_ultrasonic = direction_to_echo_pin(dir_target);
	args_target.pk = 1.5f;
	args_target.max_speed = 255;
	args_target.abs_speed_dead_zone = 0;
	args_target.abs_speed_boost_zone = 0;
	args_target.echo_data_buf_count = 1;
	args_target.mm_accuracy = 20;
	args_target.mm_target = mm_target;

	while(1)
	{
		delay(15);
		p_control_non_block(&result_target,&args_target);

		vec_target.speed = result_target.result_speed;

		vec_result = drive_combine_vecs(vec_target, vec_wall, 255);

		vec_result.speed = (int16_t) (control_treat_speed(
			(float) vec_result.speed,
			255,
			5.0f,
			120.0f
			));

		pcontrol_test_print_update(result_target.echo_avg, args_target.mm_target);

		go(vec_result);

		if(result_target.end_condition_count > 2)
			break;
	}
	
}


void pcontrol_test()
{
	lcd_print_top("Hug Right / P Fr");
	// roomba(DIRECTION_ID_LEFT);
	pcontrol_test_helper(100);
	pcontrol_test_helper(200);
	pcontrol_test_helper(300);
	pcontrol_test_helper(400);
	pcontrol_test_helper(500);

}

void test_loop()
{
	#if defined(TEST_DRIVE_STOP)
		lcd_print_top("Im stopped!");
		go_stop();
	#elif defined(TEST_DRIVE_DIAG)
		diag_test();
	#elif defined(TEST_DRIVE_CARD)
		card_test();
	#elif defined(TEST_SWITCH)
		switch_test();
	#elif defined(TEST_LOGIC_SWITCH)
		logic_switch_test();	
	#elif defined(TEST_ECHO)
		echo_test();
	#elif defined(TEST_CONVEYOR_INDEXER)
		conveyors_indexer_test();
	#elif defined(TEST_LCD)
		lcd_test();
	#elif defined(TEST_FLYWHEEL)
		flywheel_test();
	#elif defined(TEST_PCONTROL)
		pcontrol_test();
	#endif
}

#endif
