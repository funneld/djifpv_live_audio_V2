#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define UDP_PORT 45151

static int sock;
static struct sockaddr_in dest_addr;

// Function pointers for the original function
static uint32_t (*pcm_read_hook)(void *pcm, void *data, unsigned int count);

static void init_udp_socket(char* dest_ip, int dest_port) {
    // Create a UDP socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(dest_port);
    dest_addr.sin_addr.s_addr = inet_addr(dest_ip);
}

static void send_pcm_data(unsigned char* pcm_data, unsigned int pcm_data_size) {
    // Send the PCM data to the destination IP and port
    sendto(sock, pcm_data, pcm_data_size, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
}

// Load the original pcm_read function
static void load_original_func() {
    pcm_read_hook = dlsym(RTLD_NEXT, "pcm_read");
    if (pcm_read_hook == 0) {
        void* guiLib = dlopen("/system/lib/libtinyalsa.so", 1);
        pcm_read_hook = dlsym(guiLib, "pcm_read");
        if (pcm_read_hook == 0) {
            printf("dlsym: %s\n", dlerror());
        }
    }
}

uint32_t pcm_read(void *pcm, void *data, unsigned int count) {

	// Load the original function if it has not been loaded yet
	if (pcm_read_hook == NULL) {
		load_original_func();
		init_udp_socket("192.168.41.2", UDP_PORT);
	}

	// Call the original function with the same parameters
	uint32_t ret = pcm_read_hook(pcm, data, count);

	// Send the intercepted audio data over the UDP socket
	send_pcm_data(data, count);

	return ret;

}