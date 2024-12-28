#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "employees.dat"

// Structure to store employee details
typedef struct {
    int id;
    char name[50];
    int age;
    double salary;
} Employee;

// Function to add a new employee to the file
void add_employee() {
    FILE *file = fopen(FILE_NAME, "ab");  // Open the file in append-binary mode
    if (!file) {
        perror("Error opening file");
        return;
    }

    Employee emp;
    printf("Enter Employee ID: ");
    scanf("%d", &emp.id);
    getchar();  // To consume the newline character after the integer input
    printf("Enter Employee Name: ");
    fgets(emp.name, sizeof(emp.name), stdin);
    emp.name[strcspn(emp.name, "\n")] = '\0';  // Remove the newline character at the end of the name
    printf("Enter Employee Age: ");
    scanf("%d", &emp.age);
    printf("Enter Employee Salary: ");
    scanf("%lf", &emp.salary);

    fwrite(&emp, sizeof(Employee), 1, file);  // Write the employee data to the file
    fclose(file);

    printf("Employee added successfully!\n");
}

// Function to view employee details by ID
void view_employee() {
    FILE *file = fopen(FILE_NAME, "rb");  // Open the file in read-binary mode
    if (!file) {
        perror("Error opening file");
        return;
    }

    int search_id;
    printf("Enter Employee ID to view: ");
    scanf("%d", &search_id);

    Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == search_id) {
            printf("Employee ID: %d\n", emp.id);
            printf("Name: %s\n", emp.name);
            printf("Age: %d\n", emp.age);
            printf("Salary: %.2lf\n", emp.salary);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", search_id);
    }

    fclose(file);
}

// Function to update employee details by ID
void update_employee() {
    FILE *file = fopen(FILE_NAME, "rb+");  // Open the file in read-write-binary mode
    if (!file) {
        perror("Error opening file");
        return;
    }

    int search_id;
    printf("Enter Employee ID to update: ");
    scanf("%d", &search_id);

    Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id == search_id) {
            printf("Employee found! Enter new details.\n");
            emp.id = search_id;
            getchar();  // Consume newline left by previous scanf
            printf("Enter new name: ");
            fgets(emp.name, sizeof(emp.name), stdin);
            emp.name[strcspn(emp.name, "\n")] = '\0';  // Remove newline
            printf("Enter new age: ");
            scanf("%d", &emp.age);
            printf("Enter new salary: ");
            scanf("%lf", &emp.salary);

            fseek(file, -sizeof(Employee), SEEK_CUR);  // Move the file pointer back to the employee's position
            fwrite(&emp, sizeof(Employee), 1, file);  // Write the updated employee data
            found = 1;
            printf("Employee details updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Employee with ID %d not found.\n", search_id);
    }

    fclose(file);
}

// Function to delete an employee by ID (overwrite the record)
void delete_employee() {
    FILE *file = fopen(FILE_NAME, "rb");  // Open the file in read-binary mode
    if (!file) {
        perror("Error opening file");
        return;
    }

    FILE *temp_file = fopen("temp.dat", "wb");  // Temporary file to store updated records
    if (!temp_file) {
        perror("Error creating temporary file");
        fclose(file);
        return;
    }

    int delete_id;
    printf("Enter Employee ID to delete: ");
    scanf("%d", &delete_id);

    Employee emp;
    int found = 0;
    while (fread(&emp, sizeof(Employee), 1, file)) {
        if (emp.id != delete_id) {
            fwrite(&emp, sizeof(Employee), 1, temp_file);  // Write all records except the one to be deleted
        } else {
            found = 1;
        }
    }

    fclose(file);
    fclose(temp_file);

    if (found) {
        // Remove the original file and rename the temporary file
        remove(FILE_NAME);
        rename("temp.dat", FILE_NAME);
        printf("Employee with ID %d deleted successfully!\n", delete_id);
    } else {
        printf("Employee with ID %d not found.\n", delete_id);
    }
}

// Function to display the menu and handle user input
void display_menu() {
    printf("\nEmployee Details Management System\n");
    printf("1. Add Employee\n");
    printf("2. View Employee\n");
    printf("3. Update Employee\n");
    printf("4. Delete Employee\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_employee();
                break;
            case 2:
                view_employee();
                break;
            case 3:
                update_employee();
                break;
            case 4:
                delete_employee();
                break;
            case 5:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

