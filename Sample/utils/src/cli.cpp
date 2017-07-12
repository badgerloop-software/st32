#include "../include/cli.h"
#include "../../config.h"

Serial usb_uart(SERIAL_TX, SERIAL_RX, 115200);

PC_Buffer tx_buffer, rx_buffer;
volatile uint8_t availableCount = 0;

void init_cli(void) {
    pc_buffer_init(&tx_buffer, BUFFER_SIZE);
    pc_buffer_init(&rx_buffer, BUFFER_SIZE);
    usb_uart.printf("\n%s running.\n", APPLICATION_NAME);
}

bool messageAvailable(void) { return availableCount > 0; }

void getMessage(char *message, int maxLength) {
    char curr = '\0', prev = '\0';
    int index = 0;
    
    if (!messageAvailable()) return;
    
    while (index < maxLength && !pc_buffer_empty(&rx_buffer)) {
        prev = curr;
        pc_buffer_remove(&rx_buffer, &curr);
        message[index++] = (NEWLINE_GUARD) ? '\0' : curr;
        if (NEWLINE_GUARD) {
            availableCount--;
            return;
        }
    }
}

void receiveHandler(void) {
    static char prev = '\0', curr = '\0';
    
    prev = curr;
    curr = usb_uart.getc();
    if (curr == 0x08) {
        if (!pc_buffer_empty(&rx_buffer)) {
            usb_uart.putc('\b');
            rx_buffer.produce_count--;
        }
    }
    else {
        usb_uart.putc(curr);
        if (NEWLINE_GUARD) availableCount++;
        if (!pc_buffer_full(&rx_buffer)) pc_buffer_add(&rx_buffer, curr);
    }
}