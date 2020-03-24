#include "aim.h"
#include "collect.h"
#include "drive.h"
#include "echo.h"
#include "inotime.h"
#include "lcd.h"
#include "shoot.h"
#include "switch.h"
#include "wheel.h"

const char* const init_message = "Init.......";
const char* const success_message = " success! :) ";

void main_setup()
{
    lcd_init();

    lcd_print_top(init_message);

    wheel_init();
    switch_init();
    drive_init();
    echo_init();
    collect_init();
    shoot_init();

    lcd_print_bot(success_message);
}

int num = 0;

void simple_aim_n_shoot()
{
    aim_location_t loc;
    char buf[17] = "Gonna Shoot #";
    long time_start;

    loc = aim_select_location();
    if (loc < 1 || loc > 3) loc = aim_select_location();
    if (loc < 1 || loc > 3) loc = aim_select_location();
    if (loc < 1 || loc > 3) loc = aim_select_location();
    if (loc < 1 || loc > 3) loc = aim_select_location();
    if (loc < 1 || loc > 3) loc = aim_select_location();
    if (loc < 1 || loc > 3) loc = aim_select_location();
    if (loc < 1 || loc > 3) loc = ((num++) % 3) + 1;

    buf[12] = loc + '0';
    lcd_print_top(buf);
    aim(loc);
    go_stop();
    // shoot_flywheel_both_start();
    // shoot_conveyor_both_start();
    // shoot_indexer_start();

    time_start = inomillis();

    while (inomillis() - time_start < 2000)
    {
        // shoot_indexer_spam_forward();
        inodelay(10);
    }
    lcd_print_bot("Pew! Pew! Pew!");

    shoot_indexer_stop();
    shoot_flywheel_both_stop();
    shoot_conveyor_both_stop();
}

void main_game_a_loop(void)
{
    // go_stop();
    // shoot_flywheel_both_stop();
    // shoot_conveyor_both_stop();
    // shoot_indexer_stop();
    // while(switch_test_up(DIRECTION_ID_FRONT))
    // {
    //     delay(10);
    // }

    // shoot_indexer_start();

    // delay(2000);

    // shoot_indexer_stop();

    // go_stop();
    // go_right();
    // delay(500);
    // go_stop();
    // delay(5000);

    while (1)
    {
        collection_victory_lap();
        // collection_victory_lap();
        go_stop();
        simple_aim_n_shoot();
    }
}

void main_loop()
{
    go_stop();

    main_game_a_loop();
}
