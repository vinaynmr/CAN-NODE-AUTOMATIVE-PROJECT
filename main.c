/*
 * File:   main.c
 * Author: VINAY
 *
 * Created on 6 January, 2025, 5:19 PM
 */


#include "main.h"
#include "can.h"
#include "clcd.h"
#include "matrix_keypad.h"

void init_config() {
    init_can();
    init_clcd();
    init_matrix_keypad();
}

void main(void) {
    init_config();
    while (1) {
        if (can_receive()) {
            if (can_payload[D0] >= 48 && can_payload[D0] <= 57) {
                flag = 1;
                CLEAR_DISP_SCREEN;
            } else {
                    clcd_print("WARNING:  ", LINE1(0));
                    clcd_print("LIMIT ERROR", LINE2(0));
                    for(unsigned long int wait = 500000;wait--;);
            }

        }
        key = read_switches(STATE_CHANGE);
        if (flag) {
            clcd_print(" ET   FL  SB  SP", LINE1(0));
            clcd_putch(can_payload[D0], LINE2(0));
            clcd_putch(can_payload[D1], LINE2(1));
            clcd_print("*c ", LINE2(2));
            clcd_putch(can_payload[D2], LINE2(5));
            clcd_putch(can_payload[D3], LINE2(6));
            clcd_putch(can_payload[D4], LINE2(7));
            clcd_print("% ", LINE2(8));
            if(can_payload[D5] == '1')
                clcd_print("OFF ",LINE2(10));
            else
                clcd_print("ON  ",LINE2(10));
            clcd_putch(can_payload[D6], LINE2(14));
            clcd_putch(can_payload[D7], LINE2(15));
            if (key == MK_SW12)
                flag = 0;
        } else {
            if (key == MK_SW1 && node_flag == 0 && node1 < 8) {
                node1++;
            } else if (key == MK_SW1 && node_flag == 1 && node2 < 8) {
                node2++;
            } else if (key == MK_SW1 && node_flag == 2 && node3 < 8) {
                node3++;
            } else if (key == MK_SW1 && node_flag == 3 && node4 < 8) {
                node4++;
            }


            if (key == MK_SW2 && node_flag == 0 && node1 > 0) {
                node1--;
            } else if (key == MK_SW2 && node_flag == 1 && node2 > 0) {
                node2--;
            } else if (key == MK_SW2 && node_flag == 2 && node3 > 0) {
                node3--;
            } else if (key == MK_SW2 && node_flag == 3 && node4 > 0) {
                node4--;
            }

            if (key == MK_SW11) {
                if (node_flag < 3)
                    node_flag++;
                else
                    node_flag = 0;
            }
            clcd_print("NODE ID:", LINE1(0));
            clcd_putch(node1 + 48, LINE2(0));
            clcd_putch(node2 + 48, LINE2(1));
            clcd_putch(node3 + 48, LINE2(2));
            clcd_putch(node4 + 48, LINE2(3));
            if (key == MK_SW3) {
                can_payload[D0] = node1 + 48;
                can_payload[D1] = node2 + 48;
                can_payload[D2] = node3 + 48;
                can_payload[D3] = node4 + 48;
                can_transmit();
                CLEAR_DISP_SCREEN;
                clcd_print("SENT REQUEST!", LINE1(0));
                for (unsigned long int wait = 500000; wait--;);
                CLEAR_DISP_SCREEN;
            }
        }
    }
    return;
}
