/* USER CODE BEGIN Header */
/**
	******************************************************************************
	* @file           : main.c
	* @brief          : Main program body
	******************************************************************************
	* @attention
	*
	* Copyright (c) 2022 STMicroelectronics.
	* All rights reserved.
	*
	* This software is licensed under terms that can be found in the LICENSE file
	* in the root directory of this software component.
	* If no LICENSE file comes with this software, it is provided AS-IS.
	*
	******************************************************************************
	*/
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "i2c.h"
#include "iwdg.h"
#include "tim.h"
#include "usart.h"
#include "wwdg.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "math.h"
#include "string.h"
#include <stdlib.h>
#include "ee24.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define FLASH_STORAGE 0x08005000
#define page_size 0xA0
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
int cms_error_count;
int reset_count;
int a9g;
char send_string[50];
uint8_t rx_buffer1[300] = { 0 };
int rx_index1 = 0;
uint8_t rx_data1 = 0;
int count_interupts;
char input1[250] = { 0 };
char input2[250] = { 0 };
char input3[250] = { 0 };
char input4[250] = { 0 };
char input5[250] = { 0 };
char input6[250] = { 0 };
char input7[250] = { 0 };
char sms1[250] = { 0 };
char lcd_show[100];
char char_test1[300];
char lcd_char1[200];
int a9g_state = 0;
char atcammand_char[200];
int shomaresh_config;
int reset_micro = 0;
int reset_micro_count = 0;
int model_simcard;
//////sms////
int sms_chek_count; //baraye hazf payam bade 2bar chek kardan
char server_number[20] = "+989372425086";
char server_number2[20] = "+989114764806";
char input_number[50];
char send_number[20];
char sms_text[150];

int number_count_save;
char str_cut[50];
char sms[100];

int number = 5;

char str[250];
char test[270];
int i;
int uart;

//***gps***
int gpsrd;
int count_gps_read;
int gps_state;
char location[20];
char location1[20];
//char speed[5];
char location_n[10];
char location_e[10];
int loc_n;
int loc_e;
char speed[10];
int speed1;
int read_gps;
char gps_signal[5];
int gps_signal1;
char gps_signal_state1[5];
char gps_signal_state2[5];
int gps_signal_count;
int gps_error_count;
int gps_test_time;
int gps_test_count;
int gps_test_ok;
//***gprs***
int gprs = 0;
int gprs_timer;
int first_time_gprs;
int gprsrd;
char net_date[60];
int gprs_error_count; // baraye chek kardan ersal 20 sanie gprs
int gprs_error_count2; // baraye chek kardan ersal 60 sanie gprs
int send_error_count1;
int send_error_count2;
int send_error_count3; // ersal payam entezar bade moshkel dar shabake
int gprs_history_count=500; // timer baraye zakhire location history
int gprs_history;
//***check***//
int chek;
int chek_count;
int chek_count2;
int anten;
//***adc***//
uint16_t battery_adc[11];
int voltag_battery;
int battery_adc2;
int battry_count;
long voltag_battery1;
//**power**//
int power_sms_count;
int gps_led_count; // led gps
//***security****
int security;
int avcc_count;
int avcc_state;
int door_input_count;
//****sleep_mode*****//
int sleep_mode;
int input_power;
int input_power_count;
int chek_power_state;
int sleep_mode_timer;
int read_gps_sleep_count; //khandan location bad az yek zamani
//***rele***
int rele_state;
//a9g start
int a9g_start_error;
int a9g_ready;
//sim chek
int chek_sim_count;
int chek_sim_time;
int chek_sim_eror;
int chek_sim_ok;
uint8_t len;

int check_point1; //chek kardan sms
int check_point2;
int check_point_count;

int battery_count;

//////distance mode****
int distance_count;
int distance_user;
int distance_state;
int dis1; //baraye location mabda dar halate distance
int dis2;
int dis_warning;
int dis_warning_count;
//loc1_main
char loc_1[30];
int flat_loc1;
int flon_loc1;
char flat1_loc1[10];
char flon1_loc1[10];

//loc2_input
char loc_2[20];
int flat_loc2;
int flon_loc2;
char flat1_loc2[10];
char flon1_loc2[10];
int distance_;
int avcc_alarm;

int speed_user;
int speed_state;
int speed_count1;
int speed_count2;
int speed_gps;
int count_ok_loc; //daryaft doroste chand location
int ok_loc;
int red_led_count;

int sim_error_count1;
//eeprom_24hc01
uint8_t pass1[10];
char pass[10];
uint8_t security_save1[5];
char security_save[5];
uint8_t sleep_mode_save1[5];
char sleep_mode_save[5];
uint8_t rele_state_save1[5];
char rele_state_save[5];
uint8_t distance_user_save1[7];
char distance_user_save[7];
uint8_t distance_state_save1[5];
char distance_state_save[5];
uint8_t speed_user_save1[5];
char speed_user_save[5];
uint8_t speed_state_save1[5];
char speed_state_save[5];
uint8_t number11[20];
char number1[20];
uint8_t number22[20];
char number2[20];
uint8_t number33[20];
char number3[20];
uint8_t number44[20];
char number4[20];
uint8_t id1[20];
char id[20];
uint8_t avcc_alarm_save1[5];
char avcc_alarm_save[5];
uint8_t battry_count_char1[5];
char battry_count_char[5];
uint8_t gprs_save1[5];
char gprs_save[5];
uint8_t auto_security_save1[5];
char auto_security_save[5];
uint8_t car_mode1[5];
char car_mode[5];
uint8_t auto_security_time_save1[5];
char auto_security_time_save[5];
uint8_t loc_save1[22];
char loc_save[22];
uint8_t car_number1[20];
char car_number[20];

int  auto_security_time;

int change_eeprom;
char eeprom_save_char[200];
int read_eeprom_count1;
int read_eeprom_count2;
int read_eeprom = 0;
int eeprom_error;
int eeprom_error2;
int eep_ok;
int eeprom_ic;

int security_on_timer;
int security_on_count;
int reset_sms;
int security_state;
int security_timer_start;
int count_car_off2;
int count_car_off3;
int count_test;
int loc_save_count;
char location_save2[20];
int loc_error;
int power_error;
int loc_save_eeprom;
int save_count;
int user_first;
int gprs_always;
int hang;
int sleep_mode3_check;
int avcc_time;
int door_time;
int battery_send;
int anten_send;
int car_mode_count;
int warning_count_avcc;
int warning_count_door;
int warning_count_power;
int door_state;
int network_check;
int ring_reset_count;
int network_check_error;
int network_reset_count;
int ring_reset_timer;
int loc_avcc_count;
int loc_avcc_timer;
int generator_count2;
//****main check***
int main_check_time;
int main_check;
int main_check_error;

int generator_count1;
int generator_count3;

int ups_count1;
int ups_count2;
int ups_timer;

int generator_off;
int generator_off_count;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{

    //*************uart1**************
    if (huart->Instance == USART1)
    {

        rx_buffer1[rx_index1++] = rx_data1;

        if (strstr((char*) rx_buffer1, "\r\n") != NULL && rx_index1 == 2)
        {
            rx_index1 = 0;
        }
        else if (strstr((char*) rx_buffer1, "\r\n") != NULL)
        {
            ++count_interupts;
            if (count_interupts == 1)
            {
                memcpy(input1, rx_buffer1, sizeof(rx_buffer1));
            }
            if (count_interupts == 2)
            {
                memcpy(input2, rx_buffer1, sizeof(rx_buffer1));
            }
            if (count_interupts == 3)
            {
                memcpy(input3, rx_buffer1, sizeof(rx_buffer1));
            }
            if (count_interupts == 4)
            {
                memcpy(input4, rx_buffer1, sizeof(rx_buffer1));
            }
            if (count_interupts == 5)
            {
                memcpy(input5, rx_buffer1, sizeof(rx_buffer1));
            }
            if (count_interupts == 6)
            {
                memcpy(input6, rx_buffer1, sizeof(rx_buffer1));
            }
            if (count_interupts == 7)
            {
                memcpy(input7, rx_buffer1, sizeof(rx_buffer1));
                count_interupts = 0;
            }

            rx_index1 = 0;
            memset(rx_buffer1, 0, sizeof(rx_buffer1));
        }
        HAL_UART_Receive_IT(&huart1, &rx_data1, 1);
    }

    //****************uart2*******************
//	if (huart->Instance == USART2) {
//
//		rx_buffer2[rx_index2++] = rx_data2;
//
//		if (strstr((char*) rx_buffer2, "\r\n") != NULL && rx_index2 == 2) {
//			rx_index2 = 0;
//		} else if (strstr((char*) rx_buffer2, "\r\n") != NULL) {
//			memcpy(answer2, rx_buffer2, sizeof(rx_buffer2));
//			rx_index2 = 0;
//			memset(rx_buffer2, 0, sizeof(rx_buffer2));
//		}
//		HAL_UART_Receive_IT(&huart2, &rx_data2, 1);
//	}

}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

    if (htim->Instance == TIM1)
    {
        //HAL_GPIO_TogglePin(led_test_GPIO_Port, led_test_Pin);
        if (a9g == 0)
        {
            HAL_GPIO_TogglePin(led_net_GPIO_Port, led_net_Pin);
            if (a9g_state < 10)++shomaresh_config;
        }
        if (a9g == 2)
        {
            if (red_led_count == 0)
            {
                HAL_GPIO_TogglePin(led_net_GPIO_Port, led_net_Pin);
                ++sim_error_count1;
            }
            if (red_led_count == 1)
                HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_SET);
        }





        //******test cod******
        // ++count_test;
        //********read_eeprom**********
        if(eep_ok == 0 && eeprom_error == 1)++read_eeprom_count1;


        if(generator_off == 1)++generator_off_count;


        //***********main_check**********
        if(main_check == 1 ) {
            ++main_check_time;
        }

        ///distance mode//*****

        ++battery_count;
        ++reset_count;
        ++chek_count;
        ++chek_sim_time;
        //++network_reset_count;
        if(ring_reset_count>=1)++ring_reset_timer;
        if(ring_reset_timer>=60)ring_reset_count=0;



        if(avcc_alarm == 1 && HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1) {
            ++generator_count2;
        }


        if ( ups_count1 == 0 && HAL_GPIO_ReadPin(rele_GPIO_Port, rele_Pin) == 1) {

            ++ups_timer;
        }


        if (voltag_battery < 350)
            HAL_GPIO_TogglePin(led_batt_GPIO_Port, led_batt_Pin);

        if (voltag_battery >= 350)
            HAL_GPIO_WritePin(led_batt_GPIO_Port, led_batt_Pin, GPIO_PIN_SET);

        //***gps led***

        if (gprs == 0 && sleep_mode <=1)
            ++gps_test_time;


        if(sleep_mode <=1)
        {
            if (gps_led_count == 0)
            {
                HAL_GPIO_TogglePin(led_gps_GPIO_Port, led_gps_Pin);
            }

            if (gps_led_count == 1)
            {
                HAL_GPIO_WritePin(led_gps_GPIO_Port, led_gps_Pin, GPIO_PIN_SET);
            }
        }






    }
}




//****************SUBSTRING*****************
void substring(char string[200], int x, int y)
{
    memcpy(str_cut, "", sizeof(1));
    int l = y - x;
    char sub_str[50];
    for (int i = 0; i < l; i++)
    {
        sub_str[i] = string[x + i];
    }
    sub_str[l] = '\0';
    sprintf(str_cut, sub_str);
}

//******delchar*******
void removeChar(char *str, char garbage)
{

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++)
    {
        *dst = *src;
        if (*dst != garbage)
            dst++;
    }
    *dst = '\0';
}

//*****************send_atcammand*****************
void send_atcammand( char* ss2)
{
    memcpy(test, "", sizeof(1));
    strcpy(test, ss2);
    strcat(test, "\r\n");
    //  sprintf(test, test);
    // HAL_UART_Transmit(&huart1, test, strlen(test), 200);
    len = strlen (test);
    HAL_UART_Transmit(&huart1, (uint8_t *) test, len, HAL_MAX_DELAY);
}

//***************show uart*****************************
void show_uart( char *ss)
{
    strcpy(test, ss);
    strcat(test, "\r\n");
    len = strlen (test);
    HAL_UART_Transmit(&huart2, (uint8_t *) test, len, HAL_MAX_DELAY);
}

//***************show uart*****************************
void show_uart2( char *dd)
{
    strcpy(test, dd);
    len = strlen (test);
    HAL_UART_Transmit(&huart2, (uint8_t *) test, len, HAL_MAX_DELAY);
}


//***************serial.print*****************************
void serial_print( int ss1)
{
    sprintf(str, "%d", ss1);
    strcpy(test, str);
    len = strlen (test);
    HAL_UART_Transmit(&huart2, (uint8_t *) test, len, HAL_MAX_DELAY);
}

//***************serial.println*****************************
void serial_println( int ss1)
{
    sprintf(str, "%d", ss1);
    strcpy(test, str);
    strcat(test, "\r\n");
    len = strlen (test);
    HAL_UART_Transmit(&huart2, (uint8_t *) test, len, HAL_MAX_DELAY);
}


//*************void send information to server**************
void send_eeprom_server()
{
    strcpy(str,"eeprom/");
    strcat(str,id);
    strcat(str,"/");
    strcat(str,number1);
    strcat(str,"/");
    strcat(str,number2);
    strcat(str,"/");
    strcat(str,car_number);
    strcat(str,"/");
    strcat(str,sleep_mode_save);
    strcat(str,"/");
    strcat(str,speed_user_save);
    strcat(str,"/");
    strcat(str,speed_state_save);
    strcat(str,"/");
    strcat(str,gprs_save);
    strcat(str,"/");
    strcat(str,rele_state_save);
    strcat(str,"/");
    strcat(str,security_save);
    strcat(str,"/");
    strcat(str,auto_security_save);
    strcat(str,"/");
    strcat(str,auto_security_time_save);
    strcat(str,"/");
    strcat(str,car_mode);
    strcat(str,"/");
    strcat(str,loc_save);
    strcat(str,"/");
    show_uart(str);

}

//**********************************eeprom_change**********************************
void eeprom_save()
{
    show_uart("***eeprom saved***");
    //****save to eeprom****
    strcpy(id1,id);
    strcpy(sleep_mode_save1,sleep_mode_save);
    strcpy(speed_user_save1,speed_user_save);
    strcpy(speed_state_save1,speed_state_save);
    strcpy(number11,number1);
    strcpy(number22,number2);
    strcpy(gprs_save1,gprs_save);
    strcpy(loc_save1,loc_save);
    strcpy(car_number1,car_number);
    strcpy(rele_state_save1,rele_state_save);
    strcpy(security_save1,security_save);
    strcpy(auto_security_save1,auto_security_save);
    strcpy(car_mode1,car_mode);
    strcpy(auto_security_time_save1,auto_security_time_save);

    if (ee24_isConnected())
    {
        HAL_GPIO_WritePin(wp_GPIO_Port, wp_Pin, GPIO_PIN_RESET);
        HAL_Delay(300);
        ee24_eraseChip();
        HAL_Delay(300);
        ee24_write(0, id1, strlen(id1), 1000);
        HAL_Delay(100);
        ee24_write(10, number11, strlen(number11), 1000);
        HAL_Delay(100);
        ee24_write(30, number22, strlen(number22), 1000);
        HAL_Delay(100);
        ee24_write(50, car_number1, strlen(car_number1), 1000);
        HAL_Delay(100);
        ee24_write(70, sleep_mode_save1, strlen(sleep_mode_save1), 1000);
        HAL_Delay(100);
        ee24_write(75, speed_user_save1, strlen(speed_user_save1), 1000);
        HAL_Delay(100);
        ee24_write(85, speed_state_save1, strlen(speed_state_save1), 1000);
        HAL_Delay(100);
        ee24_write(90, gprs_save1, strlen(gprs_save1), 1000);
        HAL_Delay(100);
        ee24_write(95, rele_state_save1, strlen(rele_state_save1), 1000);
        HAL_Delay(100);
        ee24_write(100, security_save1, strlen(security_save1), 1000);
        HAL_Delay(100);
        ee24_write(105, auto_security_save1, strlen(auto_security_save1), 1000);
        HAL_Delay(100);
        ee24_write(110, auto_security_time_save1, strlen(auto_security_time_save1), 1000);
        HAL_Delay(100);
        ee24_write(115, car_mode1, strlen(car_mode1), 1000);
        HAL_Delay(100);
        ee24_write(120, loc_save1, strlen(loc_save1), 1000);
        HAL_Delay(300);
        HAL_GPIO_WritePin(wp_GPIO_Port, wp_Pin, GPIO_PIN_SET);
    }
    else
    {
        uint8_t sms_send = 0x1A;
        show_uart("***eeprom ic problem***");
        if(number == 6)HAL_UART_Transmit(&huart1, (uint8_t *)"AT+CMGS=\"09114764806\"\r\n", 23, 100);
        if(number == 0)HAL_UART_Transmit(&huart1, (uint8_t *)"AT+CMGS=\"09372425086\"\r\n", 23, 100);
        HAL_Delay(300);
        HAL_UART_Transmit(&huart1, (uint8_t *)"EEPROM PROBLEM", 14, 100);
        HAL_UART_Transmit(&huart1, &sms_send, 1, 100);
        HAL_Delay(500);
        number = 5;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
    }
    send_eeprom_server();
    HAL_IWDG_Refresh(&hiwdg);
}

