#include <vector>
#include "esphome.h"
#include "esphome/components/sensor/sensor.h"

#pragma pack(1)
typedef struct _Device_Status
{
    uint8_t header[16];

    uint8_t wind_status; // air volume
    uint8_t sleep_status;

    uint8_t skip1 : 1;
    uint8_t direction_status : 2;
    uint8_t run_status : 1;
    uint8_t mode_status : 4;

    // 4
    uint8_t indoor_temperature_setting;
    uint8_t indoor_temperature_status;
    uint8_t indoor_pipe_temperature;
    // 7
    uint8_t indoor_humidity_setting;
    uint8_t indoor_humidity_status;

    uint8_t somatosensory_temperature; // sensible temperature
    // 10
    uint8_t somatosensory_compensation_ctrl : 3;
    uint8_t somatosensory_compensation : 5;
    
    // 11
    uint8_t skip3 : 1;
    uint8_t temperature_Fahrenheit : 1; // fahrenheit display
    uint8_t skip2 : 1;
    uint8_t temperature_compensation : 5;

    // 12
    uint8_t timer;

    // 13
    uint8_t hour;
    // 14
    uint8_t minute;
    // 15
    uint8_t skip4 : 3;
    uint8_t poweron_hour : 5;
    // 16
    uint8_t poweron_minute : 6;
    uint8_t skip5 : 1;
    uint8_t poweron_status : 1;
    // 17
    uint8_t poweroff_hour : 5 ;
    uint8_t skip6 : 3;
    // 18
    uint8_t poweroff_minute : 6;
    uint8_t skip7 : 1;
    uint8_t poweroff_status : 1;
    // 19
    uint8_t wind_door : 4;
    uint8_t drying : 4;
    // 20
    uint8_t dual_frequency : 1;
    uint8_t efficient : 1;
    uint8_t low_electricity : 1; // save electricity
    uint8_t low_power : 1;       // energy saving
    uint8_t heat : 1;            // heating air
    uint8_t nature : 1;          // natural wind
    uint8_t left_right : 1;      // horizontal swing
    uint8_t up_down : 1;         // vertical swing

    // 21
    uint8_t smoke : 1; // smoke removal
    uint8_t voice : 1;
    uint8_t mute : 1;
    uint8_t smart_eye : 1;
    uint8_t outdoor_clear : 1; // outdoor cleaning
    uint8_t indoor_clear : 1;  // indoor cleaning
    uint8_t swap : 1;          // Change the wind
    uint8_t dew : 1;           // fresh

    // 22
    uint8_t indoor_electric : 1;
    uint8_t right_wind : 1;
    uint8_t left_wind : 1;
    uint8_t filter_reset : 1;
    uint8_t indoor_led : 1;
    uint8_t indicate_led : 1;
    uint8_t display_led : 1;
    uint8_t back_led : 1;

    // 23
    uint8_t indoor_eeprom : 1; // eeprom
    uint8_t sample : 1;
    uint8_t rev23 : 4;
    uint8_t time_lapse : 1;
    uint8_t auto_check : 1; // self-test

    // 24
    uint8_t indoor_outdoor_communication : 1;
    uint8_t indoor_zero_voltage : 1;
    uint8_t indoor_bars : 1;
    uint8_t indoor_machine_run : 1;
    uint8_t indoor_water_pump : 1;
    uint8_t indoor_humidity_sensor : 1;
    uint8_t indoor_temperature_pipe_sensor : 1;
    uint8_t indoor_temperature_sensor : 1;

    // 25
    uint8_t rev25 : 3;
    uint8_t eeprom_communication : 1;
    uint8_t electric_communication : 1;
    uint8_t wifi_communication : 1;
    uint8_t keypad_communication : 1;
    uint8_t display_communication : 1;

    // 26
    uint8_t compressor_frequency;
    // 27
    uint8_t compressor_frequency_setting;
    // 28
    uint8_t compressor_frequency_send;
    // 29
    uint8_t outdoor_temperature;
    // 30
    uint8_t outdoor_condenser_temperature;
    // 31
    uint8_t compressor_exhaust_temperature;
    // 32
    uint8_t target_exhaust_temperature;
    // 33
    uint8_t expand_threshold;
    // 34
    uint8_t UAB_HIGH;
    // 35
    uint8_t UAB_LOW;
    // 36
    uint8_t UBC_HIGH;
    // 37
    uint8_t UBC_LOW;
    // 38
    uint8_t UCA_HIGH;
    // 39
    uint8_t UCA_LOW;
    // 40
    uint8_t IAB;
    // 41
    uint8_t IBC;
    // 42
    uint8_t ICA;
    // 43
    uint8_t generatrix_voltage_high;
    // 44
    uint8_t generatrix_voltage_low;
    // 45
    uint8_t IUV;
    // 46
    uint8_t wind_machine : 3;
    uint8_t outdoor_machine : 1;
    uint8_t four_way : 1;
    uint8_t rev46 : 3;

    // 47
    uint8_t rev47;
    // 48
    uint8_t rev48;
    // 49
    uint8_t rev49;
    // 50
    uint8_t rev50;
    // 51
    uint8_t rev51;
    // 52
    uint8_t rev52;
    // 53
    uint8_t rev53;
    // 54
    uint8_t rev54;
    // 55
    uint8_t rev55;
    // 56
    uint8_t rev56;

    uint8_t extra[6];
    uint16_t chk_sum;
    uint8_t foooter[2];
} Device_Status;

