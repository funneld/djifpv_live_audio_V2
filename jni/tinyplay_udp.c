/* tinyplay.c
**
** Copyright 2011, The Android Open Source Project
**
** Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are met:
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**     * Neither the name of The Android Open Source Project nor the names of
**       its contributors may be used to endorse or promote products derived
**       from this software without specific prior written permission.
**
** THIS SOFTWARE IS PROVIDED BY The Android Open Source Project ``AS IS'' AND
** ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
** IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
** ARE DISCLAIMED. IN NO EVENT SHALL The Android Open Source Project BE LIABLE
** FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
** DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
** SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
** CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
** LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
** OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
** DAMAGE.
*/

#include "tinyalsa/asoundlib.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#define PORT 45151
#define BUFSIZE 4096

void play();
void create_socket();

int sockfd;    
struct sockaddr_in servaddr, cliaddr;
socklen_t len;
	
int main(int argc, char **argv) {   

	create_socket();
	play();

	return 0;
}

void play() {
	
	struct pcm_config config;
	struct pcm *pcm;
	int num_read;
	char buf[BUFSIZE];
	
	config.channels = 2;
	config.rate = 48000;
	config.period_size = 1024;
	config.period_count = 4;
	config.format = PCM_FORMAT_S16_LE;

	pcm = pcm_open(0, 0, PCM_OUT, &config);
	if (!pcm || !pcm_is_ready(pcm)) {
		fprintf(stderr, "Unable to open PCM device (%s)\n",
				pcm_get_error(pcm));
		return;
	}

	printf("Playing: %u ch, %u hz, %u bit\n", config.channels, config.rate, 16);

	while (1) {
		
		if ((num_read = recvfrom(sockfd, buf, BUFSIZE, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len)) < 0) {
			perror("recvfrom error");
			exit(EXIT_FAILURE);
		}
		
		pcm_write(pcm, buf, num_read);
	}

	pcm_close(pcm);
}

void create_socket() {
	
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("socket error");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	
	if (bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
		perror("bind error");
		exit(EXIT_FAILURE);
	}
	
	len = sizeof(cliaddr);
}