//**************call**************//
void call()
{
    show_uart("CALL NUMBER1");
    if (number == 0)
        strcpy(send_number, server_number);
    if (number == 6)
        strcpy(send_number, server_number2);
    if (number == 1)
        strcpy(send_number, number1);
    if (number == 2)
        strcpy(send_number, number2);
    if (number == 3)
        strcpy(send_number, number3);
    if (number == 4)
        strcpy(send_number, number4);
    if (strstr(number1, "+981111111111") == NULL)
    {
        sprintf(str, "ATD");
        strcat(str, send_number);
        strcat(str, ";\r\n");
        show_uart(str);
        send_atcammand(str);
    }
    HAL_Delay(1000);
}

//*************SEND SMS***********
//*************SEND SMS***********
//*************SEND SMS***********
void send_sms()
{
    HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_RESET);

    HAL_IWDG_Refresh(&hiwdg);
    char ch[5];
    sprintf(ch, "%c", 34); //sakht char "

    if (number == 0)
        strcpy(send_number, server_number);
    if (number == 6)
        strcpy(send_number, server_number2);
    if (number == 1)
        strcpy(send_number, number1);
    if (number == 2)
        strcpy(send_number, number2);
    if (number == 3)
        strcpy(send_number, number3);
    if (number == 4)
        strcpy(send_number, number4);

    substring(send_number, 0, 13);
    //sprintf(send_number, str_cut);
    strcpy(send_number, str_cut);

    sprintf(sms, "AT+CMGS=");
    strcat(sms, ch);
    strcat(sms, send_number);
    strcat(sms, ch);
    strcat(sms, "\r\n");

    show_uart(sms);

    HAL_UART_Transmit(&huart1, (uint8_t *)sms, strlen(sms), HAL_MAX_DELAY);
    HAL_Delay(300);
    HAL_UART_Transmit(&huart1, (uint8_t *)sms_text, strlen(sms_text), HAL_MAX_DELAY);
    uint8_t sms_send = 0x1A;
    HAL_Delay(100);
    HAL_UART_Transmit(&huart1, &sms_send, 1, HAL_MAX_DELAY);
    HAL_Delay(1000);
    HAL_IWDG_Refresh(&hiwdg);
    HAL_Delay(5000);
    HAL_IWDG_Refresh(&hiwdg);

    send_atcammand("AT+CMGD=1,4");
    HAL_Delay(500);
}

//*************ALARM SMS***********
//*************ALARM SMS***********
//*************ALARM SMS***********
void alarm_sms()
{
    if (strstr(number1, "+9800000") == NULL)
    {
        number = 1;
        if (strstr(number1, "+981111111111") == NULL)
        {
            send_sms();
            HAL_Delay(1500);
        }
        number = 2;
        HAL_IWDG_Refresh(&hiwdg);
        if (strstr(number2, "+981111111111") == NULL)
        {
            send_sms();
            HAL_Delay(1500);
        }
        HAL_Delay(2000);
        number = 1;
        HAL_IWDG_Refresh(&hiwdg);
        call();
        HAL_Delay(2000);
        number = 5;
    }

}


//***SMS-CHECK
void sms_chek()
{
    //count_interupts = 0;
    show_uart("*sms_chek*");
    send_atcammand("AT+CMGR=1");
    HAL_Delay(500);
    send_atcammand("AT+CMGR=1");
}


// PATTERY MAP
void map()
{
    //return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    voltag_battery = (voltag_battery1 - 885) * (420 - 350) / (820 - 885) + 350;
}

void map2()
{
    if(voltag_battery >=420 )voltag_battery = 420;
    if(voltag_battery < 350)voltag_battery = 350;
    battery_send = (voltag_battery - 350) * (100 - 0) / (420 - 350) + 0;
    anten_send = (anten - 0) * (100 - 0) / (31 - 0) + 0;
    //sprintf(str, "Anten:%d Battery:%d" ,anten_send,battery_send);
    //show_uart(str);
}


//*********input sms_chek************
void input_sms_chek()
{

    if (check_point1 == 1)
    {
        show_uart("sms check point");
        count_interupts = 0;
        //check_point1 = 0;
        ++check_point2;
        sms_chek();
    }

    if (check_point2 >= 4)
    {
        show_uart("sms checked and delet all sms input");
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(100);
        check_point1 = 0;
        check_point2 = 0;
        number = 5;
        if (read_gps == 1)
            send_atcammand("AT+GPSRD=5");
    }

}


//****************server_eeprom_save*******************
void server_eeprom_save()
{
    //eeprom/12345678/+981111111111/+981111111111/+981111111111/1/100/0/0/0/0/1/0/1/36.1111,52.1111
    substring(char_test1, 7, 15);
    strcpy(id, str_cut);

    substring(char_test1, 16, 29);
    strcpy(number1, str_cut);

    substring(char_test1, 30, 43);
    strcpy(number2, str_cut);

    substring(char_test1, 44, 57);
    strcpy(car_number, str_cut);

    substring(char_test1, 58, 59);
    strcpy(sleep_mode_save, str_cut);

    substring(char_test1, 60, 63);
    strcpy(speed_user_save, str_cut);

    substring(char_test1, 64, 65);
    strcpy(speed_state_save, str_cut);

    substring(char_test1, 66, 67);
    strcpy(gprs_save, str_cut);
    //////////////////////////////////////////
    substring(char_test1, 68, 69);
    strcpy(rele_state_save, str_cut);

    substring(char_test1, 70, 71);
    strcpy(security_save, str_cut);

    substring(char_test1, 72, 73);
    strcpy(auto_security_save, str_cut);

    substring(char_test1, 74, 75);
    strcpy(auto_security_time_save, str_cut);

    substring(char_test1, 76, 77);
    strcpy(car_mode, str_cut);

    substring(char_test1, 78, 97);
    strcpy(loc_save, str_cut);

    eeprom_save();

}



//***internet on***
void reset_network()
{
    send_atcammand("AT+CIPSHUT");
    HAL_Delay(1000);
    send_atcammand("AT+CGATT=1");
    HAL_Delay(500);
    HAL_IWDG_Refresh(&hiwdg);
    if (model_simcard == 1)
    {
        sprintf(str, "AT+CGDCONT=1,\"IP\",\"mtnirancell\"\r\n");
        //show_uart(str);
        //send_atcammand(str);
        HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 500);
    }

    if (model_simcard == 2)
    {
        sprintf(str, "AT+CGDCONT=1,\"IP\",\"mcinet\"\r\n");
        show_uart(str);
        send_atcammand(str);
        HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 500);
    }
    HAL_Delay(500);
    HAL_IWDG_Refresh(&hiwdg);
    if (model_simcard == 1)
    {
        sprintf(str, "AT+CSTT=\"mtnirancell\",\"\",\"\"\r\n");
        HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 500);
    }

    if (model_simcard == 2)
    {
        sprintf(str, "AT+CSTT=\"mcinet\",\"\",\"\"\r\n");
        show_uart(str);
        send_atcammand(str);
        HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 500);
    }
    HAL_Delay(500);

    send_atcammand("AT+CIICR");
    HAL_Delay(1500);
    send_atcammand("AT+CGDCONT=1");
    HAL_Delay(500);
    send_atcammand("AT+CREG=2");
    HAL_Delay(100);
    HAL_IWDG_Refresh(&hiwdg);

}


void off_internet()
{
    send_atcammand("AT+CIPSHUT");
    HAL_Delay(1000);
    send_atcammand("AT+GPSRD=0");
    if (user_first == 0 )first_time_gprs = 0;
    gprs = 0;
    gps_state = 1;
    count_gps_read = 0;
    gprsrd = 0;
    send_error_count2 = 0; //khataye erasl etelaat va ersal sms
    input_power_count = 0; //chek kardan sleep mode
}

void gprs_online()
{
    if (gprs == 1 && gprsrd == 0 && a9g == 2)   // marhale 1 roshan kardan internet
    {
        HAL_IWDG_Refresh(&hiwdg);
        show_uart("TURN ON GPRS");
        HAL_Delay(50);
        gprs_error_count2 = 0;

        gprsrd = 1; //faqat yek bar ejra mishavad baraye shoro kare micro
    }

    if (gprsrd == 1 && gprs == 1 && chek == 0)   //marhale2 location gereftan
    {
        show_uart("WAIT FOR LOCATION");
        HAL_Delay(50);
        gprsrd = 2;
        gprs_error_count2 = 0;
        read_gps = 1; //khandan etelaat a9g qeir faal
        send_atcammand("AT+GPSRD=2"); //har 2 sanie nemone bardari gps
    }



    if (gprsrd == 5 && gprs == 1)   //*****data send*****
    {

        show_uart("***DATA SEND***");
        HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_RESET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_SET);
        HAL_Delay(100);
        HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_RESET);
        HAL_Delay(50);
        gprs_error_count = 0;
        gprs_error_count2 = 0;
        send_error_count1 = 0;
        send_error_count2 = 0;
        send_error_count3 = 0; //payam wait
        network_check_error = 0;
        gprsrd = 8; //aval vorodi sms chek mishavad
        //sms_chek();
        check_point1 = 1;
        user_first = 1;
        loc_avcc_count = 0; //auto loc avcc
        loc_avcc_timer = 0;//auto loc avcc
    }

    if(gprs_always == 0)
    {
        if(gprsrd == 8 && gprs_error_count2 >= 5)  // "delay for next data send
        {
            show_uart("<<<next data>>>");
            gprs_error_count2 = 0;
            gprsrd = 9;
            check_point1 = 1;
            loc_avcc_count = 0; //auto loc avcc
            loc_avcc_timer = 0;//auto loc avcc
        }
    }

    if(gprs_always == 1)
    {
        if(gprsrd == 8 && gprs_error_count2 >= 30)  // "delay for next data send
        {
            show_uart("<<<next data>>>");
            gprs_error_count2 = 0;
            gprsrd = 9;
            check_point1 = 1;
            loc_avcc_count = 0; //auto loc avcc
            loc_avcc_timer = 0;//auto loc avcc
        }
    }

    if (gprsrd == 4 && gprs == 1 && gprs_error_count >= 20)   //data not send bade 20 sanie
    {
        show_uart("DATA NOT SEND");
        HAL_Delay(50);
        gprs_error_count = 0;
        gprs_error_count2 = 0;
        ++send_error_count1;
        ++network_check_error;
        gprsrd = 9; //aval vorodi sms chek mishavad
        //sms_chek();
        check_point1 = 1;
    }

    if(network_check_error >= 5)  //reset for not response
    {
        show_uart("ERROR--->***RESET***");
        HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
        HAL_Delay(150);
        HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
        HAL_Delay(200);
        HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
        HAL_Delay(2000);
        HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
        HAL_Delay(2000);
        hang = 1;
        HAL_Delay(50000);
    }

    if (gprsrd == 10 && gprs == 1)   // data ersal shod va sms ham chek shod
    {
        gprsrd = 1;
        network_check_error = 0;
        if (gprs_history == 1 && first_time_gprs == 2)
        {
            network_check_error = 0;
            show_uart("*history done*");
            off_internet();
            gprs_timer = 0;
            gprs_history_count = 0;
            gprs_history = 0;
            user_first = 1;
            if (sleep_mode == 1)send_atcammand("AT+GPS=0");
        }
    }

    if (gprs_error_count2 >= 60 && gprs == 1)   //vaqti ke bade 60 sanie hij data az vorodi dayaft nemishavad va kolan hang mikonad
    {
        send_atcammand("AT+GPSRD=0");
        ++network_check_error;
        HAL_Delay(2000);
        if (gprsrd == 2)
            ++gps_error_count;
        if (gprsrd == 2 && gps_error_count == 3)
        {
            show_uart("gps count error");
            gps_error_count = 0;
            sprintf(sms_text, "Please wait... The GPS signal is weak ");
            number = 1;
            if (gprs_history == 0 && gprs_always == 0)
                send_sms(); //agar halat gprs history nabod sms ra befrest
            number = 5;
            HAL_Delay(200);
        }

        show_uart("#GPRS ERROR#");
        HAL_Delay(100);
        gprs_error_count = 0;
        gprs_error_count2 = 0;
        send_error_count1 = 3;
        gprsrd = 9; //aval vorodi sms chek mishavad
        //sms_chek();
        check_point1 = 1;
    }

    //moshkel dar shabake internet khamosh
    if (gprsrd == 6 && gprs == 1)
    {
        ++network_check_error;
        show_uart("NET ERROR!");
        HAL_Delay(50);
        gprs_error_count = 0;
        gprs_error_count2 = 0;
        send_error_count1++;
        gprsrd = 9; //aval vorodi sms chek mishavad
        ++send_error_count2; //network proplem counter
        ///***send sms***///
        if (send_error_count2 >= 3)   //khataye shabake 3 bar shod gprs khamosh
        {
            send_error_count2 = 0;
            sprintf(sms_text, "NETWOK PROBLEM THE INTERNET IS OFF");
            number = 1;
            if (gprs_history == 0 && gprs_always == 0)
                send_sms(); //agar halat gprs history nabod sms ra befrest
            number = 5;

            sprintf(gprs_save, "0");
            eeprom_save();
            off_internet();
            HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
            HAL_Delay(150);
            HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
            HAL_Delay(200);
            HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
            HAL_Delay(2000);
            HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
            HAL_Delay(2000);
            hang = 1;
            HAL_Delay(50000);
//                    gprs_error_count2 = 0;
//                    gprs_error_count = 0;
//                    first_time_gprs = 0;
//                    gprs_timer = 0;
//                    gprsrd = 0;
//                    gprs = 0;
        }
        //sms_chek();
        check_point1 = 1;
    }

    //******rah andazi dobare net*********//
    if (send_error_count1 >= 3 && gprs == 1)
    {
        show_uart("RESET GPRS");
        HAL_Delay(50);
        send_error_count1 = 0;
        off_internet();
        gprs_error_count2 = 0;
        gprs_error_count = 0;
        if (user_first == 0 )first_time_gprs = 0;
        gprsrd = 0;
        gprs = 1;

        ++send_error_count3; //network proplem wait
        ///***send sms***///
        if (send_error_count3 == 3)   //khataye shabake 3 bar shod ersal montazer bodan
        {
            send_error_count3 = 4;
            sprintf(sms_text, "PLEASE WAIT... NETWOK PROBLEM");
            number = 1;
            if (gprs_history == 0 && gprs_always ==0)
                send_sms(); //agar halat gprs history nabod sms ra befrest
            number = 5;
        }

        //sms_chek();
        check_point1 = 1;
    }

    //********turn off gprs**********///
    if (gprs_timer >= 1800 && gprs_always == 0)
    {
        show_uart("INTERNET OFF");
        ///***send sms***///
        sprintf(sms_text, "Internet and online location disabled");
        number = 1;
        if (gprs_history == 0)
            send_sms(); //agar halat gprs history nabod sms ra befrest
        number = 5;

        sprintf(gprs_save, "0");
        eeprom_save();

        send_error_count3 = 0;
        off_internet();
        if (user_first == 0 )first_time_gprs = 0;
        gprs_timer = 0;
        gprsrd = 0;
        gprs = 0;
        input_power_count = 0; //chek kardan halat sleep
    }
}