uint8_t on[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xDF, 0xF4, 0xFB};

uint8_t off[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x01, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x01,
    0x55, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x31, 0xF4, 0xFB};

uint8_t mode_cool[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x01, 0x01, 0x50, 0x35, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x7F, 0xF4, 0xFB};

uint8_t mode_heat[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x01, 0x01, 0x30, 0x2F, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x59, 0xF4, 0xFB};

uint8_t mode_fan[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x07, 0x01, 0x10, 0x33, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x43, 0xF4, 0xFB};

uint8_t mode_dry[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x01, 0x01, 0x70, 0x33, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x01,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x9D, 0xF4, 0xFB};

uint8_t speed_mute[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x0B, 0xF4, 0xFB};

uint8_t speed_low[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x05, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xED, 0xF4, 0xFB};

uint8_t speed_med[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xEF, 0xF4, 0xFB};

uint8_t speed_max[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x09, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xF1, 0xF4, 0xFB};

uint8_t speed_auto[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xE9, 0xF4, 0xFB};

uint8_t turbo_on[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x5C, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x41, 0xF4, 0xFB};

uint8_t turbo_off[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x54, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x39, 0xF4, 0xFB};

uint8_t energysave_on[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x07, 0xF4, 0xFB};

uint8_t energysave_off[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xE7, 0xF4, 0xFB};

uint8_t display_on[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x93, 0xF4, 0xFB};

uint8_t display_off[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x13, 0xF4, 0xFB};

uint8_t sleep_1[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x05, 0x03, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xEF, 0xF4, 0xFB};

uint8_t sleep_2[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xF1, 0xF4, 0xFB};

uint8_t sleep_3[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x05, 0x07, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xF3, 0xF4, 0xFB};

uint8_t sleep_4[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x05, 0x09, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xF5, 0xF4, 0xFB};

uint8_t sleep_off[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xE9, 0xF4, 0xFB};

uint8_t vert_dir[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x14, 0xF4, 0xFB};

uint8_t vert_swing[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xC0,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x94, 0xF4, 0xFB};

uint8_t hor_dir[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10,
    0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xF7, 0xF4, 0xFB};

uint8_t hor_swing[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30,
    0x00, 0x00, 0x00, 0x00, 0x14, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x17, 0xF4, 0xFB};

uint8_t temp_to_F[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xD6, 0xF4, 0xFB};

uint8_t temp_to_F_reset_temp[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7B, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x4A, 0xF4, 0xFB};

uint8_t temp_to_C[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xD4, 0xF4, 0xFB};

uint8_t temp_to_C_reset_temp[] = {
    0xF4, 0xF5, 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
    0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x21, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x01, 0xF0, 0xF4, 0xFB};

class AirconClimate : public PollingComponent, public Climate, public UARTDevice
{
public:
    AirconClimate(UARTComponent *parent) : PollingComponent(2000),
                                           UARTDevice(parent),
                                           compressor_frequency(),
                                           compressor_frequency_setting(),
                                           compressor_frequency_send(),
                                           outdoor_temperature(),
                                           outdoor_condenser_temperature(),
                                           compressor_exhaust_temperature(),
                                           target_exhaust_temperature(),
                                           indoor_pipe_temperature(),
                                           indoor_humidity_setting(),
                                           indoor_humidity_status() {}

