/*
 * File:   main.c
 * Author: VINAY
 *
 * Created on 26 December, 2024, 3:33 PM
 */


#include "main.h"
#include "adc.h"
#include "can.h"
#include "clcd.h"
#include "matrix_keypad.h"
#include "i2c.h"
#include "ext_eeprom.h"

void init_config() {
    init_clcd();
    init_matrix_keypad();
    init_adc();
    init_can();
    init_i2c();
}
int temp1;
void main(void) {
    init_config();
    while (1) {
            if (can_receive()) {
                unsigned int k = 6, count = 0;
                for (int i = D0; i <  (D0 + 4); i++) {
                    if (can_payload[i] == read_external_eeprom(k++)) {
                        count++;
                    }
                }
                if (count == 4) {
                    CLEAR_DISP_SCREEN;
                    can_payload[0] = (temp1 / 10) + 48; /* DataByte 0 */
                    can_payload[1] = (temp1 % 10) + 48; /* DataByte 1 */
                    can_payload[2] = (fuel / 100) + 48; /* DataByte 2 */
                    can_payload[3] = ((fuel / 10) % 10) + 48; /* DataByte 3 */
                    can_payload[4] = (fuel % 10) + 48; /* DataByte 4 */
                    can_payload[5] = index + 48; /* DataByte 5 */
                    can_payload[6] = (speed / 10) + 48; /* DataByte 6 */
                    can_payload[7] = (speed % 10) + 48;
                    CLEAR_DISP_SCREEN;
                    can_transmit();
                    clcd_print("DATA SENT ",LINE1(0));
                    clcd_print("     SERVER",LINE2(0));
                    for(unsigned int long wait = 50000; wait--;);
                    CLEAR_DISP_SCREEN;
                }
            }
        key = read_switches(STATE_CHANGE);
        if (mode_flag) {
            mode_menu();
        } else {
            dashboard();
            if (key == MK_SW3) {
                index = !index;
            }else if (key == MK_SW11) {
                mode_flag = 1;
                CLEAR_DISP_SCREEN;
            }
        }
    }
    return;
}

void dashboard() {
    if (one_time_flag) {
        thresh_temp = read_external_eeprom(0) - 48;
        thresh_temp = (thresh_temp * 10) + (read_external_eeprom(1) - 48);
        thresh_temp = (thresh_temp * 10) + (read_external_eeprom(2) - 48);
        thresh_fuel = read_external_eeprom(3) - 48;
        thresh_fuel = (thresh_fuel * 10) + (read_external_eeprom(4) - 48);
        thresh_fuel = (thresh_fuel * 10) + (read_external_eeprom(5) - 48);
        node_id = read_external_eeprom(6) - 48;
        node_id = (node_id * 10) + (read_external_eeprom(7) - 48);
        node_id = (node_id * 10) + (read_external_eeprom(8) - 48);
        node_id = (node_id * 10) + (read_external_eeprom(9) - 48);
        one_time_flag = 0;
    }
    if (key == MK_SW1 && fuel < 100) {
        fuel += 10;
    } else if (key == MK_SW2 && fuel > 0) {
        fuel -= 10;
    }
    clcd_print(" ET   FL  SB  SP", LINE1(0));
    reg_val = read_adc(CHANNEL6);
    if (delay++ == 200) {
        delay = 0;
        volt = reg_val * 0.0048;
        volt = volt * 1000;
        volt /= 10;
        temp1=volt;
    }
    clcd_putch(((int) volt / 10) + 48, LINE2(0));
    clcd_putch(((int) volt % 10) + 48, LINE2(1));
    clcd_print("*c ", LINE2(2));
    clcd_putch((fuel / 100) + 48, LINE2(5));
    clcd_putch(((fuel / 10) % 10) + 48, LINE2(6));
    clcd_putch((fuel % 10) + 48, LINE2(7));
    clcd_print("% ", LINE2(8));
    clcd_print(seat_belt[index], LINE2(10));
    speed = read_adc(CHANNEL4) / 10.24;
//    clcd_putch((speed / 100) + 48, LINE2(13));
    clcd_putch((speed / 10) + 48, LINE2(14));
    clcd_putch((speed % 10) + 48, LINE2(15));

    if (fuel < thresh_fuel || thresh_temp < temp1 || speed > 90) {
        can_payload[0] = 'E'; /* DataByte 0 */
        can_payload[1] = 'R'; /* DataByte 1 */
        can_payload[2] = 'R'; /* DataByte 2 */
        can_payload[3] = 'O'; /* DataByte 3 */
        can_payload[4] = 'R'; /* DataByte 4 */
        can_payload[5] = 0; /* DataByte 5 */
        can_payload[6] = 0; /* DataByte 6 */
        can_payload[7] = 0;
        can_transmit();
    }
}