//***loc_history***
void gprs_hiytory()
{
    if (sleep_mode <= 1)
    {

        //**********loc_avcc*********

        if(gprs == 0 && gprs_history == 0) {

            if(avcc_state == 0 && loc_avcc_count == 2) {
                loc_avcc_count = 0;
                loc_avcc_timer = 0;
                gprs_history_count = 550;
                show_uart("loc_avcc ready to send");
            }


            if(avcc_state == 1 && loc_avcc_count == 0) {
                loc_avcc_count = 1;
                loc_avcc_timer = 0;
                show_uart("loc_avcc on");
            }

            if(loc_avcc_count ==1 && loc_avcc_timer >= 85) {
                loc_avcc_count =2;
                loc_avcc_timer = 0;
                show_uart("loc_avcc start timer");
            }

            if(loc_avcc_count == 1 && avcc_state == 0) {
                loc_avcc_count = 0;
                loc_avcc_timer = 0;
                show_uart("loc_avcc timer off");
            }

        }
        /////////////////////////////////////////////
        if (gprs_history_count >= 600 && gprs_history == 0 && gprs == 0 && gps_signal1 == 1)   // time 1800
        {
            show_uart("start history");
            gprs = 1; //gprs roshan
            gprsrd = 0; //faal kardan halate rah andazi baraye avalin bar
            gprs_timer = 0;
            send_error_count3 = 0; //sms wait problem network
            gprs_history_count = 0;
            gprs_history = 1;
            loc_avcc_count = 0;
            loc_avcc_timer = 0;
        }

        if (gprs_history_count >= 200 && gprs_history == 1)
        {
            show_uart("stop history");
            off_internet();
            gprs_timer = 0;
            gprs_history_count = 0;
            gprs_history = 0;
            if (sleep_mode == 1)send_atcammand("AT+GPS=0");
        }
    }

    if (sleep_mode == 3)
    {
        if (gprs_history_count >= 200 && gprs_history == 0 && gprs == 0 && HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1 && gps_signal1 == 1)   // time 3600
        {
            show_uart("start history");
            gprs = 1; //gprs roshan
            gprsrd = 0; //faal kardan halate rah andazi baraye avalin bar
            gprs_timer = 0;
            send_error_count3 = 0; //sms wait problem network
            gprs_history_count = 0;
            gprs_history = 1;
        }

        if (gprs_history_count >= 200 && gprs_history == 1)
        {
            show_uart("stop history");
            off_internet();
            gprs_timer = 0;
            gprs_history_count = 0;
            gprs_history = 0;
            if (sleep_mode == 1)send_atcammand("AT+GPS=0");
        }
    }
}


void send_sms_server()
{
    strcpy(sms_text, str);
    number = 0;
    send_sms();
    HAL_Delay(500);
}

//*************************************************config********************************************************************
void config()
{
    show_uart("CONFIG");

    substring(char_test1, 7, 15);
    strcpy(sms1, str_cut);
    //strcat(sms1, "\r\n");
    show_uart(sms1);

    strcpy(id, sms1);
    sprintf(number1, "+981111111111");
    sprintf(number2, "+981111111111");
    sprintf(sleep_mode_save, "0");
    sprintf(speed_user_save, "100");
    sprintf(speed_state_save, "0");
    sprintf(gprs_save, "0");
    sprintf(loc_save, "36.111111,52.111111");
    sprintf(car_number, "+981111111111");
    sprintf(rele_state_save, "0");
    sprintf(security_save, "0");
    sprintf(auto_security_save, "1");
    sprintf(car_mode, "1");
    sprintf(auto_security_time_save, "1");


    gprs = 0;
    car_mode_count = 1;
    security = 0;
    sleep_mode = 0;
    rele_state = 0;
    speed_user = 100;
    speed_state = 0;
    security_on_timer=1;
    reset_sms=1;
    auto_security_time = 300;

    //****save to eeprom****
    strcpy(id1,id);
    strcpy(sleep_mode_save1,sleep_mode_save);
    strcpy(speed_user_save1,speed_user_save);
    strcpy(speed_state_save1,speed_state_save);
    strcpy(number11,number1);
    strcpy(number22,number2);
    strcpy(gprs_save1,gprs_save);
    strcpy(loc_save1,loc_save);
    strcpy(car_number1,car_number);
    strcpy(rele_state_save1,rele_state_save);
    strcpy(security_save1,security_save);
    strcpy(auto_security_save1,auto_security_save);
    strcpy(car_mode1,car_mode);
    strcpy(auto_security_time_save1,auto_security_time_save);

    show_uart("***CONFIG OK***");

    if (ee24_isConnected())
    {
        show_uart("data saved");
        HAL_GPIO_WritePin(wp_GPIO_Port, wp_Pin, GPIO_PIN_RESET);
        HAL_Delay(300);
        ee24_eraseChip();
        HAL_Delay(300);
        ee24_write(0, id1, strlen(id1), 1000);
        HAL_Delay(100);
        ee24_write(10, number11, strlen(number11), 1000);
        HAL_Delay(100);
        ee24_write(30, number22, strlen(number22), 1000);
        HAL_Delay(100);
        ee24_write(50, car_number1, strlen(car_number1), 1000);
        HAL_Delay(100);
        ee24_write(70, sleep_mode_save1, strlen(sleep_mode_save1), 1000);
        HAL_Delay(100);
        ee24_write(75, speed_user_save1, strlen(speed_user_save1), 1000);
        HAL_Delay(100);
        ee24_write(85, speed_state_save1, strlen(speed_state_save1), 1000);
        HAL_Delay(100);
        ee24_write(90, gprs_save1, strlen(gprs_save1), 1000);
        HAL_Delay(100);
        ee24_write(95, rele_state_save1, strlen(rele_state_save1), 1000);
        HAL_Delay(100);
        ee24_write(100, security_save1, strlen(security_save1), 1000);
        HAL_Delay(100);
        ee24_write(105, auto_security_save1, strlen(auto_security_save1), 1000);
        HAL_Delay(100);
        ee24_write(110, auto_security_time_save1, strlen(auto_security_time_save1), 1000);
        HAL_Delay(100);
        ee24_write(115, car_mode1, strlen(car_mode1), 1000);
        HAL_Delay(100);
        ee24_write(120, loc_save1, strlen(loc_save1), 1000);
        HAL_Delay(300);
        HAL_GPIO_WritePin(wp_GPIO_Port, wp_Pin, GPIO_PIN_SET);

        sprintf(sms_text, "CONFIG OK");
        send_sms();
        HAL_Delay(500);
        show_uart("***CONFIG OK***");
    }
    else
    {
        show_uart("***eeprom ic problem***");
        sprintf(sms_text, "EEPROM IC PROBLEM\r\n");
        send_sms();
        HAL_Delay(500);
        number = 5;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
    }
}

//*************************************************change_pass********************************************************************
//*************************************************change_pass********************************************************************
//*************************************************change_pass********************************************************************
void forget_pass()
{
    substring(char_test1, 2, 10);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, id) != NULL)
    {
        sprintf(sms_text, "PASSWORD:");
        strcat(sms_text, pass);
        send_sms();
        number = 5;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
    }

}
//*************************************************change_pass********************************************************************
//*************************************************change_pass********************************************************************
//*************************************************change_pass********************************************************************
void change_pass()
{
    substring(char_test1, 2, 6);
    strcpy(sms1, str_cut);
    //strcat(sms1, "\r\n");
    substring(char_test1, 21, 22);//R 1111 1111 12345678 +989025088863
    strcpy(str, str_cut);
    show_uart(str);
    if (strstr(sms1, pass) != NULL && strstr(str, "+") != NULL)
    {
        substring(char_test1, 12, 20);
        strcpy(sms1, str_cut);
        //strcat(sms1, "\r\n");
        if (strstr(sms1, id) != NULL)
        {
            substring(char_test1, 21, 34);
            strcpy(car_number, str_cut);
            show_uart(car_number);
            substring(char_test1, 7, 11);
            strcpy(sms1, str_cut);
            strcpy(pass, sms1);  ///***save new pass***///
            strcpy(number1, input_number);  ///***save new number***///
            sprintf(number2, "+981111111111");
            sprintf(number3, "+981111111111");
            sprintf(number4, "+981111111111");
            number = 1;
            sprintf(sms_text, "New user added \r\nDevice password changed");
            send_sms();
            eeprom_save();
            send_eeprom_server();
            send_sms_server();
            number = 5;
            gprs_history_count = 1000;
            input_power_count = 0;			//chek kardan sleep mode
            send_atcammand("AT+CMGD=1,4");
            HAL_Delay(500);
        }

    }
}

void eep_add_memb()
{
///number1 save
    //char *dest = substr(send_number, 3, 7); //number1 1

    if (number_count_save == 2)
    {
        strcpy(number2, send_number);
        eeprom_save();
    }
    if (number_count_save == 3)
    {
        strcpy(number3, send_number);
        eeprom_save();
    }
    if (number_count_save == 4)
    {
        strcpy(number4, send_number);
        eeprom_save();
    }
}

//*************************************************ADD_MEMBER********************************************************************
void add_member()
{
    if (number == 1 || number == 0 || number == 6 )
    {
        //char *dest = substr(char_test1, 2, 6);
        substring(char_test1, 2, 6);
        strcpy(sms1, str_cut);
        strcat(sms1, "\r\n");
        if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
        {
            substring(char_test1, 7, 8);
            strcpy(sms1, str_cut);
            //strcat(sms1, "\r\n");
            number_count_save = atoi(sms1); // shomare karbar baraye zakhire
            sprintf(lcd_char1, "ADD USER");
            strcat(lcd_char1, sms1);
            show_uart(lcd_char1);
            substring(char_test1, 9, 22);
            strcpy(sms1, str_cut);
            //strcat(sms1, "\r\n");
            sprintf(lcd_char1, "num:");
            strcat(lcd_char1, sms1);
            show_uart(lcd_char1);
            strcpy(send_number, sms1); //shomare telephon user
            eep_add_memb();
            number = 1;
            sprintf(sms_text, "New user number saved");
            send_sms();
            HAL_Delay(500);
            send_eeprom_server();
            send_sms_server();
            number = 5;
            send_atcammand("AT+CMGD=1,4");
            HAL_Delay(500);
        }

    }

}

//***************************send location*************************//
//***************************send location*************************//
//***************************send location*************************//
void send_location_sms()
{
    //char *dest = substr(char_test1, 2, 6);
    substring(char_test1, 2, 6);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
    {
        memcpy(sms_text, "", sizeof(1));
        if (gps_signal1 == 3 || gps_signal1 == 0)
            sprintf(sms_text, "There is no signal\r\n");
        if (gps_signal1 == 1)
            sprintf(sms_text, "The signal is excellent\r\n");
        strcat(sms_text, "www.google.com/maps/place/");
        if (gps_signal1 == 1)
        {
            strcat(sms_text, location);
            strcat(sms_text, "\r\n");
        }
        if (gps_signal1 == 3 || gps_signal1 == 0 )
        {
            strcat(sms_text, loc_save);
            strcat(sms_text, "\r\n");
        }
        strcat(sms_text, "SPEED: ");
        strcat(sms_text, speed);
        show_uart(sms_text);
        send_sms();
        number = 5;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
    }

}

void security_on()   //sms vorodi baraye roshan kardan net
{
    substring(char_test1, 3, 7);
    // sprintf(sms1, str_cut);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
    {

        sprintf(lcd_char1, "security on  ");
        show_uart(lcd_char1);
        sprintf(lcd_char1, "PASS ok  ");
        show_uart(lcd_char1);
        sprintf(sms_text, "Security mode enabled");
        show_uart(sms_text);
        send_sms();

        number = 5;
        sprintf(security_save, "1");
        eeprom_save();
        HAL_Delay(20);
        security = 1;
        avcc_count = 0;
        door_input_count = 0;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
    }

}

void security_off()   //sms vorodi baraye roshan kardan net
{
    substring(char_test1, 3, 7);
    //sprintf(sms1, str_cut);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
    {
        sprintf(sms_text, "Security mode disabled");
        show_uart(sms_text);
        send_sms();
        number = 5;
        sprintf(security_save, "0");
        eeprom_save();
        HAL_Delay(20);
        security = 0;
        avcc_count = 0;
        door_input_count = 0;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
    }

}

void sleep_on()   //sms vorodi baraye roshan kardan net
{
    substring(char_test1, 3, 7);
    // sprintf(sms1, str_cut);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, pass) != NULL || number == 0|| number == 6)
    {
        sprintf(sms_text, "Power Save Mode1 on\r\nThe GPS signal is weaker");
        send_sms();
        number = 5;
        sprintf(sleep_mode_save, "1");
        eeprom_save();
        HAL_Delay(20);
        sleep_mode = 1;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(1000);
        send_atcammand("AT+GPS=0");
        HAL_Delay(1000);
        input_power_count = 0;
    }

}

void sleep_off()   //sms vorodi baraye roshan kardan net
{
    substring(char_test1, 3, 7);
    //sprintf(sms1, str_cut);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
    {
        sprintf(sms_text, "Sleep mode off\r\nPower save mode disabled");
        send_sms();
        number = 5;
        sprintf(sleep_mode_save, "0");
        eeprom_save();
        HAL_Delay(20);
        sleep_mode = 0;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
        input_power_count = 0;
    }

}


void sleep_on2()   //sms vorodi baraye roshan kardan net
{
    substring(char_test1, 3, 7);
    //sprintf(sms1, str_cut);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
    {
        sprintf(sms_text, "Sleep mode2 on\r\nGPS is off\r\nPower save mode on");
        send_sms();
        number = 5;
        sprintf(sleep_mode_save, "2");
        eeprom_save();
        HAL_Delay(20);
        sleep_mode = 2;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
        input_power_count = 0;
    }

}

void auto_sleep()   //sms vorodi baraye roshan kardan net
{
    substring(char_test1, 3, 7);
    //sprintf(sms1, str_cut);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
    {
        sprintf(sms_text, "Auto Power save mode on\r\nGPS Signal is on when the car is on");
        send_sms();
        number = 5;
        sprintf(sleep_mode_save, "3");
        eeprom_save();
        HAL_Delay(20);
        sleep_mode = 3;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
        input_power_count = 0;
    }

}

void car_on()   //sms vorodi baraye roshan kardan mashin
{
    substring(char_test1, 3, 7);
//   sprintf(sms1, str_cut);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    //if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
    // {
    HAL_GPIO_WritePin(rele_GPIO_Port, rele_Pin, GPIO_PIN_RESET); //car is on
    sprintf(sms_text, "The Car turned on");
    send_sms();
    number = 5;
    count_car_off2 = 0;
    count_car_off3 = 0;
    sprintf(rele_state_save, "0");
    eeprom_save();
    HAL_Delay(20);
    rele_state = 0;

    send_atcammand("AT+CMGD=1,4");
    HAL_Delay(500);
    // }

}

void call_gps()
{
    sprintf(str,"");
    strcat(str,"ATD");
    if (number == 0)
        strcat(str,server_number);
    if (number == 6)
        strcat(str, server_number2);
    if (number == 1)
        strcat(str, number1);
    if (number == 2)
        strcat(str, number2);
    strcat(str, ";");
    send_atcammand(str);
    HAL_Delay(2000);
    number = 5;
    send_atcammand("AT+CMGD=1,4");
    HAL_Delay(500);
}

void reset_gps_()
{
    sprintf(sms_text, "***RESET GPS***");
    send_sms();
    number = 5;
    send_atcammand("AT+CMGD=1,4");
    HAL_Delay(500);

}

