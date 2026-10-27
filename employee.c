#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Employee Management System using a Binary Search Tree.
   BST key: employee ID. Beginner-friendly C DSA project. */

typedef struct Employee {
    int id;
    char name[60];
    char department[40];
    float salary;
    struct Employee *left, *right;
} Employee;

Employee *root = NULL;

Employee *createEmployee(int id, const char *name, const char *department, float salary) {
    Employee *node = malloc(sizeof(Employee));
    if (!node) { printf("Memory allocation failed.\n"); return NULL; }
    node->id = id;
    snprintf(node->name, sizeof(node->name), "%s", name);
    snprintf(node->department, sizeof(node->department), "%s", department);
    node->salary = salary;
    node->left = node->right = NULL;
    return node;
}

Employee *searchEmployee(Employee *node, int id) {
    if (node == NULL || node->id == id) return node;
    if (id < node->id) return searchEmployee(node->left, id);
    return searchEmployee(node->right, id);
}

Employee *insertEmployee(Employee *node, int id, const char *name, const char *department, float salary) {
    if (node == NULL) return createEmployee(id, name, department, salary);
    if (id < node->id) node->left = insertEmployee(node->left, id, name, department, salary);
    else if (id > node->id) node->right = insertEmployee(node->right, id, name, department, salary);
    else printf("Employee ID already exists.\n");
    return node;
}

void inorder(Employee *node) {
    if (!node) return;
    inorder(node->left);
    printf("%-8d %-22s %-18s Rs.%-12.2f\n", node->id, node->name, node->department, node->salary);
    inorder(node->right);
}

Employee *minimumNode(Employee *node) {
    while (node && node->left) node = node->left;
    return node;
}

Employee *deleteEmployee(Employee *node, int id, int *deleted) {
    if (!node) return NULL;
    if (id < node->id) node->left = deleteEmployee(node->left, id, deleted);
    else if (id > node->id) node->right = deleteEmployee(node->right, id, deleted);
    else {
        *deleted = 1;
        if (!node->left) { Employee *r = node->right; free(node); return r; }
        if (!node->right) { Employee *l = node->left; free(node); return l; }
        Employee *successor = minimumNode(node->right);
        node->id = successor->id;
        strcpy(node->name, successor->name);
        strcpy(node->department, successor->department);
        node->salary = successor->salary;
        int ignored = 0;
        node->right = deleteEmployee(node->right, successor->id, &ignored);
    }
    return node;
}

void readLine(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin)) buffer[strcspn(buffer, "\n")] = '\0';
    else buffer[0] = '\0';
}

int readInt(const char *prompt, int *out) {
    char line[100], extra;
    printf("%s", prompt);
    if (!fgets(line, sizeof(line), stdin)) return 0;
    if (sscanf(line, "%d %c", out, &extra) != 1) { printf("Enter a valid whole number.\n"); return 0; }
    return 1;
}

int readSalary(const char *prompt, float *out) {
    char line[100], extra;
    printf("%s", prompt);
    if (!fgets(line, sizeof(line), stdin)) return 0;
    if (sscanf(line, "%f %c", out, &extra) != 1 || *out < 0) {
        printf("Enter a valid non-negative salary.\n"); return 0;
    }
    return 1;
}

void addEmployee(void) {
    int id; char name[60], department[40]; float salary;
    if (!readInt("Enter employee ID: ", &id) || id <= 0) { printf("ID must be positive.\n"); return; }
    if (searchEmployee(root, id)) { printf("Employee ID already exists.\n"); return; }
    printf("Enter employee name: "); readLine(name, sizeof(name));
    printf("Enter department: "); readLine(department, sizeof(department));
    if (!name[0] || !department[0]) { printf("Name and department cannot be empty.\n"); return; }
    if (!readSalary("Enter monthly salary (Rs.): ", &salary)) return;
    Employee *newRoot = insertEmployee(root, id, name, department, salary);
    if (!newRoot && !root) { printf("Could not add employee.\n"); return; }
    root = newRoot;
    printf("Employee added successfully.\n");
}

void listEmployees(void) {
    if (!root) { printf("No employee records yet.\n"); return; }
    printf("\n%-8s %-22s %-18s %-15s\n", "ID", "Name", "Department", "Monthly Salary");
    printf("--------------------------------------------------------------------------\n");
    inorder(root);
}

void findEmployee(void) {
    int id; if (!readInt("Enter employee ID to search: ", &id)) return;
    Employee *e = searchEmployee(root, id);
    if (!e) printf("Employee not found.\n");
    else printf("\nID: %d\nName: %s\nDepartment: %s\nMonthly salary: Rs.%.2f\n", e->id, e->name, e->department, e->salary);
}

void updateSalary(void) {
    int id; float salary;
    if (!readInt("Enter employee ID to update: ", &id)) return;
    Employee *e = searchEmployee(root, id);
    if (!e) { printf("Employee not found.\n"); return; }
    printf("Current salary: Rs.%.2f\n", e->salary);
    if (!readSalary("Enter new monthly salary (Rs.): ", &salary)) return;
    e->salary = salary;
    printf("Salary updated.\n");
}

void removeEmployee(void) {
    int id, deleted = 0;
    if (!readInt("Enter employee ID to delete: ", &id)) return;
    root = deleteEmployee(root, id, &deleted);
    printf(deleted ? "Employee deleted successfully.\n" : "Employee not found.\n");
}

void summary(void) {
    Employee *stack[10000]; int top = -1, count = 0; double payroll = 0;
    if (root) stack[++top] = root;
    while (top >= 0) {
        Employee *e = stack[top--]; count++; payroll += e->salary;
        if (e->left && top < 9998) stack[++top] = e->left;
        if (e->right && top < 9998) stack[++top] = e->right;
    }
    printf("\n--- Employee Summary ---\nTotal employees: %d\nTotal monthly payroll: Rs.%.2f\n", count, payroll);
    if (count) printf("Average monthly salary: Rs.%.2f\n", payroll / count);
}

void freeTree(Employee *node) {
    if (!node) return;
    freeTree(node->left); freeTree(node->right); free(node);
}

int main(void) {
    int choice;
    do {
        printf("\n====== EMPLOYEE MANAGEMENT SYSTEM ======\n");
        printf("1. Add employee\n2. Display employees (sorted by ID)\n3. Search employee\n");
        printf("4. Update salary\n5. Delete employee\n6. Employee summary\n0. Exit\n");
        if (!readInt("Choose an option: ", &choice)) continue;
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: listEmployees(); break;
            case 3: findEmployee(); break;
            case 4: updateSalary(); break;
            case 5: removeEmployee(); break;
            case 6: summary(); break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid option.\n");
        }
    } while (choice != 0);
    freeTree(root);
    return 0;
}
