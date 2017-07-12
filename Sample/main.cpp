#include "mbed.h"
#include "EthernetInterface.h"
#include "utils/include/cli.h"
#include "TCPServer.h"
#include "TCPSocket.h"
#include "config.h"

/*****************************************************************************/
/*                                 Variables                                 */
/*****************************************************************************/
char message[BUFFER_SIZE];
char sock_message[BUFFER_SIZE];
bool eth_started = false;
bool connected = false;
DigitalOut  green(LED1);
DigitalOut  blue(LED2);
DigitalOut  red(LED3);
DigitalIn   user_button(USER_BUTTON);
EthernetInterface eth;
TCPSocket socket;
SocketAddress adresses;
nsapi_error_t ns_error;
int scount = 0;
int rcount = -1;
/*****************************************************************************/
/*****************************************************************************/

static void print_prompt(void) {
    usb_uart.putc('=');
    usb_uart.putc('>');
    usb_uart.putc(' ');    
}

inline void handle_socket_incoming(void) {
    if (connected) {
        rcount = socket.recv(sock_message, BUFFER_SIZE);
        if (rcount > 0) usb_uart.printf("recv %d [%s]\n", rcount, sock_message);
        else usb_uart.printf("Nothing to receive: %d\n", rcount);
    }
    else usb_uart.printf("You're not connected!\n");
}

void connect_to_nuc(void) {
    if (eth_started) {
        usb_uart.printf("Attempting to connect to %s on port %d . . .", TARGET_IP, TARGET_PORT);
        socket.open(&eth);
        ns_error = socket.connect(TARGET_IP, TARGET_PORT);
        if (!ns_error) {
            usb_uart.printf(" connection established!\n");
            connected = true;
            handle_socket_incoming(); 
        }
        else usb_uart.printf(" connection failed. Error Code: %d\n", ns_error);
    }
    else usb_uart.printf("Can't. Ethernet did not come up!\n");
}

void handle_input(void) {
    if (!strcmp("green", message)) green = !green;
    else if (!strcmp("red", message)) red = !red;
    else if (!strcmp("blue", message)) blue = !blue;
    else if (!strcmp("connect", message)) connect_to_nuc();
    else if (!strncmp("send", message, 4)) {
        if (strlen(message) > 6) {
            scount = socket.send(&message[5], strlen(message) - 5);
            usb_uart.printf("sent %d [%.*s]\n", scount, strstr(&message[5], "\r\n") - &message[5], &message[5]);    
        }
        else usb_uart.printf("Can't send nothing!!\n");
    }
    else if (!strcmp("receive", message)) handle_socket_incoming();
    else if (message[0] != 0) usb_uart.printf("Didn't recognize '%s'\n", message);
    print_prompt();
}

inline void handle_usb_uart(void) {
    if (usb_uart.readable()) receiveHandler();
    if (messageAvailable()) {
        getMessage(message, BUFFER_SIZE);
        handle_input();
    }    
}

inline void handle_button(void) {
    green = ~green;
    red = ~red;
    blue = ~blue;
}

void initialize_networking(void) {
    usb_uart.printf("Attempting to connect to network . . .\n");
    if (!eth.connect()) eth_started = true;
    if (eth_started) usb_uart.printf("Internet enabled, IP: %s\n", eth.get_ip_address());
    else usb_uart.printf("Could not connect.\n");    
}

void initialization(void) {
    init_cli();
    //initialize_networking();
    print_prompt();
}

int main(void) {
    
    initialization();
    
    while (1) {
        
        handle_usb_uart();
        
        if (user_button) handle_button();
        
    }
}