void car_off()   //sms vorodi baraye khamosh kardan mashin
{
    substring(char_test1, 3, 7);
    //sprintf(sms1, str_cut);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
    {

//            if(count_car_off2 == 0 && count_car_off3 == 0)
//                {
//                    ++count_car_off2;
//                    sprintf(sms_text, "Please resend for confirmation");
//                    send_sms();
//                    number = 5;
//                }

//            if(count_car_off2 >= 1 && count_car_off3 >= 7)
//                {
//										HAL_GPIO_WritePin(rele_GPIO_Port, rele_Pin, GPIO_PIN_SET); //car is off
//                    sprintf(sms_text, "The Car turned off");
//                    send_sms();
//                    number = 5;
//                    sprintf(rele_state_save, "1");
//                    eeprom_save();
//                    HAL_Delay(20);
//                    rele_state = 1;
//                    HAL_Delay(500);
//                    count_car_off2 = 0;
//                    count_car_off3 = 0;
//                }

        HAL_GPIO_WritePin(rele_GPIO_Port, rele_Pin, GPIO_PIN_SET); //car is off
        sprintf(sms_text, "The Car turned off");
        send_sms();
        number = 5;
        sprintf(rele_state_save, "1");
        eeprom_save();
        HAL_Delay(20);
        rele_state = 1;
        HAL_Delay(500);

        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
    }

}

//void distance_on()   //sms battery
//{
//    substring(char_test1, 3, 7);
//    // sprintf(sms1, str_cut);
//    strcpy(sms1, str_cut);
//    strcat(sms1, "\r\n");
//    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
//        {
//            substring(char_test1, 8, 12);
//            strcpy(sms1, str_cut);
//            distance_user = atoi(sms1);
//            distance_state = 1;
//            strcpy(distance_user_save, sms1);
//            sprintf(distance_state_save, "1");
//            eeprom_save();
//            sprintf(str, "DISTANCE MODE ON:%d m", distance_user);
//            show_uart(str);
//            strcpy(sms_text, str);
//            send_sms();
//            number = 5;
//            dis1 = 0; //baraye location mabda dar halate distance
//            dis2 = 0;
//            dis_warning = 0;
//            dis_warning_count = 0;
//            send_atcammand("AT+CMGD=1,4");
//            HAL_Delay(500);
//        }

//}

//void distance_off()   //sms battery
//{
//    substring(char_test1, 3, 7);
//    //sprintf(sms1, str_cut);
//    strcpy(sms1, str_cut);
//    strcat(sms1, "\r\n");
//    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
//        {
//            sprintf(distance_state_save, "1");
//            eeprom_save();
//            HAL_Delay(20);
//            distance_state = 0;
//            sprintf(str, "DISTANCE MODE OFF");
//            show_uart(str);
//            strcpy(sms_text, str);
//            send_sms();
//            number = 5;
//            dis1 = 0; //baraye location mabda dar halate distance
//            dis2 = 0;
//            dis_warning = 0;
//            dis_warning_count = 0;

//            sprintf(distance_state_save, "0");
//            eeprom_save();
//            send_atcammand("AT+CMGD=1,4");
//            HAL_Delay(500);
//        }

//}

void speed_on()   //sms battery
{
    substring(char_test1, 3, 7);
    //sprintf(sms1, str_cut);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
    {
        substring(char_test1, 8, 12);
        // sprintf(sms1, str_cut);
        strcpy(sms1, str_cut);
        speed_user = atoi(sms1);
        sprintf(speed_user_save, "%d", speed_user);
        speed_state = 1;

        //EE_WriteVariable(120, 1); //distance state
        HAL_Delay(20);
        //EE_WriteVariable(125, speed_user); //speed alarm
        HAL_Delay(20);

        //sprintf(speed_user_save, sms1);
        sprintf(speed_state_save, "1");
        eeprom_save();
        sprintf(str, "SPEED ALARM ON:%d KM", speed_user);
        show_uart(str);
        // sprintf(sms_text, str);
        strcpy(sms_text, str);
        send_sms();
        number = 5;
        speed_count1 = 0;
        speed_count2 = 0;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
    }

}

void speed_off()   //sms battery
{
    substring(char_test1, 3, 7);
    //sprintf(sms1, str_cut);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
    {
        sprintf(speed_state_save, "0");
        eeprom_save();
        HAL_Delay(20);
        speed_state = 0;
        sprintf(str, "SPEED ALARM OFF");
        show_uart(str);
        //sprintf(sms_text, str);
        strcpy(sms_text, str);
        send_sms();
        number = 5;
        speed_count1 = 0;
        speed_count2 = 0;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
    }

}


//*****************************************a9g-start******************************************
//*****************************************a9g-start******************************************
void a9g_start()
{
//**************level1_a9g check********************
    if (a9g_state == 0)
    {
        //HAL_Delay(2000);
        show_uart("A9G First Start");
        show_uart("Level1:a9g check");
        for (int i = 0; i <= 10; i++)
        {
            send_atcammand("AT");
            HAL_Delay(50);

        }

        a9g_state = 1;
        shomaresh_config = 0;
    }
//************level2***********************

//***a9g_off***
    if (a9g_state == 1 && shomaresh_config >= 3)
    {

        show_uart("Level2:a9g not response");
        show_uart("reset module - check again");
        HAL_Delay(100);
        HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
        HAL_Delay(150);
        HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
        HAL_Delay(200);
        HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
        HAL_Delay(2000);
        HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
        HAL_Delay(5000);
        send_atcammand("AT");
        HAL_Delay(50);
        send_atcammand("AT");
        HAL_Delay(50);
        send_atcammand("AT");
        HAL_Delay(50);
        send_atcammand("AT+IPR=9600");
        HAL_Delay(50);
        send_atcammand("ATE0");
        HAL_Delay(50);
        send_atcammand("AT&W");
        HAL_Delay(100);
        show_uart("RESET MICRO");
        hang = 1;
        HAL_Delay(50000);

    }

//***_a9g respons ok***
    if (a9g_state == 2)
    {
        for (int i = 0; i <= 6; i++)
        {
            HAL_GPIO_TogglePin(led_net_GPIO_Port, led_net_Pin);
            HAL_Delay(50);
        }
        show_uart("Level2:a9g response ok");
        show_uart("wait for network???");
        a9g_start_error=0;
        a9g_state = 3;
        shomaresh_config = 0;
        HAL_Delay(500);
        send_atcammand("AT+GPSRD=0");
        HAL_Delay(500);
        HAL_IWDG_Refresh(&hiwdg);
        send_atcammand("AT+GPS=0");
        HAL_Delay(500);
        send_atcammand("AT+CREG?");

    }
//************level3 - network check***********************
    if (a9g_state == 3 && shomaresh_config >= 10)
    {
        show_uart("level3: network checking!!!");
        send_atcammand("AT+CREG?");

        ++a9g_start_error;
        if(a9g_start_error >= 5)
        {
            HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
            HAL_Delay(150);
            HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
            HAL_Delay(200);
            HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
            HAL_Delay(2000);
            HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
            HAL_Delay(2000);
            hang = 1;
            HAL_Delay(50000);
        }
        shomaresh_config = 0;
    }

//************level4 - sim card model***********************
    if (a9g_state == 4)
    {
        a9g_start_error = 0;
        show_uart("level4: sim card model?");
        send_atcammand("AT+COPS?");
        shomaresh_config = 0;
        a9g_state = 5;
    }

    if (a9g_state == 5 && shomaresh_config >= 3)
    {
        show_uart("sim card error!!! - check again");
        send_atcammand("AT+COPS?");
        shomaresh_config = 0;
        ++a9g_start_error;
        if(a9g_start_error >= 10)
        {
            HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
            HAL_Delay(150);
            HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
            HAL_Delay(200);
            HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
            HAL_Delay(2000);
            HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
            HAL_Delay(2000);
            a9g_state = 1;
            a9g_start_error = 0;
        }
        shomaresh_config = 0;
    }
//************level5 - sim card model***********************
    if (a9g_state == 6)
    {
        show_uart("config a9g");
        shomaresh_config = 0;
        send_atcammand("ATE0");
        HAL_Delay(100);
        send_atcammand("AT+CMGF=1");
        HAL_Delay(100);
        send_atcammand("AT+CSMP=17,167,0,0");
        HAL_Delay(100);
        //sprintf(atcammand_char, "AT+CPMS=\"SM\",\"ME\",\"SM\"");
        send_atcammand("AT+CPMS=\"ME\",\"ME\",\"ME\"");
        HAL_Delay(100);
        send_atcammand("AT+CSCS=\"GSM\"");
        //HAL_Delay(100);
        send_atcammand("AT+CREG=2");
        HAL_Delay(100);
        send_atcammand("AT+CREG=2");
        HAL_Delay(100);
        send_atcammand("AT+CLIP=1");
        HAL_Delay(100);
        send_atcammand("AT+CMGD=1,4"); // AT+CMGD=0
        HAL_Delay(500);
        send_atcammand("AT+CLVL=5");
        HAL_Delay(100);
        send_atcammand("AT+SNFS=1");
        HAL_Delay(100);
        //**********new***************


        //**********new***************
        send_atcammand("AT+IPR=9600");
        HAL_Delay(100);
        send_atcammand("AT&W");
        HAL_Delay(100);

        a9g = 1;
        HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_SET);
        number = 5;
        a9g_start_error = 0;
        a9g_state = 10;
        battery_count = 5;
        show_uart("*a9g ready - start program*");
        battery_count = 10;
    }


}


//*********************gps_read****************//
void gps_read()
{
    //if (input_power == 1 || sleep_mode == 0) {
    if (sleep_mode == 0)
    {
        if (gprs == 0)
        {
            if (count_gps_read >= 400 && gpsrd == 0)   // time"60
            {
                read_gps = 1;
                count_gps_read = 0;
                gpsrd = 1;
                show_uart("turn on gps module");
                send_atcammand("AT+GPS=1");
                HAL_Delay(1000);
                send_atcammand("AT+GPSRD=5");
                HAL_Delay(500);
                count_interupts = 0;
            }

            if (count_gps_read >= 50 && gpsrd == 1)
            {
                gpsrd = 0;
                send_atcammand("AT+GPSRD=0");
                HAL_Delay(500);
                read_gps = 0; // baraye namayesh khoroji uart 0 bashad namayesh faal

                if (gps_signal1 == 0 || gps_signal1 == 3)   // signal not good
                {
                    count_gps_read = 390; // time again
                    show_uart("signal bad");
                }
                count_interupts = 0;
                //sms_chek();
                check_point1 = 1;
            }
        }
    }

    //*******sleep _mode gps******//
    if (gprs == 0)
    {
        if (sleep_mode == 1)
        {

            if (sleep_mode_timer >= 400 && read_gps_sleep_count == 0)   // time:400
            {
                show_uart("read gps on sleep mode");
                read_gps_sleep_count = 1; //shoro timer baraye khandan gps dar halate sleep_mode
                sleep_mode_timer = 0;
                gps_state = 1;
                count_gps_read = 0;
                read_gps = 1; // baraye namayesh khoroji uart 0 bashad namayesh faal
                send_atcammand("AT+GPS=1");
                HAL_Delay(1000);
                send_atcammand("AT+GPSRD=5");
                HAL_Delay(500);
                gpsrd = 1;
            }

            if (count_gps_read >= 150 && read_gps_sleep_count == 1)
            {
                show_uart("read gps off");
                read_gps_sleep_count = 0; //shoro timer baraye khandan gps dar halate sleep_mode
                count_gps_read = 0;
                send_atcammand("AT+GPSRD=0");
                HAL_Delay(500);
                send_atcammand("AT+GPS=0");
                HAL_Delay(1000);
                //sms_chek();
                //send_atcammand("AT+CMGD=2");
                read_gps = 0; // baraye namayesh khoroji uart 0 bashad namayesh faal
                count_interupts = 0;
                sms_chek();
                gpsrd = 0;
            }
        }

        //****************sleep_mode3_auto sleep*****************
        if(sleep_mode ==3 && HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1)
        {
            if (count_gps_read >= 400 && gpsrd == 0)   // time"60
            {
                sleep_mode3_check = 1;
                read_gps = 1;
                count_gps_read = 0;
                gpsrd = 1;
                show_uart("turn on gps module");
                send_atcammand("AT+GPS=1");
                HAL_Delay(1000);
                send_atcammand("AT+GPSRD=5");
                HAL_Delay(500);
                count_interupts = 0;
            }

            if (count_gps_read >= 50 && gpsrd == 1)
            {
                gpsrd = 0;
                send_atcammand("AT+GPSRD=0");
                HAL_Delay(500);
                read_gps = 0; // baraye namayesh khoroji uart 0 bashad namayesh faal

                if (gps_signal1 == 0 || gps_signal1 == 3)   // signal not good
                {
                    count_gps_read = 390; // time again
                    show_uart("signal bad");
                }
                count_interupts = 0;
                //sms_chek();
                check_point1 = 1;
            }
        }

        if(sleep_mode ==3 && sleep_mode3_check == 1 && HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 0)
        {
            sleep_mode3_check = 0;
            show_uart("Sowich off gps is off");
            send_atcammand("AT+GPS=0");
            HAL_Delay(1000);
            send_atcammand("AT+GPSRD=0");
            HAL_Delay(500);
            read_gps = 0;
            count_gps_read = 400;
            gpsrd = 0;
            gprs_history_count = 0;
            count_gps_read = 400;
            HAL_GPIO_WritePin(led_gps_GPIO_Port, led_gps_Pin, GPIO_PIN_RESET);
        }


    }
}

void gps_test()
{
    //if (gprs == 0) {
    if (sleep_mode == 0)
    {
        if (gps_led_count == 1)
        {
            gps_test_time = 0;
        }

        if (gps_test_time >= 600)
        {
            for (int i = 0; i < 7; i++)
            {
                HAL_GPIO_TogglePin(led_gps_GPIO_Port, led_gps_Pin);
                HAL_Delay(100);
            }
            show_uart("RESET GPS");
            gps_test_time = 0;
            send_atcammand("AT+GPSRD=0");
            HAL_Delay(2000);
            HAL_IWDG_Refresh(&hiwdg);
            send_atcammand("AT+GPS=0");
            HAL_Delay(3000);
            count_interupts = 0;
            send_atcammand("AT+GPS=1");
            HAL_Delay(2000);
        }
    }

    if (sleep_mode == 3 && HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1)
    {
        if (gps_led_count == 1)
        {
            gps_test_time = 0;
        }

        if (gps_test_time >= 600)
        {
            for (int i = 0; i < 7; i++)
            {
                HAL_GPIO_TogglePin(led_gps_GPIO_Port, led_gps_Pin);
                HAL_Delay(100);
            }
            show_uart("RESET GPS");
            gps_test_time = 0;
            send_atcammand("AT+GPSRD=0");
            HAL_Delay(2000);
            HAL_IWDG_Refresh(&hiwdg);
            send_atcammand("AT+GPS=0");
            HAL_Delay(3000);
            count_interupts = 0;
            send_atcammand("AT+GPS=1");
            HAL_Delay(2000);
        }
    }

    //}
}


