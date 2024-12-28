// writer.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>

#define MSG_SIZE 100  // Max message size

// Define message structure
struct msgbuf {
    long mtype;  // Message type
    char mtext[MSG_SIZE];  // Message text
};

int main() {
    // Create a unique key for the message queue
    key_t key = ftok("writer.c", 65);  // ftok returns a unique key
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create or access the message queue
    int msgid = msgget(key, 0666 | IPC_CREAT);  // Access the message queue
    if (msgid == -1) {
        perror("msgget failed");
        exit(1);
    }

    // Prepare the message
    struct msgbuf message;
    message.mtype = 1;  // Message type (1 is commonly used for simple messages)
    snprintf(message.mtext, MSG_SIZE, "Hello from the writer process!");

    // Send the message to the queue
    if (msgsnd(msgid, &message, sizeof(message.mtext), 0) == -1) {
        perror("msgsnd failed");
        exit(1);
    }

    printf("Writer: Message sent to queue.\n");

    // Wait before exiting
    printf("Writer: Press Enter to exit...\n");
    getchar();

    // Detach and exit
    return 0;
}