    void setup() override
    {
        compressor_frequency.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        compressor_frequency_setting.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        compressor_frequency_send.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        outdoor_temperature.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        outdoor_condenser_temperature.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        compressor_exhaust_temperature.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        target_exhaust_temperature.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        indoor_pipe_temperature.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        indoor_humidity_setting.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
        indoor_humidity_status.set_state_class(sensor::STATE_CLASS_MEASUREMENT);
    }

    void update() override
    {
        uint8_t req_stat[] = {
            0xF4, 0xF5, 0x00, 0x40,
            0x0C, 0x00, 0x00, 0x01,
            0x01, 0xFE, 0x01, 0x00,
            0x00, 0x66, 0x00, 0x00,
            0x00, 0x01, 0xB3, 0xF4,
            0xFB};

        write_array(req_stat, 21);
        flush();

        if (read_response())
        {

            // ESP_LOGD(
            //     "aircon",
            //     "compf: %d compf_set: %d compf_snd: %d\n",
            //     ((Device_Status*)int_buf)compressor_frequency,
            //     ((Device_Status*)int_buf)compressor_frequency_setting,
            //     ((Device_Status*)int_buf)compressor_frequency_send);

            // ESP_LOGD(
            //     "aircon",
            //     "out_temp: %d out_cond_temp: %d comp_exh_temp: %d comp_exh_temp_tgt: %d\n",
            //     ((Device_Status*)int_buf)outdoor_temperature,
            //     ((Device_Status*)int_buf)outdoor_condenser_temperature,
            //     ((Device_Status*)int_buf)compressor_exhaust_temperature,
            //     ((Device_Status*)int_buf)target_exhaust_temperature);

            // ESP_LOGD(
            //     "aircon",
            //     "indoor_pipe_temp %d\n",
            //     ((Device_Status*)int_buf)indoor_pipe_temperature);

            // ESP_LOGD(
            //     "aircon",
            //     "indor_humid_set: %d indoor_humid: %d\n",
            //     ((Device_Status*)int_buf)indoor_humidity_setting,
            //     ((Device_Status*)int_buf)indoor_humidity_status);

            target_temperature = ((Device_Status*)int_buf)->indoor_temperature_setting;
            current_temperature = ((Device_Status*)int_buf)->indoor_temperature_status;

            // See if the system is actively running
            bool comp_running = false;
            if (((Device_Status*)int_buf)->compressor_frequency > 0)
            {
                comp_running = true;
            }

            if (((Device_Status*)int_buf)->left_right && ((Device_Status*)int_buf)->up_down)
                swing_mode = climate::CLIMATE_SWING_BOTH;
            else if (((Device_Status*)int_buf)->left_right)
                swing_mode = climate::CLIMATE_SWING_HORIZONTAL;
            else if (((Device_Status*)int_buf)->up_down)
                swing_mode = climate::CLIMATE_SWING_VERTICAL;
            else
                swing_mode = climate::CLIMATE_SWING_OFF;

            if (((Device_Status*)int_buf)->run_status == 0)
            {
                mode = CLIMATE_MODE_OFF;
                action = CLIMATE_ACTION_OFF;
            }
            else if (((Device_Status*)int_buf)->mode_status == 0)
            {
                mode = CLIMATE_MODE_FAN_ONLY;
                action = CLIMATE_ACTION_FAN;
            }
            else if (((Device_Status*)int_buf)->mode_status == 1)
            {
                mode = climate::CLIMATE_MODE_HEAT;
                if (comp_running)
                {
                    action = CLIMATE_ACTION_HEATING;
                }
                else
                {
                    action = CLIMATE_ACTION_IDLE;
                }
            }
            else if (((Device_Status*)int_buf)->mode_status == 2)
            {
                mode = climate::CLIMATE_MODE_COOL;
                if (comp_running)
                {
                    action = CLIMATE_ACTION_COOLING;
                }
                else
                {
                    action = CLIMATE_ACTION_IDLE;
                }
            }
            else if (((Device_Status*)int_buf)->mode_status == 3)
            {
                mode = climate::CLIMATE_MODE_DRY;
                if (comp_running)
                {
                    action = CLIMATE_ACTION_DRYING;
                }
                else
                {
                    action = CLIMATE_ACTION_IDLE;
                }
            }

            if (((Device_Status*)int_buf)->wind_status == 18)
            {
                fan_mode = climate::CLIMATE_FAN_HIGH;
            }
            else if (((Device_Status*)int_buf)->wind_status == 14)
            {
                fan_mode = climate::CLIMATE_FAN_MEDIUM;
            }
            else if (((Device_Status*)int_buf)->wind_status == 10)
            {
                fan_mode = climate::CLIMATE_FAN_LOW;
            }
            else if (((Device_Status*)int_buf)->wind_status == 2)
            {
                fan_mode = climate::CLIMATE_FAN_QUIET;
            }
            else if (((Device_Status*)int_buf)->wind_status == 0)
            {
                fan_mode = climate::CLIMATE_FAN_AUTO;
            }

            this->publish_state();

            // Update sensors
            set_sensor(compressor_frequency, ((Device_Status*)int_buf)->compressor_frequency);
            set_sensor(compressor_frequency_setting, ((Device_Status*)int_buf)->compressor_frequency_setting);
            set_sensor(compressor_frequency_send, ((Device_Status*)int_buf)->compressor_frequency_send);
            set_sensor(outdoor_temperature, ((Device_Status*)int_buf)->outdoor_temperature);
            set_sensor(outdoor_condenser_temperature, ((Device_Status*)int_buf)->outdoor_condenser_temperature);
            set_sensor(compressor_exhaust_temperature, ((Device_Status*)int_buf)->compressor_exhaust_temperature);
            set_sensor(target_exhaust_temperature, ((Device_Status*)int_buf)->target_exhaust_temperature);
            set_sensor(indoor_pipe_temperature, ((Device_Status*)int_buf)->indoor_pipe_temperature);
            set_sensor(indoor_humidity_setting, ((Device_Status*)int_buf)->indoor_humidity_setting);
            set_sensor(indoor_humidity_status, ((Device_Status*)int_buf)->indoor_humidity_status);

            // Save target temperature since it gets messed up by the mode switch command
            if (this->mode == CLIMATE_MODE_COOL && target_temperature > 0)
            {
                cool_tgt_temp = target_temperature;
            }
            else if (this->mode == CLIMATE_MODE_HEAT && target_temperature > 0)
            {
                heat_tgt_temp = target_temperature;
            }
        }
    }