//*******************eeprom read**********************
void read_eeprom_()
{
    if( read_eeprom == 1 && eeprom_error == 1 && eeprom_ic == 0) 	//***ic problem
    {
        if(read_eeprom_count1 >= 2)
        {
            show_uart("eeeprom ic problem --->check again");
            read_eeprom_count1 = 0;
            read_eeprom = 0;
            eeprom_error2 = 0;
            ++read_eeprom_count2;
        }
    }

    if( read_eeprom == 1 && eeprom_error == 1 && eeprom_ic == 1) 	//***error eeprom storage
    {
        if(read_eeprom_count1 >= 2)
        {
            show_uart("**eeprom storage empty**");
            read_eeprom_count1 = 0;
            read_eeprom = 0;
            eeprom_error2 = 0;
            ++read_eeprom_count2;
        }
    }

    if(read_eeprom_count2 >= 3 && eeprom_ic == 1)  //chek kardan bad az 3 bar khondan ic eeprom
    {
        show_uart("****config eeprom starage for first time****");
        read_eeprom_count2 = 0;
        eep_ok = 1;
        //read_eeprom = 1;
        sprintf(char_test1, "CONFIG 12345678");
        number = 0;
        config();
    }

    if(read_eeprom_count2 >= 3 && eeprom_ic == 0)  //chek kardan bad az 3 bar khondan ic eeprom
    {
        show_uart("****eeeprom ic not work****");
        eep_ok = 1;
        read_eeprom = 1;
        read_eeprom_count1 = 0;
        eeprom_ic = 0;
        a9g = 2;
    }

    if(read_eeprom == 0)
    {
        read_eeprom = 1;
        show_uart("read eeprom");
        HAL_Delay(150);
        if (ee24_isConnected())
        {
            eeprom_ic = 1;
            show_uart("ic ok");
            //***pass***
            ee24_read(0, id1, 8, 1000);
            HAL_Delay(100);
            memcpy(id, id1, sizeof(id1));
            show_uart(id);
            if (strstr(id, "12345678") == NULL)
            {
                show_uart("EEPROM DATA ERROR");
                eeprom_error = 1;
            }

            if (strstr(id, "12345678") != NULL)
            {
                //***numbers***
                ee24_read(10, number11, 13, 1000);
                HAL_Delay(100);
                memcpy(number1, number11, sizeof(number11));
                show_uart(number1);

                ee24_read(30, number22, 13, 1000);
                HAL_Delay(100);
                memcpy(number2, number22, sizeof(number22));
                show_uart(number2);

                ee24_read(50, car_number1, 13, 1000);
                HAL_Delay(100);
                memcpy(car_number, car_number1, sizeof(car_number1));
                show_uart(car_number);

                //***sleep***
                ee24_read(70, sleep_mode_save1, 1, 1000);
                HAL_Delay(100);
                memcpy(sleep_mode_save, sleep_mode_save1, sizeof(sleep_mode_save1));
                if (strstr(sleep_mode_save, "1") != NULL)
                {
                    show_uart("sleep mode on");
                    sleep_mode = 1;
                }

                if (strstr(sleep_mode_save, "0") != NULL)
                {
                    show_uart("sleep mode off");
                    sleep_mode = 0;
                }

                if (strstr(sleep_mode_save, "2") != NULL)
                {
                    show_uart("gps off sleep on");
                    sleep_mode = 2;
                }

                if (strstr(sleep_mode_save, "3") != NULL)
                {
                    show_uart("Auto sleep on");
                    sleep_mode = 3;
                }

                //********speed*********
                ee24_read(75, speed_user_save1, 3, 1000);
                HAL_Delay(100);
                memcpy(speed_user_save, speed_user_save1, sizeof(speed_user_save1));
                //show_uart(speed_user_save);
                speed_user = atoi(speed_user_save);
                sprintf(str, "SPEED ALARM:%d KM", speed_user);
                show_uart(str);

                ee24_read(85, speed_state_save1, 1, 1000);
                HAL_Delay(100);
                memcpy(speed_state_save, speed_state_save1, sizeof(speed_state_save1));
                if (strstr(speed_state_save, "1") != NULL)
                {
                    show_uart("speed alarm on");
                    speed_state = 1;
                }
                if (strstr(speed_state_save, "0") != NULL)
                {
                    show_uart("speed alarm off");
                    speed_state = 0;
                }

                //***gprs_save***
                ee24_read(90, gprs_save1, 1, 1000);
                HAL_Delay(100);
                memcpy(gprs_save, gprs_save1, sizeof(gprs_save1));
                if (strstr(gprs_save, "0") != NULL)
                {
                    show_uart("gprs off");
                    gprs = 0;
                }

                if (strstr(gprs_save, "1") != NULL)
                {
                    show_uart("gprs on");
                    gprs = 1;
                }

                if (strstr(gprs_save, "2") != NULL)
                {
                    show_uart("gprs always on");
                    gprs = 1;
                    gprs_always = 1;
                }
                //***rele state***
                ee24_read(95, rele_state_save1, 1, 1000);
                HAL_Delay(100);
                memcpy(rele_state_save, rele_state_save1, sizeof(rele_state_save1));
                if (strstr(rele_state_save, "0") != NULL)
                {
                    show_uart("car on");
                    HAL_GPIO_WritePin(rele_GPIO_Port, rele_Pin, GPIO_PIN_RESET);
                    rele_state = 0;
                }

                if (strstr(rele_state_save, "1") != NULL)
                {
                    show_uart("car off");
                    HAL_GPIO_WritePin(rele_GPIO_Port, rele_Pin, GPIO_PIN_SET);
                    rele_state = 1;
                }

                //***security state***
                ee24_read(100, security_save1, 1, 1000);
                HAL_Delay(100);
                memcpy(security_save, security_save1, sizeof(security_save1));
                if (strstr(security_save, "0") != NULL)
                {
                    show_uart("security off");
                    security = 0;
                }

                if (strstr(security_save, "1") != NULL)
                {
                    show_uart("security on");
                    security = 1;
                }

                //***auto_security***
                ee24_read(105, auto_security_save1, 1, 1000);
                HAL_Delay(100);
                memcpy(auto_security_save, auto_security_save1, sizeof(auto_security_save1));
                if (strstr(auto_security_save, "1") != NULL)
                {
                    show_uart("auto security on");
                    security_on_timer = 1;
                }
                if (strstr(auto_security_save, "0") != NULL)
                {
                    show_uart("auto security off");
                    security_on_timer = 0;
                }

                //***auto security time_save1***
                ee24_read(110, auto_security_time_save1, 1, 1000);
                HAL_Delay(100);
                memcpy(auto_security_time_save, auto_security_time_save1, sizeof(auto_security_time_save1));
                if (strstr(auto_security_time_save, "1") != NULL)
                {
                    show_uart("auto_time 1");
                    auto_security_time = 300; // 600
                }
                if (strstr(auto_security_time_save, "2") != NULL)
                {
                    show_uart("auto_time 2");
                    auto_security_time = 600;
                }

                if (strstr(auto_security_time_save, "3") != NULL)
                {
                    show_uart("auto_time 3");
                    auto_security_time = 3600;
                }

                if (strstr(auto_security_time_save, "4") != NULL)
                {
                    show_uart("auto_time 4");
                    auto_security_time = 7200;
                }

                if (strstr(auto_security_time_save, "5") != NULL)
                {
                    show_uart("auto_time 5");
                    auto_security_time = 10800;
                }

                if (strstr(auto_security_time_save, "6") != NULL)
                {
                    show_uart("auto_time 6");
                    auto_security_time = 14400;
                }

                if (strstr(auto_security_time_save, "7") != NULL)
                {
                    show_uart("auto_time 7");
                    auto_security_time = 18000;
                }


                //***reset sms save***
                ee24_read(115, car_mode1, 1, 1000);
                HAL_Delay(100);
                memcpy(car_mode, car_mode1, sizeof(car_mode1));
                if (strstr(car_mode, "1") != NULL)
                {
                    show_uart("CAR MODE");
                    car_mode_count = 1;
                }
                if (strstr(car_mode, "0") != NULL)
                {
                    show_uart("MOTORCYCLE mode");
                    car_mode_count = 0;
                }
                //***location_save***
                ee24_read(120, loc_save1, 19, 1000);
                HAL_Delay(100);
                memcpy(loc_save, loc_save1, sizeof(loc_save1));
                show_uart(loc_save);

                read_eeprom_count1 = 0;
                eep_ok = 1;
                read_eeprom = 0;
                eeprom_error =0;
                eeprom_error2 = 0;
                HAL_GPIO_WritePin(wp_GPIO_Port, wp_Pin, GPIO_PIN_SET);
                a9g = 2;
                strcpy(pass,"1111");

                if (sleep_mode == 1)
                {
                    sleep_mode_timer = 390;
                }

            }
        }
        else
        {
            if( eeprom_error2 == 0 )
            {
                eeprom_ic =0;
                eeprom_error2 = 1;
                eeprom_error = 1;
            }
        }
    }


}

//***************************check a9g******************************
//***************************check a9g******************************
//***************************check a9g******************************
void chek_a9g_at()
{
    if (a9g == 2 && sim_error_count1 >= 120)
    {
        show_uart("SIM CARD ERROR ----> NO SIM");
        HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
        HAL_Delay(150);
        HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
        HAL_Delay(200);
        HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
        HAL_Delay(2000);
        HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
        hang = 1;
        HAL_Delay(50000);
    }

    if (chek_count >= 20 && chek == 0 && gprsrd < 4 )
    {

        chek_count = 0;
        send_atcammand("AT");
        chek = 1;
    }

    if (chek == 1 && chek_count >= 5)
    {
        ++chek_count2;
        show_uart("A9G error");
        chek = 0;
        chek_count = 15;
        //sprintf(str, "battery voltage:%d v", voltag_battery);
        sprintf(lcd_show, "BAT=%d ANT:%d ", voltag_battery, anten);
        show_uart(lcd_show);
    }

    if (chek_count2 >= 3)
    {
        show_uart("Reset Device");
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
        hang = 1;
        HAL_Delay(50000);
    }

    if (chek == 2)
    {
        chek = 0;
        chek_count = 0;
        chek_count2 = 0;
        //cms_error_count = 0;
        show_uart("A9G OK");
        send_atcammand("AT+CSQ");
        sprintf(str, "battery voltage:%d v security timer:%ds", voltag_battery,security_on_count);
        show_uart(str);
        count_interupts = 0; //


    }

}

//********sim card chek******
void chek_sim()
{
    if (gprs == 1 ) {
        chek_sim_time = 0;
    }
    if (gprs == 0 )
    {

        if (chek_sim_time >= 250 && chek_sim_count == 0) // 500
        {
            chek_sim_time = 0;
            sprintf(atcammand_char, "AT+COPS?");
            send_atcammand(atcammand_char);
            chek_sim_count = 1;

        }

        if (chek_sim_time >= 10 && chek_sim_count == 1)
        {
            chek_sim_time = 0;
            chek_sim_count = 1;
            ++chek_sim_eror;
            show_uart("sim error");
            sprintf(atcammand_char, "AT+COPS?");
            send_atcammand(atcammand_char);
        }

        if (chek_sim_eror >= 4)
        {
            show_uart("sim error reset micro");
            HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
            HAL_Delay(150);
            HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
            HAL_Delay(200);
            HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
            HAL_Delay(2000);
            HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
            hang = 1;
            HAL_Delay(50000);
        }

        if (chek_sim_ok == 1)
        {
            show_uart("sim ok");
            chek_sim_time = 0;
            chek_sim_count = 0;
            chek_sim_eror = 0;
            chek_sim_ok = 0;
            show_uart("RESET NETWORK");
            reset_network();
        }
    }
}

void battry()   //sms battery
{
    substring(char_test1, 3, 7);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, pass) != NULL || number == 0 || number == 6)
    {
        int batt_sms;
        if (voltag_battery < 420)
            batt_sms = (voltag_battery - 360) * (100 - 0) / (420 - 360) + 0;
        if (voltag_battery > 420)
            batt_sms = 100;
        //sprintf(str, "VOLTAGE=%d", batt_sms);
        sprintf(str, "BATTERY:%d%c\r\nANTEN:%d%c", battery_send,37, anten_send,37);
        show_uart(str);
        strcpy(sms_text, str);
        send_sms();
        number = 5;
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(500);
    }

}


//**********************************BATTERY*********************************
void battery_()
{
    if (battery_count >= 2)
    {
        battery_count = 0;

        battery_adc2 = 0;
        HAL_ADC_PollForConversion(&hadc, 1000);

        for (int count_battry = 0; count_battry < 10; ++count_battry)
        {
            HAL_ADC_PollForConversion(&hadc, 1000);
            battery_adc[count_battry] = 0;
            battery_adc[count_battry] = HAL_ADC_GetValue(&hadc);
            battery_adc2 += battery_adc[count_battry];
            HAL_Delay(2);
        }

        voltag_battery1 = battery_adc2 / 10;
        map();
        map2();
        map();

//        sprintf(str, "Battery:%d",voltag_battery);
//        show_uart(str);
    }

}

//**********************************power_check*********************************
void power_chek()
{

    //******************220 qaat***********************
    if (power_sms_count == 0 && a9g == 2
            && avcc_alarm == 0 && HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1 )
    {

        HAL_Delay(500);
        if ( HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1 ) {
            generator_count1= 0 ;
            generator_count3 = 0;
            show_uart("power Disconnected trig");
            warning_count_power = 0;
            avcc_alarm = 1;
            sprintf(avcc_alarm_save, "1");
            //eeprom_save();
            HAL_Delay(20);
            HAL_IWDG_Refresh(&hiwdg);
            show_uart("POwer Disconnected");
            generator_count2 = 0;
            power_sms_count = 1; //chek kardan halate qaat bodan faqat yek bar
            chek_power_state = 0; //chek kardan halate vasl bodan faqat yek bar
            input_power_count = 0; //chek kardan halate sleep
            input_power = 0; //barq vorodi qaat
            if(  security == 1) {
                number = 1;
                sprintf(sms_text, "***Warning***\r\n INPUT POWER Disconnected");
                send_sms();
                number = 5;

                HAL_IWDG_Refresh(&hiwdg);
                if (strstr(number2, "+981111111111") == NULL)
                {
                    number = 2;
                    send_sms();
                    HAL_Delay(1500);
                }
//                if(power_error == 2)
//                {
//                    alarm_sms();
//                }
            }
        }
    }

    //******************220 vasl***********************
    if ( chek_power_state == 0 && HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 0)
    {
        HAL_Delay(500);
        if ( HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 0 ) {
            generator_count1 = 0;
            generator_count2 = 0;
            generator_count3 = 0;
            show_uart("***INPUT POWER Connected***");
            if(avcc_alarm == 1 &&  security == 1) {
                number = 1;
                sprintf(sms_text, "***INPUT POWER Connected***");
                send_sms();

                HAL_IWDG_Refresh(&hiwdg);
                if (strstr(number2, "+981111111111") == NULL)
                {
                    number = 2;
                    send_sms();
                    HAL_Delay(1500);
                }
                number = 5;


            }
            warning_count_power = 0;
            power_error = 2;
            avcc_alarm = 0;
            sprintf(avcc_alarm_save, "0");
            //eeprom_save();
            HAL_Delay(20);
            chek_power_state = 1;
            power_sms_count = 0;
            input_power = 1; //barq vorodi vasl
            input_power_count = 0;
        }

    }
//***************generator vasl*************
    if(avcc_alarm == 1 && HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 0 && generator_count1 == 0 ) {
        HAL_Delay(500);
        if(HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 0) {
            generator_count1 = 1;
            generator_count2 = 0;
            generator_count3 = 0;
            generator_off = 1;
            show_uart("***The GENERATOR turned on***");
            if(  security == 1) {
                number = 1;
                sprintf(sms_text, "***The GENERATOR turned on***");
                send_sms();
                HAL_IWDG_Refresh(&hiwdg);
                if (strstr(number2, "+981111111111") == NULL)
                {
                    number = 2;
                    send_sms();
                    HAL_Delay(1500);
                }
                number = 5;
            }
        }
    }




    if(avcc_alarm == 1 && HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 1 && generator_count1 == 1 ) {
        HAL_Delay(500);
        if(HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 1) {
            generator_count1 = 0;
            generator_count2 = 0;
            generator_count3 = 0;
            show_uart("***The GENERATOR turned on***");
            if(  security == 1) {
                number = 1;
                sprintf(sms_text, "***The GENERATOR turned off***");
                send_sms();
                HAL_IWDG_Refresh(&hiwdg);
                if (strstr(number2, "+981111111111") == NULL)
                {
                    number = 2;
                    send_sms();
                    HAL_Delay(1500);
                }
                number = 5;
            }
        }
    }

    //*******************generator qaat*********
    if(avcc_alarm == 1 && generator_count1 == 0 && generator_count2 >= 20 && generator_count3 == 0 && HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 1) {
        HAL_Delay(500);
        if(HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 1) {
            generator_count1 = 0;
            generator_count2 = 0;
            generator_count3 = 1;
            show_uart("---The GENERATOR did not turn on---");
            if(  security == 1) {
                number = 1;
                sprintf(sms_text, "***Warning***\r\n---The GENERATOR did not turn on---");
                send_sms();
                number = 5;
            }
        }
    }



    //***********************bad az vasl shodan barq check kardan generator****************
    if(generator_off == 1 && HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 0) {
        if(generator_off_count >= 60 && HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 0) {
            generator_off = 0;
            generator_off_count = 0;
					if( security == 1){
            number = 1;
            sprintf(sms_text, "*The input power is connected but the generator is still on");
            send_sms();

            HAL_IWDG_Refresh(&hiwdg);
            if (strstr(number2, "+981111111111") == NULL)
            {
                number = 2;
                send_sms();
                HAL_Delay(1500);
            }
            number = 5;
					}
        }
				
				
				//****generator khamosh shod*****
				if(HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 1){
					 generator_off = 0;
            generator_off_count = 0;
					if( security == 1){
            number = 1;
            sprintf(sms_text, "***The GENERATOR turned off***");
            send_sms();

            HAL_IWDG_Refresh(&hiwdg);
            if (strstr(number2, "+981111111111") == NULL)
            {
                number = 2;
                send_sms();
                HAL_Delay(1500);
            }
            number = 5;
					}
				}

    }

    //********ups on*********
    if ( ups_count1 == 0 && HAL_GPIO_ReadPin(rele_GPIO_Port, rele_Pin) == 1 && ups_timer >=10)
    {
        ups_timer = 0;
        ups_count1 = 1;
        show_uart("***Warning***\r\n---The UPS did not turn on---");
        if(  security == 1) {
            number = 1;
            sprintf(sms_text, "***Warning***\r\n---The UPS turned off---");
            send_sms();
            HAL_IWDG_Refresh(&hiwdg);
            if (strstr(number2, "+981111111111") == NULL)
            {
                number = 2;
                send_sms();
                HAL_Delay(1500);
            }
            number = 5;
        }
    }

    if ( ups_count1 == 1 && HAL_GPIO_ReadPin(rele_GPIO_Port, rele_Pin) == 0) {
        HAL_Delay(500);
        if(HAL_GPIO_ReadPin(rele_GPIO_Port, rele_Pin) == 0) {
            ups_count1 = 0;
            ups_timer = 0;
            show_uart("**The UPS turned on**");
            if(  security == 1) {
                number = 1;
                sprintf(sms_text, "**The UPS turned on**");
                send_sms();
                HAL_IWDG_Refresh(&hiwdg);
                if (strstr(number2, "+981111111111") == NULL)
                {
                    number = 2;
                    send_sms();
                    HAL_Delay(1500);
                }
                number = 5;
            }
        }
    }
}


