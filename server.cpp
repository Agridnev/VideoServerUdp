#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

const int readBufferSize = 256;
char readBuffer[readBufferSize];
const int writeBufferSize = 512;
char writeBuffer[writeBufferSize];

Server::Server(Camera *camera, ImageCompressor *imageCompressor, int port) : camera(camera), imageCompressor(imageCompressor), port(port)
{

}

Server::~Server()
{

}

void Server::run()
{
    int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s == -1)
    {
        printf("Cannot create socket\n");
        fflush(stdout);
        return;
    }
    struct sockaddr_in si_me;
    memset((char *) &si_me, 0, sizeof(si_me));
    si_me.sin_family = AF_INET;
    si_me.sin_port = htons(port);
    si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(s, (struct sockaddr*) &si_me, sizeof(si_me)) == -1)
    {
        printf("Cannot bind socket\n");
        fflush(stdout);
        return;
    }
    CompressedImage compressedFrame;
    while (true)
    {
        struct sockaddr_in si_other;
        unsigned int slen = sizeof(si_other);
        int recv_len = recvfrom(s, readBuffer, readBufferSize, 0, (struct sockaddr *) &si_other, &slen);
        if (recv_len == -1)
        {
            printf("Cannot receive data\n");
            fflush(stdout);
            return;
        }
        if (readBuffer[0] == 0 && recv_len == 1)
        {
            camera->capture();
            compressedFrame = imageCompressor->compress(camera->getFrame());
            int parts = compressedFrame.getSize() / writeBufferSize;
            if (compressedFrame.getSize() % writeBufferSize)
                ++parts;
            *((int *) writeBuffer) = parts;
            if (sendto(s, writeBuffer, sizeof(int), 0, (struct sockaddr*) &si_other, slen) == -1)
            {
                printf("Cannot send data\n");
                fflush(stdout);
                return;
            }
        }
        else if (readBuffer[0] == 1 && recv_len == 5)
        {
            int part = *((int *) (readBuffer + 1));
            int offset = part * writeBufferSize;
            int size = compressedFrame.getSize() - offset;
            if (size > writeBufferSize)
                size = writeBufferSize;
            if (offset >= 0 && offset < compressedFrame.getSize() && size > 0)
            {
                memcpy(writeBuffer, (char *) compressedFrame.getData() + offset, size);
                if (sendto(s, writeBuffer, size, 0, (struct sockaddr*) &si_other, slen) == -1)
                {
                    printf("Cannot send data\n");
                    fflush(stdout);
                    return;
                }
            }
            else
            {
                printf("Got some trash\n");
                printf("Offset: %d, Size: %d, ImageSize: %d\n", offset, size, compressedFrame.getSize());
                fflush(stdout);
            }
        }
        else
        {
            printf("Got some trash\n");
            fflush(stdout);
        }
    }
    close(s);
}