    void control(const ClimateCall &call) override
    {
        const uint8_t resp_size = 83;
        uint8_t response_buf[resp_size];
        if (call.get_mode().has_value())
        {
            // Save target temperature since it gets messed up by the mode switch command
            if (this->mode == CLIMATE_MODE_COOL && target_temperature > 0)
            {
                cool_tgt_temp = target_temperature;
            }
            else if (this->mode == CLIMATE_MODE_HEAT && target_temperature > 0)
            {
                heat_tgt_temp = target_temperature;
            }

            // User requested mode change
            ClimateMode md = *call.get_mode();

            if (md != climate::CLIMATE_MODE_OFF && this->mode == climate::CLIMATE_MODE_OFF)
            {
                send_command(on, sizeof(on));
            }

            switch (md)
            {
            case climate::CLIMATE_MODE_OFF:
                send_command(off, sizeof(off));
                break;
            case climate::CLIMATE_MODE_COOL:
                send_command(mode_cool, sizeof(mode_cool));
                set_temp(cool_tgt_temp);
                break;
            case climate::CLIMATE_MODE_HEAT:
                send_command(mode_heat, sizeof(mode_heat));
                set_temp(heat_tgt_temp);
                break;
            case climate::CLIMATE_MODE_FAN_ONLY:
                send_command(mode_fan, sizeof(mode_fan));
                break;
            case climate::CLIMATE_MODE_DRY:
                send_command(mode_dry, sizeof(mode_dry));
                break;
            default:
                break;
            }

            // Publish updated state
            this->mode = md;
            this->publish_state();
        }

        if (call.get_target_temperature().has_value())
        {
            // User requested target temperature change
            int temp = *call.get_target_temperature();

            set_temp(temp);

            // Send target temp to climate
            target_temperature = temp;
            this->publish_state();
        }

        if (call.get_fan_mode().has_value())
        {
            ClimateFanMode fm = *call.get_fan_mode();
            switch (fm)
            {
            case climate::CLIMATE_FAN_AUTO:
                send_command(speed_auto, sizeof(speed_auto));
                break;
            case climate::CLIMATE_FAN_LOW:
                send_command(speed_low, sizeof(speed_low));
                break;
            case climate::CLIMATE_FAN_MEDIUM:
                send_command(speed_med, sizeof(speed_med));
                break;
            case climate::CLIMATE_FAN_HIGH:
                send_command(speed_max, sizeof(speed_max));
                break;
            case climate::CLIMATE_FAN_QUIET:
                send_command(speed_mute, sizeof(speed_mute));
                break;
            default:
                break;
            }
            fan_mode = fm;
            this->publish_state();
        }

        if (call.get_swing_mode().has_value())
        {
            ClimateSwingMode sm = *call.get_swing_mode();

            if (sm == climate::CLIMATE_SWING_OFF)
            {
                if (climate::CLIMATE_SWING_BOTH == swing_mode)
                {
                    send_command(vert_swing, sizeof(vert_swing));
                    send_command(hor_swing, sizeof(hor_swing));
                }
                else if (climate::CLIMATE_SWING_VERTICAL == swing_mode)
                {
                    send_command(vert_swing, sizeof(vert_swing));
                }
                else if (climate::CLIMATE_SWING_HORIZONTAL == swing_mode)
                {
                    send_command(hor_swing, sizeof(hor_swing));
                }
            }
            else if (sm == climate::CLIMATE_SWING_BOTH)
            {
                if (climate::CLIMATE_SWING_OFF == swing_mode)
                {
                    send_command(vert_swing, sizeof(vert_swing));
                    send_command(hor_swing, sizeof(hor_swing));
                }
                else if (climate::CLIMATE_SWING_VERTICAL == swing_mode)
                {
                    send_command(hor_swing, sizeof(hor_swing));
                }
                else if (climate::CLIMATE_SWING_HORIZONTAL == swing_mode)
                {
                    send_command(vert_swing, sizeof(vert_swing));
                }
            }
            else if (sm == climate::CLIMATE_SWING_VERTICAL)
            {
                if (climate::CLIMATE_SWING_BOTH == swing_mode)
                {
                    send_command(hor_swing, sizeof(hor_swing));
                }
                else if (climate::CLIMATE_SWING_HORIZONTAL == swing_mode)
                {
                    send_command(hor_swing, sizeof(hor_swing));
                    send_command(vert_swing, sizeof(vert_swing));
                }
            }
            else if (sm == climate::CLIMATE_SWING_HORIZONTAL)
            {
                if (climate::CLIMATE_SWING_BOTH == swing_mode)
                {
                    send_command(vert_swing, sizeof(vert_swing));
                }
                else if (climate::CLIMATE_SWING_VERTICAL == swing_mode)
                {
                    send_command(vert_swing, sizeof(vert_swing));
                    send_command(hor_swing, sizeof(hor_swing));
                }
            }

            swing_mode = sm;
            this->publish_state();
        }

        if (call.get_preset().has_value())
        {
            ClimatePreset pre = *call.get_preset();
            switch (pre)
            {
            case climate::CLIMATE_PRESET_NONE:
                send_command(turbo_off, sizeof(turbo_off));
                send_command(energysave_off, sizeof(energysave_off));
                break;
            case climate::CLIMATE_PRESET_BOOST:
                send_command(turbo_on, sizeof(turbo_on));
                break;
            case climate::CLIMATE_PRESET_ECO:
                send_command(energysave_on, sizeof(energysave_on));
                break;
            default:
                break;
            }

            preset = pre;
            this->publish_state();
        }
    }