void sensor_chek()
{


    //******auto_security*****
    if (security_on_timer == 1 && security == 0 )
    {
        if (HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 0 && HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 1 && a9g == 2 )
        {
            security_timer_start = 1;
            warning_count_avcc = 0;
        }

        if (HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1 || HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 0)
        {
            security_timer_start = 0;
            security_on_count=0;

        }
        //******avcc_auto_input******
        if (HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1 && security_state == 1 && a9g == 2 )
        {
            HAL_Delay(100);
            if (HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1 )++warning_count_avcc;
            if (HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1 && warning_count_avcc == 1 )
            {
                show_uart("avcc Auto input");
                HAL_Delay(50);
                number = 1;
                sprintf(sms_text, "***Warning***\r\nThe switch opened");
                send_sms();
                number = 5;
                security_state = 0;
                security_on_count = 0;
                warning_count_avcc = 0;
            }
        }

        //******door_alarm_auto_input******
        if (HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 0 && security_state == 1 && a9g == 2 )
        {
            HAL_Delay(100);
            if (HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 0)++warning_count_door;
            if (HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 0 && warning_count_door>=1)
            {
                show_uart("door alarm Auto input");
                HAL_Delay(50);
                number = 1;
                if(car_mode_count == 1)sprintf(sms_text, "***Warning***\r\nThe doors opened");
                if(car_mode_count == 0)sprintf(sms_text, "***Warning***\r\nMotorcycle movment");
                send_sms();
                number = 5;
                security_state = 0;
                security_on_count = 0;
                warning_count_door = 0;
            }
        }
    }

    //****************security avcc && door input***************
    //*******avcc input********//
    if (HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1 && security == 1
            && avcc_count == 0 && a9g == 2)
    {
        HAL_Delay(100);
        show_uart("Avcc trig");
        if (HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1 )++warning_count_avcc;

        if (HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1 &&  warning_count_avcc == 3)
        {
            avcc_count = 1;
            avcc_time = 0;
            show_uart("avcc input");
            HAL_Delay(50);
            number = 1;
            sprintf(sms_text, "***Warning***\r\nThe switch opened");
            alarm_sms();
            warning_count_avcc = 0;

        }
    }

    if (HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 0 && avcc_count == 1 && avcc_time >= 60)
    {
        avcc_time = 0;
        avcc_count = 0;
        show_uart("AVCC Closed");
        warning_count_avcc = 0;
    }

    if (HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 0)
    {
        avcc_state = 0;
        warning_count_avcc = 0;
    }

    if (HAL_GPIO_ReadPin(avcc_GPIO_Port, avcc_Pin) == 1)
        avcc_state = 1;

//********door_input********
    if (HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 0
            && security == 1 && door_input_count == 0 && a9g == 2)
    {
        show_uart("door trig");
        //HAL_Delay(50);
        if (HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 0)++warning_count_door;
        if (HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 0 && warning_count_door>=1)
        {
            door_input_count = 1;
            HAL_IWDG_Refresh(&hiwdg);
            show_uart("Door input Warning");
            HAL_Delay(50);
            if(car_mode_count == 1)sprintf(sms_text, "***Warning***\r\nThe doors opened");
            if(car_mode_count == 0)sprintf(sms_text, "***Warning***\r\nMotorcycle Movment");
            alarm_sms();
            warning_count_door = 0;
        }
    }

    if (HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 1 && door_time >= 60 && door_input_count == 1)
    {
        show_uart("door trig closed");
        door_input_count = 0;
        door_time = 0;
        warning_count_door = 0;
    }

    if (HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 1)
    {
        warning_count_door = 0;
    }

    if (HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 0)
    {
        door_state =1;
    }

    if (HAL_GPIO_ReadPin(door_input_GPIO_Port, door_input_Pin) == 1)
    {
        door_state =0;
    }

}


//*******************************sleep**********************
//*******************************sleep**********************
//*******************************sleep**********************
void sleep_()
{
    if(sleep_mode <= 1)
    {
        if (input_power == 1 && input_power_count == 0)   //barq vorodi vasl sleep qeire faal
        {
            show_uart("power on gps on");
            for (int i = 0; i <= 10; i++)
            {
                HAL_GPIO_TogglePin(led_batt_GPIO_Port, led_batt_Pin);
                HAL_GPIO_TogglePin(led_net_GPIO_Port, led_net_Pin);
                HAL_GPIO_TogglePin(led_gps_GPIO_Port, led_gps_Pin);
                HAL_Delay(100);
            }
            input_power_count = 1;
            gps_state = 1;
            read_gps = 0;
            gpsrd = 0;
            count_gps_read = 400;
            read_gps_sleep_count = 0; //khandan gps bad az zaman tey shode
            if (sleep_mode == 0)
            {
                send_atcammand("AT+GPS=1");
            }

            HAL_Delay(1000);
        }

        if (sleep_mode == 1 && input_power == 0 && input_power_count == 0)
        {
            show_uart("power off sleep mode on gps off");
            input_power_count = 1;
            gps_state = 1;
            read_gps = 0;
            gpsrd = 0;
            count_gps_read = 400;
            read_gps_sleep_count = 0; //khandan gps bad az zaman tey shode
            //sleep_mode_timer = 0; // sefr kardan zaman khndan gps da sleep mode
            // send_atcammand("AT+GPS=0");
            HAL_Delay(1000);
        }

        if (sleep_mode == 0 && input_power == 0 && input_power_count == 0)
        {
            show_uart("power off  gps on");
            input_power_count = 1;
            gps_state = 1;
            read_gps = 0;
            gpsrd = 0;
            read_gps_sleep_count = 0; //khandan gps bad az zaman tey shode
            count_gps_read = 400;
            send_atcammand("AT+GPS=1");
            HAL_Delay(1000);
        }
    }

    //******sleep mode2*****
    if(sleep_mode == 2 && gprs == 0)
    {
        if ( input_power_count == 0)
        {
            show_uart("sleep mode2 on gps off");
            for (int i = 0; i <= 10; i++)
            {
                HAL_GPIO_TogglePin(led_batt_GPIO_Port, led_batt_Pin);
                HAL_GPIO_TogglePin(led_net_GPIO_Port, led_net_Pin);
                HAL_GPIO_TogglePin(led_gps_GPIO_Port, led_gps_Pin);
                HAL_Delay(100);
            }
            input_power_count = 1;
            gps_state = 0;
            read_gps = 0;
            gpsrd = 0;
            send_atcammand("AT+GPS=0");
            HAL_Delay(1000);
            send_atcammand("AT+GPRD=0");
            HAL_Delay(1000);
            HAL_GPIO_WritePin(led_gps_GPIO_Port, led_gps_Pin, GPIO_PIN_RESET);
        }
    }

    if(sleep_mode == 2 && gprs == 1)
    {
        if ( input_power_count == 0)
        {
            show_uart("sleep mode2 on gps on for gprs");
            for (int i = 0; i <= 10; i++)
            {
                HAL_GPIO_TogglePin(led_batt_GPIO_Port, led_batt_Pin);
                HAL_GPIO_TogglePin(led_net_GPIO_Port, led_net_Pin);
                HAL_GPIO_TogglePin(led_gps_GPIO_Port, led_gps_Pin);
                HAL_Delay(100);
            }
            input_power_count = 1;
            gps_state = 0;
            read_gps = 0;
            gpsrd = 0;
            //send_atcammand("AT+GPS=0");
            HAL_Delay(1000);
        }
    }



    //******sleep mode3*****
    if(sleep_mode == 3 && gprs == 0)
    {
        if ( input_power_count == 0 )
        {
            show_uart("sleep mode3 auto sleep mode");
            for (int i = 0; i <= 10; i++)
            {
                HAL_GPIO_TogglePin(led_batt_GPIO_Port, led_batt_Pin);
                HAL_GPIO_TogglePin(led_net_GPIO_Port, led_net_Pin);
                HAL_GPIO_TogglePin(led_gps_GPIO_Port, led_gps_Pin);
                HAL_Delay(100);
            }
            input_power_count = 1;
            gps_state = 0;
            read_gps = 0;
            sleep_mode3_check = 0;
            gpsrd = 0;
            count_gps_read = 400;
            send_atcammand("AT+GPS=0");
            HAL_Delay(1000);
            send_atcammand("AT+GPRD=0");
            HAL_Delay(1000);
            HAL_GPIO_WritePin(led_gps_GPIO_Port, led_gps_Pin, GPIO_PIN_RESET);
        }
    }

    if(sleep_mode == 3 && gprs == 1)
    {
        if ( input_power_count == 0)
        {
            show_uart("sleep mode3 auto sleep mode");
            for (int i = 0; i <= 10; i++)
            {
                HAL_GPIO_TogglePin(led_batt_GPIO_Port, led_batt_Pin);
                HAL_GPIO_TogglePin(led_net_GPIO_Port, led_net_Pin);
                HAL_GPIO_TogglePin(led_gps_GPIO_Port, led_gps_Pin);
                HAL_Delay(100);
            }
            input_power_count = 1;
            gps_state = 1;
            read_gps = 0;
            count_gps_read = 400;
            sleep_mode3_check = 0;
            gpsrd = 0;
            //send_atcammand("AT+GPS=0");
            HAL_Delay(1000);
        }
    }


}

void reset_()
{
    if (reset_count >= 50000 )
    {

        HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
        HAL_Delay(150);
        HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
        HAL_Delay(200);
        HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
        HAL_Delay(2000);
        HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
        hang = 1;
        HAL_Delay(50000);
    }

//    if(network_reset_count >= 4000 && gprs == 0 )
//    {
//        network_reset_count = 0;
//        show_uart("auto reset network");
//        send_atcammand("AT+CFUN=0");
//        HAL_Delay(5000);
//        send_atcammand("AT+CFUN=1");
//        HAL_Delay(5000);
//        hang=1;
//    }
}

//////////////////////////////////////////////////////////

//void distance()
//{
//    if (distance_state == 1)
//        {

//            if (dis1 == 0)   // marhale1 gereftane loc mabda
//                {
//                    if (gps_signal1 == 1 && ok_loc == 1)
//                        {
//                            dis1 = 1;
//                            // ****loc1 ****
//                            //sprintf(loc_1, location);  // ********location******
//                            strcpy(loc_1, location);
//                            substring(loc_1, 3, 7);
//                            //sprintf(flat1_loc1, str_cut);	//test
//                            strcpy(flat1_loc1, str_cut);
//                            substring(loc_1, 11, 15);
//                            //sprintf(flon1_loc1, str_cut);	//test
//                            strcpy(flon1_loc1, str_cut);
//                            flat_loc1 = atoi(flat1_loc1);
//                            flon_loc1 = atoi(flon1_loc1);
//                        }

//                }

//            if (gps_signal1 == 1 && dis1 == 1 && distance_count >= 30)
//                {
//                    distance_count = 0;
//                    // ****loc2 ****
//                    //sprintf(loc_2, location);  // ********input_location******
//                    strcpy(loc_2, location);
//                    substring(loc_2, 3, 7);
//                    // sprintf(flat1_loc2, str_cut);	//test
//                    strcpy(flat1_loc2, str_cut);
//                    substring(loc_2, 11, 15);
//                    // sprintf(flon1_loc2, str_cut);	//test
//                    strcpy(flon1_loc2, str_cut);
//                    flat_loc2 = atoi(flat1_loc2);
//                    flon_loc2 = atoi(flon1_loc2);

//                    //***calculate***
//                    long x = flat_loc1 - flat_loc2;
//                    //x= x*x;
//                    long y = flon_loc1 - flon_loc2;
//                    //y = y*y;

//                    if (x < 0)
//                        x = x * -1;
//                    if (y < 0)
//                        y = y * -1;
//                    distance_ = x + y;
//                    //distance_ = sqrt(distance_);
//                    distance_ = distance_ * 10;

//                    if (distance_ < distance_user)
//                        {
//                            dis2 = 0;
//                            dis_warning = 0;
//                            dis_warning_count = 0;
//                        }

//                    if (distance_ > distance_user && dis2 < 3)
//                        {
//                            ++dis2;
//                            if (dis2 >= 3)
//                                {
//                                    sprintf(str, "distance:%d", distance_);
//                                    show_uart(str);
//                                    number = 1;
//                                    sprintf(sms_text, "warning out of location");
//                                    send_sms();
//                                    number = 5;
//                                    send_atcammand("AT+CMGD=1,4");
//                                }
//                        }

//                }

//        }
//}

void speed_()
{
    if (speed_state == 1)
    {

        if (gps_signal1 == 1 && ok_loc == 1)
        {
            speed_gps = atoi(speed);
            if (speed_gps > speed_user && speed_count1 == 0)
            {
                speed_count1 = 1;
                number = 1;
                sprintf(sms_text, "warning out of Speed Limit");
                send_sms();
                number = 5;
                send_atcammand("AT+CMGD=1,4");

            }
        }
    }

}


//***************************check*************************************
//***************************check*************************************

