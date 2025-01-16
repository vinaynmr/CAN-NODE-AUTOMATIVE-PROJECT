/*
 * File:   threshold.c
 * Author: VINAY
 *
 * Created on 26 December, 2024, 4:48 PM
 */


#include "adc.h"
#include "can.h"
#include "clcd.h"
#include "main.h"
#include "matrix_keypad.h"
#include "i2c.h"
#include "ext_eeprom.h"

void set_temp_threshold()
{
    if(one_time_flag)
    {
//        write_external_eeprom(0,48);
//        write_external_eeprom(1,48);
//        write_external_eeprom(2,48);
        thresh_temp = read_external_eeprom(0) - 48;
        thresh_temp = (thresh_temp *10) + (read_external_eeprom(1) - 48);
        thresh_temp = (thresh_temp *10) + (read_external_eeprom(2) - 48);
        one_time_flag = 0;
    }
    clcd_print("ENGINE TEMP:",LINE1(0));
    clcd_print("THRESHOLD ->",LINE2(0));
    if(key == MK_SW1){ //&& thresh_temp < 1000){
        thresh_temp++;
        CLEAR_DISP_SCREEN;
    }else if(key ==  MK_SW2 && thresh_temp > 0){
        thresh_temp--;
        CLEAR_DISP_SCREEN;
    }
    clcd_putch((thresh_temp / 100) + 48,LINE2(13));
    clcd_putch((thresh_temp / 10) + 48,LINE2(14));
    clcd_putch((thresh_temp % 10) + 48,LINE2(15));
    if(key == MK_SW11)
    {
        write_external_eeprom(0,(thresh_temp / 100) + 48);
        write_external_eeprom(1,(thresh_temp / 10) + 48);
        write_external_eeprom(2,(thresh_temp % 10) + 48);
        thresh_temp = 0;
        threshold_flag = 0;
        one_time_flag = 1;
        CLEAR_DISP_SCREEN;
    }else if (key == MK_SW12){
        threshold_flag = 0;
        thresh_temp = 0;
        one_time_flag = 1;
        CLEAR_DISP_SCREEN;
    }
}

void set_fuel_threshold()
{
    if(one_time_flag)
    {
//        write_external_eeprom(3,48);
//        write_external_eeprom(4,48);
//        write_external_eeprom(5,48);
        thresh_fuel = read_external_eeprom(3) - 48;
        thresh_fuel = (thresh_fuel * 10) + (read_external_eeprom(4) - 48);
        thresh_fuel = (thresh_fuel * 10) + (read_external_eeprom(5) - 48);
        one_time_flag = 0;
    }
    clcd_print("ENGINE FUEL:",LINE1(0));
    clcd_print("THRESHOLD ->",LINE2(0));
    if(key == MK_SW1 && thresh_fuel < 100){
        thresh_fuel++;
        CLEAR_DISP_SCREEN;
    }else if(key ==  MK_SW2 && thresh_fuel > 0){
        thresh_fuel--;
        CLEAR_DISP_SCREEN;
    }
    clcd_putch((thresh_fuel / 100) + 48,LINE2(13));
    clcd_putch((thresh_fuel / 10) + 48,LINE2(14));
    clcd_putch((thresh_fuel % 10) + 48,LINE2(15));
    if(key == MK_SW11)
    {
        write_external_eeprom(3,(thresh_fuel / 100) + 48);
        write_external_eeprom(4,(thresh_fuel / 10) + 48);
        write_external_eeprom(5,(thresh_fuel % 10) + 48);
        threshold_flag = 0;
        thresh_fuel = 0;
        one_time_flag = 1;
        CLEAR_DISP_SCREEN;
    }else if (key == MK_SW12){
        threshold_flag = 0;
        thresh_fuel = 0;
        one_time_flag = 1;
        CLEAR_DISP_SCREEN;
    }
}

void set_node_id()
{
    if(one_time_flag)
    {
//        write_external_eeprom(6,48);
//        write_external_eeprom(7,48);
//        write_external_eeprom(8,48);
//        write_external_eeprom(9,48);
        node_id = read_external_eeprom(6) - 48;
        node_id = (node_id *10) + (read_external_eeprom(7) - 48);
        node_id = (node_id *10) + (read_external_eeprom(8) - 48);
        node_id = (node_id *10) + (read_external_eeprom(9) - 48);
        one_time_flag = 0;
    }
    clcd_print("SET NODE ID:",LINE1(0));
    if(key == MK_SW1 && node_id < 1000){
        node_id++;
        CLEAR_DISP_SCREEN;
    }else if(key ==  MK_SW2 && node_id > 0){
        node_id--;
        CLEAR_DISP_SCREEN;
    }
    clcd_putch((node_id / 1000) + 48,LINE2(0));
    clcd_putch((node_id / 100) + 48,LINE2(1));
    clcd_putch((node_id / 10) + 48,LINE2(2));
    clcd_putch((node_id % 10) + 48,LINE2(3));
    if(key == MK_SW11)
    {
        write_external_eeprom(6,(node_id / 1000) + 48);
        write_external_eeprom(7,(node_id / 100) + 48);
        write_external_eeprom(8,(node_id / 10) + 48);
        write_external_eeprom(9,(node_id % 10) + 48);
        mode_menu_flag = 0;
        node_id = 0;
        one_time_flag = 1;
        CLEAR_DISP_SCREEN;
    }else if (key == MK_SW12){
        mode_menu_flag = 0;
        node_id = 0;
        one_time_flag = 1;
        CLEAR_DISP_SCREEN;
    }
}