    ClimateTraits traits() override
    {
        // The capabilities of the climate device
        auto traits = climate::ClimateTraits();
        traits.set_supports_current_temperature(true);
        traits.set_visual_min_temperature(16);
        traits.set_visual_max_temperature(30);
        traits.set_visual_temperature_step(1);
        traits.set_supported_modes({
            climate::CLIMATE_MODE_OFF,
            climate::CLIMATE_MODE_COOL,
            climate::CLIMATE_MODE_HEAT,
            climate::CLIMATE_MODE_FAN_ONLY,
            climate::CLIMATE_MODE_DRY,
        });
        traits.set_supported_swing_modes({climate::CLIMATE_SWING_OFF,
                                          climate::CLIMATE_SWING_BOTH,
                                          climate::CLIMATE_SWING_VERTICAL,
                                          climate::CLIMATE_SWING_HORIZONTAL});
        traits.set_supported_fan_modes({
            climate::CLIMATE_FAN_AUTO,
            climate::CLIMATE_FAN_LOW,
            climate::CLIMATE_FAN_MEDIUM,
            climate::CLIMATE_FAN_HIGH,
            climate::CLIMATE_FAN_QUIET,
        });
        traits.set_supported_presets({climate::CLIMATE_PRESET_NONE,
                                      climate::CLIMATE_PRESET_BOOST,
                                      climate::CLIMATE_PRESET_ECO});
        traits.set_supports_action(true);
        return traits;
    }