void chek_()
{

    //*****config a9g*****
    if (a9g == 0 && a9g_state < 10)
    {
        //***level1 START A9G***
        if (a9g_state == 1 )
        {
            if (strstr(char_test1, "OK") != NULL)
            {
                reset_micro_count = 0;
                show_uart("a9g on");
                a9g_state = 2;
                HAL_IWDG_Refresh(&hiwdg);
            }
        }

        //****network check****
        if (strstr(char_test1, "READY") != NULL
                || strstr(char_test1, "+CREG: 1,1") != NULL
                || strstr(char_test1, "Ai_Thinker_Co._Ltd." ) != NULL || strstr(char_test1, "+CREG: 2,1" ) != NULL )
        {
            show_uart("network ready");
            a9g_state = 4;
        }




        //***MODEL SIMCARD***
        if (a9g_state == 5)
        {
            //char *dest = substr(char_test1, 0, 5);
            substring(char_test1, 0, 5);
            //sprintf(sms1, str_cut);
            strcpy(sms1, str_cut);
            strcat(sms1, "\r\n");
            if (strstr(sms1, "+COPS") != NULL)
            {
                substring(char_test1, 12, 17);
                strcpy(sms1, str_cut);
                strcat(sms1, "\r\n");
                //***HAMRAH AVAL****
                if (strstr(sms1, "43211") != NULL)
                {
                    show_uart("SIM: MCI");
                    a9g_state = 6;
                    model_simcard = 2;
                }
                //***IRANCEL****
                if (strstr(sms1, "43235") != NULL)
                {
                    show_uart("SIM: IranCell");
                    a9g_state = 6;
                    model_simcard = 1;
                }
            }
        }
    }

    //******main_check********
    if( strstr(char_test1, "+CREG: 1,1") != NULL || strstr(char_test1, "+CREG: 2,1" ) != NULL || strstr(char_test1, "+CREG: 2,5" ) != NULL  ) {
        main_check_time = 0;
        main_check = 0;
        main_check_error = 0;
        show_uart("***main check OK****");
    }

    if (strstr(char_test1, "+CIEV: roam, 0") != NULL
            || strstr(char_test1, "+CIEV: service,  0") != NULL || strstr(char_test1, "+CREG: 0") != NULL)
    {
        red_led_count = 0;
    }

    if (strstr(char_test1, "+CREG: 1") != NULL
            || strstr(char_test1, "+CIEV: service,  1") != NULL
            || strstr(char_test1, "+CREG: 1,1") != NULL)
    {
        red_led_count = 1;
        sim_error_count1 = 0;
    }
    //**********************chek_a9g*****************////
    //**********************chek_a9g*****************////
    //**********************chek_a9g*****************////
    if (strstr(char_test1, "OK") != NULL && chek == 1)
    {
        chek = 2;
    }

    //*********************anten********************
    if (strstr(char_test1, "+CSQ") != NULL)
    {
        substring(char_test1, 6, 8);
        strcpy(sms1, str_cut);
        anten = atoi(sms1);
        sprintf(str, "ANTEN:");
        strcat(str, sms1);
        show_uart(str);

    }



//********************************input sms number**************************
    substring(char_test1, 0, 4);
    strcpy(sms1, str_cut);

    if (strstr(sms1, "+CMT") != NULL && a9g == 2)   /////sms vorodi inteupts
    {
        show_uart("INPUT SMS1");
        send_atcammand("AT+GPSRD=0");
        for (int i = 0; i < 10; i++)
        {
            HAL_GPIO_TogglePin(led_net_GPIO_Port, led_net_Pin);
            HAL_GPIO_TogglePin(led_gps_GPIO_Port, led_gps_Pin);
            HAL_GPIO_TogglePin(led_batt_GPIO_Port, led_batt_Pin);
            HAL_Delay(50);
        }
        network_reset_count = 0;//sefr kardan reset dar sorat ok bodan shabake
        HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_SET);
        check_point1 = 1;
        ///NUMBER
        substring(char_test1, 7, 20);
        strcpy(sms1, str_cut);
        //strcat(sms1, "\r\n");
        show_uart(sms1);

        if (strstr(sms1, server_number) != NULL)   /////////////////server send sms
        {
            strcpy(input_number, sms1);
            number = 0;
            show_uart("SERVER NUMBER1");

        }
        else if (strstr(sms1, server_number2) != NULL)     /////////////////number1 send sms
        {
            strcpy(input_number, sms1);
            number = 6;
            show_uart("SERVER NUMBER2");
        }
        else if (strstr(sms1, number1) != NULL)     /////////////////number1 send sms
        {
            strcpy(input_number, sms1);
            number = 1;
            show_uart("NUMBER1");
        }

        else if (strstr(sms1, number2) != NULL)   /////////////////number2 send sms
        {
            strcpy(input_number, sms1);
            number = 2;
            show_uart("NUMBER2");
        }

        else if (strstr(sms1, number3) != NULL)   /////////////////number3 send sms
        {
            strcpy(input_number, sms1);
            number = 3;
            show_uart("NUMBER3");
        }

        else if (strstr(sms1, number4) != NULL)   /////////////////number4 send sms
        {
            strcpy(input_number, sms1);
            number = 4;
            show_uart("NUMBER4");
        }
        else
        {
            strcpy(input_number, sms1);
            number = 5;
            show_uart("Unknown");
            memcpy(send_number, "", sizeof(1));
        }
    }

    //****RAVESH DASTI****//
    substring(char_test1, 0, 5);
    strcpy(sms1, str_cut);

    //show_uart(sms2);
    if (strstr(sms1, "+CMGR") != NULL && a9g == 2)   /////sms vorodi inteupts
    {
        if (gprs == 1 && gprsrd == 9)
            gprsrd = 10; //chek kardan sms va raftan be marhale badi baraye internet
        show_uart("INPUT SMS2");
        send_atcammand("AT+GPSRD=0");
        network_reset_count = 0;
        for (int i = 0; i < 10; i++)
        {
            HAL_GPIO_TogglePin(led_net_GPIO_Port, led_net_Pin);
            HAL_GPIO_TogglePin(led_gps_GPIO_Port, led_gps_Pin);
            HAL_GPIO_TogglePin(led_batt_GPIO_Port, led_batt_Pin);
            HAL_Delay(50);
        }
        HAL_GPIO_WritePin(led_net_GPIO_Port, led_net_Pin, GPIO_PIN_SET);
        ///NUMBER
        //char *dest = substr(char_test1, 19, 32);
        substring(char_test1, 19, 32);
        strcpy(sms1, str_cut);
        //strcat(sms2, "\r\n");
        show_uart(sms1);
        check_point1 = 1;

        if (strstr(sms1, server_number) != NULL)   /////////////////server send sms
        {
            strcpy(input_number, sms1);
            number = 0;
            show_uart("SERVER NUMBER1");

        }
        else if (strstr(sms1, server_number2) != NULL)     /////////////////number1 send sms
        {
            strcpy(input_number, sms1);
            number = 6;
            show_uart("SERVER NUMBER2");
        }
        else if (strstr(sms1, number1) != NULL)     /////////////////number1 send sms
        {
            strcpy(input_number, sms1);
            number = 1;
            show_uart("NUMBER1");
        }

        else if (strstr(sms1, number2) != NULL)   /////////////////number2 send sms
        {
            strcpy(input_number, sms1);
            number = 2;
            show_uart("NUMBER2");
        }

        else if (strstr(sms1, number3) != NULL)   /////////////////number3 send sms
        {
            strcpy(input_number, sms1);
            number = 3;
            show_uart("NUMBER3");
        }

        else if (strstr(sms1, number4) != NULL)   /////////////////number4 send sms
        {
            strcpy(input_number, sms1);
            number = 4;
            show_uart("NUMBER4");
        }
        else
        {
            strcpy(input_number, sms1);
            number = 5;
            show_uart("Unknown");
        }
        //HAL_Delay(300);
    }

//***********************************input sms text**********************************************************
//***********************************input sms text**********************************************************
//***********************************input sms text**********************************************************

    if (strstr(char_test1, "network reset") != NULL || strstr(char_test1, "Network reset") != NULL  )
    {
        show_uart("auto reset network");
        if(number == 6)HAL_UART_Transmit(&huart1, (uint8_t *)"AT+CMGS=\"09114764806\"\r\n", 23, 100);
        if(number == 0)HAL_UART_Transmit(&huart1, (uint8_t *)"AT+CMGS=\"09372425086\"\r\n", 23, 100);
        HAL_Delay(300);
        HAL_UART_Transmit(&huart1, (uint8_t *)"RESET NETWORK", 13, 100);
        uint8_t sms_send = 0x1A;
        HAL_UART_Transmit(&huart1, &sms_send, 1, 100);
        HAL_Delay(2000);
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(1000);
        send_atcammand("AT+CFUN=0");
        HAL_Delay(5000);
        send_atcammand("AT+CFUN=1");
        HAL_Delay(4000);
        hang = 1;
        HAL_Delay(2000);
    }


    ///send server information
    if (strstr(char_test1, "information") != NULL || strstr(char_test1, "Information") != NULL )
    {
        if(number == 0 || number == 6)
        {
            if(number == 6)HAL_UART_Transmit(&huart1, (uint8_t *)"AT+CMGS=\"09114764806\"\r\n", 23, 100);
            if(number == 0)HAL_UART_Transmit(&huart1, (uint8_t *)"AT+CMGS=\"09372425086\"\r\n", 23, 100);
            HAL_Delay(300);
            send_eeprom_server();
            HAL_UART_Transmit(&huart1,(uint8_t *) str, strlen(str), 250);
            uint8_t sms_send = 0x1A;
            HAL_UART_Transmit(&huart1, &sms_send, 1, 250);
            HAL_Delay(3000);
            send_atcammand("AT+CMGD=1,4");
            HAL_Delay(500);
        }
    }

    ///CONFIG EEPROM
    if (strstr(char_test1, "eeprom") != NULL )
    {
        if(number == 0 || number == 6)
        {
            show_uart("***EEPROM SAVED***");
            //EEPROM SAVE
            server_eeprom_save();
            uint8_t sms_send = 0x1A;
            if(number == 6)HAL_UART_Transmit(&huart1, (uint8_t *)"AT+CMGS=\"09114764806\"\r\n", 23, 100);
            if(number == 0)HAL_UART_Transmit(&huart1, (uint8_t *)"AT+CMGS=\"09372425086\"\r\n", 23, 100);
            HAL_Delay(300);
            sprintf(str, "EEPROM CONFIG OK");
            HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 100);
            sms_send = 0x1A;
            HAL_UART_Transmit(&huart1, &sms_send, 1, 100);
            HAL_Delay(3000);
            send_atcammand("AT+CMGD=1,4");
            HAL_Delay(2000);
            hang = 1;
            HAL_Delay(50000);
            //eep_ok = 0;
        }
    }

//***NUMBER1 CONFIG***
    substring(char_test1, 0, 6);
    strcpy(sms1, str_cut);
    if (strstr(sms1, "CONFIG") != NULL )
    {
        if ( number == 0 || number == 6 )
            config(); /////sms vorodi inteupts
        HAL_Delay(100);
    }

    if (strstr(sms1, "+CIEV") != NULL && a9g == 2)
    {
        check_point1 = 1;
        show_uart("CIEV SMS");
        send_atcammand("AT+GPSRD=0");
        HAL_Delay(300);
    }
//**change pass***//
    if (check_point1 == 1 && a9g == 2)
    {
        substring(char_test1, 0, 1);
        strcpy(sms1, str_cut);
        if (strstr(sms1, "R") != NULL)
        {
            change_pass();
            check_point1 = 0;
            HAL_Delay(1000);
        }
    }

    //******************server sms******************
//    if (strstr(char_test1, "Server") != NULL )
//    {
//        show_uart("site send sms");
//        substring(char_test1, 7, 15); //id
//        strcpy(str, str_cut);
//        show_uart(str);
//        if (strstr(id, str) != NULL )
//        {

//            substring(char_test1, 16, 29); //input number
//            strcpy(str, str_cut);
//            strcpy(input_number, str_cut);
//            show_uart(input_number);
//            //****change pass****
//            substring(char_test1, 30, 31);
//            strcpy(sms1, str_cut);
//            if(strstr(sms1, "R") != NULL)
//            {
//                show_uart("server - change pass");
//                substring(char_test1, 30, 64); //change pass
//                strcpy(char_test1, str_cut);
//                show_uart(char_test1);
//                change_pass();
//                check_point1 = 0;
//                HAL_Delay(1000);

//            }

//            //****input sms****
//            if(strstr(str, number1) != NULL || strstr(str, number2) != NULL || strstr(str, number3) != NULL || strstr(str, number4) != NULL || strstr(str, server_number) != NULL || strstr(str, server_number2) != NULL )
//            {
//                check_point1 = 1;

//                if(strstr(str, number1) != NULL )
//                {
//                    number = 1;
//                    show_uart("site-number=1");
//                }
//                if(strstr(str, number2) != NULL )
//                {
//                    number = 2;
//                    show_uart("site-number=2");
//                }
//                if(strstr(str, number3) != NULL )
//                {
//                    number = 3;
//                    show_uart("site-number=3");
//                }
//                if(strstr(str, number4) != NULL )
//                {
//                    number = 4;
//                    show_uart("site-number=4");
//                }
//                if(strstr(str, server_number) != NULL )
//                {
//                    number = 0;
//                    show_uart("site-number=server1");
//                }
//                if(strstr(str, server_number2) != NULL )
//                {
//                    number = 6;
//                    show_uart("site-numbe:server2");
//                }

//                substring(char_test1, 30, 31);
//                strcpy(str, str_cut);
//                //**add member***//
//                if (strstr(str, "A") != NULL)
//                {
//                    substring(char_test1, 30, 52);
//                    strcpy(char_test1, str_cut);
//                    add_member();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**location***//
//                if (strstr(str, "L") != NULL)
//                {
//                    substring(char_test1, 30, 36);
//                    strcpy(char_test1, str_cut);
//                    send_location_sms();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                substring(char_test1, 30, 32);
//                strcpy(str, str_cut);
//                //**internet_on***//
//                if (strstr(str, "I1") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    internet_on();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**internet_off***//
//                if (strstr(str, "I2") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    internet_off();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }
//                //**internet_on***//
//                if (strstr(str, "I3") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    internet_on2();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**internet_on_for gps location***//
//                if (strstr(str, "I4") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    internet_on3();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }
//                //**security_on***//
//                if (strstr(str, "S1") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    security_on();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**security_off***//
//                if (strstr(str, "S2") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    security_off();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**sleep_on***//
//                if (strstr(str, "P1") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    sleep_on();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**sleep_off***//
//                if (strstr(str, "P2") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    sleep_off();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**sleep_off***//
//                if (strstr(sms1, "P3") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    sleep_on2();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**sleep_off***//
//                if (strstr(sms1, "P4") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    auto_sleep();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**rele_on***//
//                if (strstr(str, "ON") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    car_on();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**rele_off***//
//                if (strstr(str, "OF") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    car_off();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**BATTERY VOLTAJ***//
//                if (strstr(str, "BT") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    battry();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //////////////////////////////////////////////////////////////////////////
//                //**distance on***//
////                            if (strstr(str, "D1") != NULL)
////                                {
////                                    substring(char_test1, 30, 42);
////                                    strcpy(char_test1, str_cut);
////                                    distance_on();
////                                    HAL_Delay(1000);
////                                    check_point1 = 0;
////                                }
//                //**distance off***//
////                            if (strstr(str, "D2") != NULL)
////                                {
////                                    substring(char_test1, 30, 37);
////                                    strcpy(char_test1, str_cut);
////                                    distance_off();
////                                    HAL_Delay(1000);
////                                    check_point1 = 0;
////                                }

//                //**speed alarm on***//
//                if (strstr(str, "M1") != NULL)
//                {
//                    substring(char_test1, 30, 41);
//                    strcpy(char_test1, str_cut);
//                    speed_on();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**speed alarm off***//
//                if (strstr(str, "M2") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    speed_off();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**auto_security_on***//
//                if (strstr(str, "E1") != NULL)
//                {
//                    substring(char_test1, 30, 39);
//                    strcpy(char_test1, str_cut);
//                    auto_security_on();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**auto_security_off***//
//                if (strstr(str, "E2") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    auto_security_off();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**auto_reset_on***//
//                if (strstr(str, "Y1") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    car_mode_();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }

//                //**auto_reset_off***//
//                if (strstr(str, "Y2") != NULL)
//                {
//                    substring(char_test1, 30, 37);
//                    strcpy(char_test1, str_cut);
//                    motor_mode();
//                    HAL_Delay(1000);
//                    check_point1 = 0;
//                }



//            }

//        }

//    }

