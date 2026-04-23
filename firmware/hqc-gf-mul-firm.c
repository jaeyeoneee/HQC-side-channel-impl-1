#ifndef SS_VER
#define SS_VER SS_VER_2_1
#endif

#include "hal.h"
#include "simpleserial.h"
#include <stdint.h>

extern uint16_t gf_mul_bridge(uint16_t a, uint16_t b);

static uint8_t g_a = 0;
static uint8_t g_b = 0;
static volatile uint16_t g_result = 0;

uint8_t cmd_set_input(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
    (void)cmd;
    (void)scmd;

    if (len < 2) {
        return 1;
    }

    g_a = buf[0];
    g_b = buf[1];
    return 0;
}

uint8_t cmd_capture(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
    (void)cmd;
    (void)scmd;
    (void)len;
    (void)buf;

    trigger_high();
    g_result = gf_mul_bridge((uint16_t)g_a, (uint16_t)g_b);
    trigger_low();

    return 0;
}

uint8_t cmd_read_result(uint8_t cmd, uint8_t scmd, uint8_t len, uint8_t *buf)
{
    (void)cmd;
    (void)scmd;
    (void)len;
    (void)buf;

    uint8_t out[2];
    out[0] = (uint8_t)((g_result >> 8) & 0xFF);
    out[1] = (uint8_t)(g_result & 0xFF);

    simpleserial_put('r', 2, out);
    return 0;
}

int main(void)
{
    platform_init();
    init_uart();
    trigger_setup();

    simpleserial_init();
    simpleserial_addcmd('j', 2, cmd_set_input);
    simpleserial_addcmd('c', 0, cmd_capture);
    simpleserial_addcmd('r', 0, cmd_read_result);

    while (1) {
        simpleserial_get();
    }
}