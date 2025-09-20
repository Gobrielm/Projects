#pragma once

// stdlib
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
// system
#include <fcntl.h>
#include <poll.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h>
// C++
#include <vector>
#include <string>


class HashTable {
    int hash() const {

    }

    struct Node {
        Node *next;
    };

    struct MyData {
        int foo;
        Node node;
    };

    size_t list_size(struct Node *node) {
        size_t cnt = 0;
        for (; node != NULL; node = node->next) {
            cnt++;
        }
        return cnt;
}

};