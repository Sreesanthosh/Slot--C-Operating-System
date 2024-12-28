#include <stdio.h>
#include <fcntl.h>  // For open()
#include <unistd.h> // For read(), write(), close()
#include <sys/types.h>
#include <sys/stat.h>

#define BUFFER_SIZE 1024  // Buffer size to read and write in chunks

int main(int argc, char *argv[]) {
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Check for correct number of arguments
    if (argc != 3) {
        write(STDERR_FILENO, "Usage: <source_file> <destination_file>\n", 41);
        return 1;
    }

    // Open source file for reading
    source_fd = open(argv[1], O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        return 1;
    }

    // Open destination file for writing (create if it doesn't exist)
    dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (dest_fd == -1) {
        perror("Error opening destination file");
        close(source_fd);
        return 1;
    }

    // Read from source file and write to destination file in chunks
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }

    // Check for read error
    if (bytes_read == -1) {
        perror("Error reading from source file");
    }

    // Close both files
    close(source_fd);
    close(dest_fd);

    return 0;
}

