/* 
 * File:   main.h
 * Author: VINAY
 *
 * Created on 26 December, 2024, 3:33 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include<xc.h>

#define TRUE 1
#define FALSE 0

unsigned char key;
unsigned int speed = 0, temp = 0, reg_val = 0, delay = 0;
float volt;

unsigned int mode_flag = 0,config_mode_flag = 1,mode_menu_flag = 0;
unsigned int threshold_flag = 0,threshold_mode_flag = 1;

unsigned int thresh_temp = 0,thresh_fuel = 0,node_id = 0;
unsigned int thresh_temp_flag = 1,thresh_fuel_flag = 1,node_id_flag = 1,one_time_flag = 1;


unsigned char *seat_belt[] = {"ON ","OFF"};
unsigned int fuel = 80,index = 1;

void dashboard();
void mode_menu();
void set_node_id();
void threshold_menu();
void set_temp_threshold();
void set_fuel_threshold();

#endif	/* MAIN_H */

