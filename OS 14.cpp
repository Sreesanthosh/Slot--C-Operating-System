#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

// Function to create a file in the directory
void create_file(const char *directory, const char *filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    FILE *file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error creating file");
        return;
    }
    printf("File '%s' created successfully in directory '%s'.\n", filename, directory);
    fclose(file);
}

// Function to delete a file from the directory
void delete_file(const char *directory, const char *filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "%s/%s", directory, filename);

    if (remove(filepath) == 0) {
        printf("File '%s' deleted successfully from directory '%s'.\n", filename, directory);
    } else {
        perror("Error deleting file");
    }
}

// Function to list all files in the directory
void list_files(const char *directory) {
    DIR *dir = opendir(directory);
    struct dirent *entry;

    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }

    printf("Files in directory '%s':\n", directory);
    while ((entry = readdir(dir)) != NULL) {
        // Skip '.' and '..' entries
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}

// Function to display menu and handle user input
void display_menu() {
    printf("\nFile Organizer Program\n");
    printf("1. List Files\n");
    printf("2. Create File\n");
    printf("3. Delete File\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    const char *directory = "./files"; // Single-level directory

    // Check if directory exists, create if not
    if (access(directory, F_OK) == -1) {
        if (mkdir(directory, 0777) == -1) {
            perror("Error creating directory");
            return 1;
        }
        printf("Directory '%s' created.\n", directory);
    }

    int choice;
    char filename[256];

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                list_files(directory);
                break;
            case 2:
                printf("Enter filename to create: ");
                scanf("%s", filename);
                create_file(directory, filename);
                break;
            case 3:
                printf("Enter filename to delete: ");
                scanf("%s", filename);
                delete_file(directory, filename);
                break;
            case 4:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