    sensor::Sensor compressor_frequency;
    sensor::Sensor compressor_frequency_setting;
    sensor::Sensor compressor_frequency_send;
    sensor::Sensor outdoor_temperature;
    sensor::Sensor outdoor_condenser_temperature;
    sensor::Sensor compressor_exhaust_temperature;
    sensor::Sensor target_exhaust_temperature;
    sensor::Sensor indoor_pipe_temperature;
    sensor::Sensor indoor_humidity_setting;
    sensor::Sensor indoor_humidity_status;

private:
    float heat_tgt_temp = 16.1111f;
    float cool_tgt_temp = 26.6667f;

    bool read_response()
    {
        int size = 0;
        uint32_t start_time = millis();
        while (millis() - start_time < 250)
            ;

        size = available();
        bool read_success = read_array(int_buf, size);

        // Exit if we timed out
        if (!read_success)
        {
            return false;
        }

        ESP_LOGD(
            "aircon",
            "Received %d bytes.",
            size);

        uint16_t checksum = 0;
        for (int i = 2; i < size - 4; i++)
        {
            checksum += int_buf[i];
        }
        uint16_t rxd_checksum = int_buf[size - 4];
        rxd_checksum = rxd_checksum << 8;
        rxd_checksum |= int_buf[size - 3];
        if (rxd_checksum != checksum)
        {
            ESP_LOGD(
                "aircon",
                "CRC check failed. Computed: %d Received: %d Bytes Not Read: %d\n",
                checksum,
                rxd_checksum,
                available());
            read_success = false;
        }

        return read_success;
    }

    void send_command(uint8_t cmd[], size_t sz)
    {
        uint32_t start_time = millis();
        write_array(cmd, sz);
        flush();
        read_response();
    }

    void set_sensor(Sensor &sensor, float value)
    {
        if (!sensor.has_state() || sensor.get_raw_state() != value)
            sensor.publish_state(value);
    }


    int modify_bit(int n, int p, int b) 
    { 
        int mask = 1 << p; 
        return ((n & ~mask) | (b << p)); 
    } 

    void temp_cmd(int temp){
        std::vector<uint8_t> request = { 0x00, 0x40, 0x29, 0x00, 0x00, 0x01, 0x01, 0xFE, 0x01,
        0x00, 0x00, 0x65, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00};
        int pos = 17;
        request.at(pos) = temp << 1 ;
        request.at(pos) = modify_bit(request.at(pos), 0, 1);
        uint16_t sum = 0;
        // run for loop from 0 to vecSize
        for(unsigned int i = 0; i < request.size(); i++)
        {
            sum = sum + request[i];
        }
        request.insert(request.end(), { (uint8_t)((sum & 0xFF00) >> 8), (uint8_t)(sum & 0x00FF) });
        request.insert(request.begin(), {0xF4, 0xF5,}); // Header
        request.insert(request.end(), {0xF4, 0xFB}); // Footer
        // std::vector<uint8_t> buffer(request);
        // uint8_t * ptr = reinterpret_cast<uint8_t*>(request.data());

        int size=request.size();
        uint8_t arr[size];
        for (int i = 0; i < size; i++) {
            arr[i] = request[i];
        }

        send_command(arr, sizeof(arr));

    }

    void set_temp(int temp)
    {
        temp_cmd(temp);
        
    }

    uint8_t int_buf[256];
    // Device_Status dev_stat;
};