//****************************android************************************
    if( a9g == 2)
    {
        if (number == 0 || number == 1 || number == 2 || number == 3 || number == 4 || number == 6  )
        {
            check_point1 = 1;

            //**add member***//
            substring(char_test1, 0, 1);
            strcpy(sms1, str_cut);
            if (strstr(sms1, "A") != NULL)
            {
                add_member();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**location***//
            if (strstr(sms1, "L") != NULL || strstr(sms1, "l") != NULL)
            {
                send_location_sms();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**location2***//

            //**forget pass***//
            if (strstr(sms1, "C") != NULL)
            {
                forget_pass();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**internet_on***//
            substring(char_test1, 0, 2);
            strcpy(sms1, str_cut);





            //**security_on***//
            if (strstr(sms1, "S1") != NULL || strstr(sms1, "s1") != NULL)
            {
                security_on();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**security_off***//
            if (strstr(sms1, "S2") != NULL || strstr(sms1, "s2") != NULL)
            {
                security_off();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**sleep_on***//
            if (strstr(sms1, "P1") != NULL || strstr(sms1, "p1") != NULL)
            {
                sleep_on();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**sleep_off***//
            if (strstr(sms1, "P2") != NULL || strstr(sms1, "p2") != NULL)
            {
                sleep_off();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**sleep_off***//
            if (strstr(sms1, "P3") != NULL || strstr(sms1, "p3") != NULL)
            {
                sleep_on2();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**sleep_off***//
            if (strstr(sms1, "P4") != NULL || strstr(sms1, "p4") != NULL)
            {
                auto_sleep();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**rele_on***//
            if (strstr(sms1, "ON") != NULL || strstr(sms1, "on") != NULL || strstr(sms1, "On") != NULL)
            {
                car_on();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**rele_off***//
            if (strstr(sms1, "OF") != NULL || strstr(sms1, "of") != NULL || strstr(sms1, "Of") != NULL )
            {
                car_off();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**BATTERY VOLTAJ***//
            if (strstr(sms1, "BT") != NULL || strstr(sms1, "Bt") != NULL || strstr(sms1, "bt") != NULL)
            {
                battry();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**distance***//
//                    if (strstr(sms1, "D1") != NULL)
//                        {
//                            distance_on();
//                            HAL_Delay(1000);
//                            check_point1 = 0;
//                        }

//                    if (strstr(sms1, "D2") != NULL)
//                        {
//                            distance_off();
//                            HAL_Delay(1000);
//                            check_point1 = 0;
//                        }

            //**speed alarm on***//
            if (strstr(sms1, "M1") != NULL)
            {
                speed_on();
                HAL_Delay(1000);
                check_point1 = 0;
            }

            //**speed alarm off***//
            if (strstr(sms1, "M2") != NULL)
            {
                speed_off();
                HAL_Delay(1000);
                check_point1 = 0;
            }



            ///reset
            if (strstr(char_test1, "reset gps") != NULL)
            {

                reset_gps_();
                HAL_Delay(3000);
                HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
                HAL_Delay(150);
                HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
                HAL_Delay(200);
                HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
                HAL_Delay(2000);
                HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
                hang = 1;
                HAL_Delay(50000);

            }

            if (strstr(char_test1, "call") != NULL)
            {

                call_gps();

                check_point1 = 0;
            }

        }
    }
    //********************************************************************************************
//SIM MCI:
//+CLCC: 1,1,4,0,0,"09372425086",161  //IRANCELL
//+CLCC: 1,1,4,0,0,"989114764806",145 //MCI
//SIM IRANCELL:
//+CLCC: 1,1,4,0,0,"989372425086",145 //IRANCELL
//+CLCC: 1,1,4,0,0,"989114764806",145 //MCI
    //******ring*******

    if (strstr(char_test1, "RING") != NULL)
    {
        send_atcammand("AT+GPSRD=0");
        HAL_Delay(1000);
        HAL_Delay(100);
        show_uart("Call");
        send_atcammand("AT+CLCC");
        //HAL_Delay(50);
    }

    if (strstr(char_test1, "+CLCC") != NULL)
    {
        substring(char_test1, 18, 19); //+CLCC: 1,1,4,0,0,"09372425086",161
        strcat(sms1, str_cut);
        if(strstr(sms1, "0") != NULL)  //09372425086
        {
            show_uart("call IRANCELL");
            sprintf(sms1, "+989");
            substring(char_test1, 20, 29);
            strcat(sms1, str_cut);
            show_uart(sms1);
        }
        else if(strstr(sms1, "9") != NULL)   // 989114764806
        {
            show_uart("call MCI");
            sprintf(sms1, "+");
            substring(char_test1, 18, 30);
            strcat(sms1, str_cut);
            show_uart(sms1);
        }
        if (strstr(sms1, server_number) != NULL || strstr(sms1, number1) != NULL
                || strstr(sms1, number2) != NULL
                || strstr(sms1, server_number2) != NULL)
        {
            send_atcammand("ATA");
            show_uart("ata");
            ++ring_reset_count;

            reset_network();


            if (strstr(sms1, server_number) != NULL)   /////////////////server send sms
            {
                number = 0;
            }
            else if (strstr(sms1, server_number2) != NULL)     /////////////////number1 send sms
            {
                number = 6;
            }
            else if (strstr(sms1, number1) != NULL)     /////////////////number1 send sms
            {
                number = 1;
            }

            else if (strstr(sms1, number2) != NULL)   /////////////////number2 send sms
            {
                number = 2;
            }

            if(ring_reset_count>=5)sprintf(sms_text, "***RESET GPS***\r\n");
            if(ring_reset_count<10)sprintf(sms_text, "");
            strcat(sms_text, "Location:\r\n");

            strcat(sms_text, "www.google.com/maps/place/");
            if (gps_signal1 == 1)
            {
                strcat(sms_text, location);
                strcat(sms_text, "\r\n");
            }
            if (gps_signal1 == 3 || gps_signal1 == 0 )
            {
                strcat(sms_text, loc_save);
                strcat(sms_text, "\r\n");
            }
            show_uart(sms_text);
            send_sms();
            number = 5;
            HAL_Delay(3000);
            if(ring_reset_count>=5)
            {
                show_uart("***RESET Server***");
                HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
                HAL_Delay(150);
                HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
                HAL_Delay(200);
                HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
                HAL_Delay(2000);
                HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
                HAL_Delay(2000);
                hang = 1;
                HAL_Delay(50000);
            }
        }
    }

    //*************************************************gps location********************************************************************
    //*************************************************gps location********************************************************************
    //*************************************************gps location********************************************************************


    //*************************************************gprs_error********************************************************************
    //*************************************************gprs_error********************************************************************
    //*************************************************gprs_error********************************************************************
    if (strstr(char_test1, "notfound") != NULL && gprs == 1)
    {
        show_uart("first time error");
        if (user_first == 0 )first_time_gprs = 0;
    }

    if (strstr(char_test1, "HTTP/1.1  200  OK") != NULL && gprs == 1)
    {
        gprsrd = 5; //data send and saved
    }

    if (strstr(char_test1, "Server") != NULL && gprs == 1)
    {
        gprsrd = 5; //data send and saved
    }

    if (strstr(char_test1, "Date") != NULL && gprs == 1)
    {
        gprsrd = 5; //data send and saved
    }

    if (strstr(char_test1, "Content-Length: 2") != NULL && gprs == 1)
    {
        gprsrd = 5; //data send and saved
    }

    if (strstr(char_test1, "Connection: Keep-Alive") != NULL && gprs == 1)
    {
        gprsrd = 5; //data send and saved
    }

    if (strstr(char_test1, "server: LiteSpeed") != NULL && gprs == 1)
    {
        gprsrd = 5; //data send and saved
    }

    if (strstr(char_test1, "failure, pelase check your network!") != NULL
            && gprs == 1)
    {
        gprsrd = 6; //data not send / network error
    }

    if (strstr(char_test1, "Dns,fail,try url") != NULL && gprs == 1)
    {
        gprsrd = 6; //data not send / network error
    }

    if (strstr(char_test1, "HTTP/1.1  500") != NULL && gprs == 1)
    {
        gprsrd = 6; //data not send / network error
    }

    if (strstr(char_test1, "+CMS ERROR: 321") != NULL)
    {
        if (gprs == 1 && gprsrd == 9)
            gprsrd = 10; //chek kardan sms va raftan be marhale badi baraye internet
        //show_uart("NO SMS");
        //HAL_Delay(50);
    }

    if (strstr(char_test1, "+CMS ERROR: 321") != NULL)
    {
        show_uart("**NO INPUT SMS**");
    }

    if (strstr(char_test1, "+CMS ERROR: 300") != NULL
            || strstr(char_test1, "+CMS ERROR: 518") != NULL
            || strstr(char_test1, "+CMS ERROR: 500") != NULL
            || strstr(char_test1, "+CME ERROR: 58") != NULL)   //|| strstr(char_test1, "+CMS ERROR: 500") != NULL
    {
        show_uart("CMS ERROR");
        HAL_Delay(50);
        send_atcammand("AT+CMGD=1,4");
        HAL_Delay(1000);
        ++cms_error_count;
        if (cms_error_count >= 4)
        {
            show_uart("CMS ERROR--->***RESET***");
            HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
            HAL_Delay(150);
            HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
            HAL_Delay(200);
            HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
            HAL_Delay(2000);
            HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
            HAL_Delay(2000);
            hang = 1;
            HAL_Delay(50000);
        }

    }

    //**************chek model sim card**********************
    //***MODEL SIMCARD***

    //char *dest = substr(char_test1, 0, 5);
    substring(char_test1, 0, 5);
    strcpy(sms1, str_cut);
    strcat(sms1, "\r\n");
    if (strstr(sms1, "+COPS") != NULL)
    {
        //char *dest = substr(char_test1, 12, 17);
        substring(char_test1, 12, 17);
        strcpy(sms1, str_cut);
        strcat(sms1, "\r\n");
        //***HAMRAH AVAL****
        if (strstr(sms1, "43211") != NULL)
        {
            show_uart("SIM MCI");
            chek_sim_ok = 1;
            model_simcard = 2;
            red_led_count = 1;
        }
        //***IRANCEL****
        if (strstr(sms1, "43235") != NULL)
        {
            show_uart("SIM IRANCEL");
            chek_sim_ok = 1;
            model_simcard = 1;
            red_led_count = 1;
        }

    }

}

//*******************************************uart_input*******************************************//
//*******************************************uart_input*******************************************//
//*******************************************uart_input*******************************************//
//*******************************************uart_input*******************************************//
void uart1_()
{

//****************input1****************
    if (strstr(input1, "\r\n") != NULL)
    {
        memcpy(char_test1, "", sizeof(1));
        strcpy(char_test1, input1);
        if (read_gps == 0)
            show_uart(char_test1);
        memcpy(input1, "", sizeof(1));
        if (count_interupts >= 7)
            count_interupts = 0;
        chek_();
    }
//****************input2****************
    if (strstr(input2, "\r\n") != NULL)
    {
        memcpy(char_test1, "", sizeof(1));
        strcpy(char_test1, input2);
        if (read_gps == 0)
            show_uart(char_test1);
        memcpy(input2, "", sizeof(1));
        if (count_interupts >= 7)
            count_interupts = 0;
        chek_();
    }
//****************input3****************
    if (strstr(input3, "\r\n") != NULL)
    {
        memcpy(char_test1, "", sizeof(1));
        strcpy(char_test1, input3);
        if (read_gps == 0)
            show_uart(char_test1);
        memcpy(input3, "", sizeof(1));
        if (count_interupts >= 7)
            count_interupts = 0;
        chek_();
    }
//****************input4****************
    if (strstr(input4, "\r\n") != NULL)
    {


        memcpy(char_test1, "", sizeof(1));
        strcpy(char_test1, input4);
        if (read_gps == 0)
            show_uart(char_test1);
        memcpy(input4, "", sizeof(1));
        if (count_interupts >= 7)
            count_interupts = 0;
        chek_();
    }
//****************input5****************
    if (strstr(input5, "\r\n") != NULL)
    {

        memcpy(char_test1, "", sizeof(1));
        strcpy(char_test1, input5);
        if (read_gps == 0 && gprs == 0)
            show_uart(char_test1);
        memcpy(input5, "", sizeof(1));
        if (count_interupts >= 7)
            count_interupts = 0;
        chek_();
    }

    //****************input6****************
    if (strstr(input6, "\r\n") != NULL)
    {

        memcpy(char_test1, "", sizeof(1));
        strcpy(char_test1, input6);
        if (read_gps == 0 && gprs == 0)
            show_uart(char_test1);
        memcpy(input6, "", sizeof(1));
        if (count_interupts >= 7)
            count_interupts = 0;
        chek_();
    }


    //****************input7****************
    if (strstr(input7, "\r\n") != NULL)
    {

        memcpy(char_test1, "", sizeof(1));
        strcpy(char_test1, input7);
        if (read_gps == 0 && gprs == 0)
            show_uart(char_test1);
        memcpy(input7, "", sizeof(1));
        if (count_interupts >= 7)
            count_interupts = 0;
        chek_();
    }

}


//**********test***********
void test_cod()
{
    if(count_test >= 2)
    {
        sprintf(str, "battery voltage:%d v", voltag_battery);
        show_uart(str);
        count_test = 0;
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
    /* USER CODE BEGIN 1 */

    /* USER CODE END 1 */

    /* MCU Configuration--------------------------------------------------------*/

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* USER CODE BEGIN Init */

    /* USER CODE END Init */

    /* Configure the system clock */
    SystemClock_Config();

    /* USER CODE BEGIN SysInit */

    /* USER CODE END SysInit */

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_ADC_Init();
    MX_IWDG_Init();
    MX_TIM1_Init();
    MX_USART1_UART_Init();
    MX_USART2_UART_Init();
    MX_I2C2_Init();
    MX_WWDG_Init();
    /* USER CODE BEGIN 2 */
    HAL_UART_Receive_IT(&huart1, &rx_data1, 1); // faal kardan  interupt uart1
    HAL_ADC_Start(&hadc);
    HAL_TIM_Base_Start_IT(&htim1);  //faal kardan timer
    //HAL_UART_Receive_IT(&huart2, &rx_data2, 1); // faal kardan  interupt uart2
    HAL_UART_Transmit(&huart2, (uint8_t *)"******                  ******\r\n", 21, 100);
    HAL_UART_Transmit(&huart2, (uint8_t *)"     ***START PROGRAM***\r\n", 21, 100);
    HAL_UART_Transmit(&huart2, (uint8_t *)"******                  ******\r\n", 21, 100);
//***************************************************
    HAL_GPIO_WritePin(wp_GPIO_Port, wp_Pin, GPIO_PIN_SET);
    HAL_Delay(1000);

    /* USER CODE END 2 */

    /* Infinite loop */
    /* USER CODE BEGIN WHILE */
    while (1)
    {

//					while(1){
//						battery_();
//						sprintf(lcd_show, "BAT=%d v", voltag_battery);
//            show_uart(lcd_show);
//						 HAL_IWDG_Refresh(&hiwdg);
//						HAL_Delay(1000);
//					}

        uart1_();
        //uart2_();
        if (a9g_state < 10)
            a9g_start();

        if (a9g == 1)
            read_eeprom_();

        if (a9g == 2)
        {
            if (check_point1 == 0)
            {
                chek_a9g_at();
                chek_sim();
                //gps_read();
                //gprs_online();
                //gprs_hiytory();
                battery_();
                power_chek();
                //sensor_chek();
                sleep_();
                reset_();
                //gps_test();
                //speed_();

            }

            input_sms_chek();

        }

//****hang micro****
        if (reset_micro_count >= 6)
        {
            HAL_Delay(50);
            send_atcammand("AT+CMGD=1,4");
            HAL_Delay(500);
//                    HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_SET);
//                    HAL_Delay(150);
//                    HAL_GPIO_WritePin(a9greset_GPIO_Port, a9greset_Pin, GPIO_PIN_RESET);
//                    HAL_Delay(200);
//                    HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_RESET);
//                    HAL_Delay(2000);
//                    HAL_GPIO_WritePin(a9g_start_GPIO_Port, a9g_start_Pin, GPIO_PIN_SET);
//                    HAL_Delay(2000);
            hang = 1;
            HAL_Delay(50000);
        }
        if (reset_micro == 0)
            HAL_IWDG_Refresh(&hiwdg);

        /* USER CODE END WHILE */

        /* USER CODE BEGIN 3 */
    }
    /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI14|RCC_OSCILLATORTYPE_LSI
                                       |RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
    RCC_OscInitStruct.HSI14CalibrationValue = 16;
    RCC_OscInitStruct.LSIState = RCC_LSI_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
    RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                                  |RCC_CLOCKTYPE_PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
    {
        Error_Handler();
    }
    PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1;
    PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
    {
        Error_Handler();
    }
}

/* USER CODE BEGIN 4 */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef *hwwdg)
{
    if(hang == 0) HAL_WWDG_Refresh(hwwdg);

}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1)
    {
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
    /* USER CODE BEGIN 6 */
    /* User can add his own implementation to report the file name and line number,
    	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

