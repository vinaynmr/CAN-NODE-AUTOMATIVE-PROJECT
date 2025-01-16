/*
 * File:   mode.c
 * Author: VINAY
 *
 * Created on 26 December, 2024, 4:15 PM
 */


#include "main.h"
#include "adc.h"
#include "can.h"
#include "clcd.h"
#include "matrix_keypad.h"

void mode_menu() {
    if (mode_menu_flag) {
        if (config_mode_flag)
            set_node_id();
        else
            threshold_menu();
    } else {
        if (config_mode_flag)
            clcd_print("->", LINE1(0));
        else
            clcd_print("->", LINE2(0));
        clcd_print("SET NODE ID", LINE1(3));
        clcd_print("SET THRESHOLD", LINE2(3));
        if (key == MK_SW1) {
            config_mode_flag = 1;
            CLEAR_DISP_SCREEN;
        } else if (key == MK_SW2) {
            config_mode_flag = 0;
            CLEAR_DISP_SCREEN;
        }
        if (key == MK_SW11) {
            mode_menu_flag = 1;
            CLEAR_DISP_SCREEN;
        } else if (key == MK_SW12) {
            mode_flag = 0;
            CLEAR_DISP_SCREEN;
        }
    }
}

void threshold_menu() {
    if (threshold_flag) {
        if (threshold_mode_flag)
            set_temp_threshold();
        else
            set_fuel_threshold();
    } else {
        clcd_print("ENGINE TEMP", LINE1(3));
        clcd_print("ENGINE FUEL", LINE2(3));
        if (threshold_mode_flag)
            clcd_print("->", LINE1(0));
        else
            clcd_print("->", LINE2(0));
        if (key == MK_SW1) {
            threshold_mode_flag = 1;
            CLEAR_DISP_SCREEN;
        } else if (key == MK_SW2) {
            threshold_mode_flag = 0;
            CLEAR_DISP_SCREEN;
        }
        if (key == MK_SW11){
            threshold_flag = 1;
            CLEAR_DISP_SCREEN;
        }
        if (key == MK_SW12){
            mode_menu_flag = 0;
            CLEAR_DISP_SCREEN;
        }
    }
}
