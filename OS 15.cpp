#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

#define ROOT_DIR "./root"  // The root directory where subdirectories will be stored

// Function to create a subdirectory in the root directory
void create_subdirectory(const char *subdir_name) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", ROOT_DIR, subdir_name);

    if (mkdir(path, 0777) == 0) {
        printf("Subdirectory '%s' created successfully.\n", subdir_name);
    } else {
        perror("Error creating subdirectory");
    }
}

// Function to list files in a subdirectory
void list_files(const char *subdir_name) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", ROOT_DIR, subdir_name);

    DIR *dir = opendir(path);
    struct dirent *entry;

    if (dir == NULL) {
        perror("Error opening subdirectory");
        return;
    }

    printf("Files in subdirectory '%s':\n", subdir_name);
    while ((entry = readdir(dir)) != NULL) {
        // Skip '.' and '..'
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            printf("%s\n", entry->d_name);
        }
    }
    closedir(dir);
}

// Function to create a file in a subdirectory
void create_file(const char *subdir_name, const char *filename) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s/%s", ROOT_DIR, subdir_name, filename);

    FILE *file = fopen(path, "w");
    if (file == NULL) {
        perror("Error creating file");
        return;
    }
    printf("File '%s' created in subdirectory '%s'.\n", filename, subdir_name);
    fclose(file);
}

// Function to delete a file from a subdirectory
void delete_file(const char *subdir_name, const char *filename) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s/%s", ROOT_DIR, subdir_name, filename);

    if (remove(path) == 0) {
        printf("File '%s' deleted from subdirectory '%s'.\n", filename, subdir_name);
    } else {
        perror("Error deleting file");
    }
}

// Function to delete a subdirectory
void delete_subdirectory(const char *subdir_name) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s", ROOT_DIR, subdir_name);

    if (rmdir(path) == 0) {
        printf("Subdirectory '%s' deleted successfully.\n", subdir_name);
    } else {
        perror("Error deleting subdirectory");
    }
}

// Function to display the main menu and handle user input
void display_menu() {
    printf("\nTwo-Level Directory Organizer\n");
    printf("1. Create Subdirectory\n");
    printf("2. List Files in Subdirectory\n");
    printf("3. Create File in Subdirectory\n");
    printf("4. Delete File from Subdirectory\n");
    printf("5. Delete Subdirectory\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    // Check if the root directory exists, create it if not
    if (access(ROOT_DIR, F_OK) == -1) {
        if (mkdir(ROOT_DIR, 0777) == -1) {
            perror("Error creating root directory");
            return 1;
        }
        printf("Root directory '%s' created.\n", ROOT_DIR);
    }

    int choice;
    char subdir_name[256], filename[256];

    while (1) {
        display_menu();
        scanf("%d", &choice);
        getchar();  // To consume the newline character left by scanf

        switch (choice) {
            case 1:
                printf("Enter subdirectory name: ");
                fgets(subdir_name, sizeof(subdir_name), stdin);
                subdir_name[strcspn(subdir_name, "\n")] = '\0';  // Remove newline character
                create_subdirectory(subdir_name);
                break;
            case 2:
                printf("Enter subdirectory name: ");
                fgets(subdir_name, sizeof(subdir_name), stdin);
                subdir_name[strcspn(subdir_name, "\n")] = '\0';
                list_files(subdir_name);
                break;
            case 3:
                printf("Enter subdirectory name: ");
                fgets(subdir_name, sizeof(subdir_name), stdin);
                subdir_name[strcspn(subdir_name, "\n")] = '\0';
                printf("Enter filename to create: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                create_file(subdir_name, filename);
                break;
            case 4:
                printf("Enter subdirectory name: ");
                fgets(subdir_name, sizeof(subdir_name), stdin);
                subdir_name[strcspn(subdir_name, "\n")] = '\0';
                printf("Enter filename to delete: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';
                delete_file(subdir_name, filename);
                break;
            case 5:
                printf("Enter subdirectory name: ");
                fgets(subdir_name, sizeof(subdir_name), stdin);
                subdir_name[strcspn(subdir_name, "\n")] = '\0';
                delete_subdirectory(subdir_name);
                break;
            case 6:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

