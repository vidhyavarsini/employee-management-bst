# PeopleDesk — Employee Management System using Binary Search Tree

Beginner-friendly DSA project in C using a Binary Search Tree (BST), with a separate responsive website demo.

## Features
- Add employees with unique ID, name, department and monthly salary
- Display employees sorted by ID using inorder traversal
- Search employee by ID
- Update salary
- Delete employee (leaf, one-child and two-child cases)
- Show employee count, distinct departments, total payroll and average salary
- Website with search, department filter, add/edit/delete, dashboard cards and CSV export
- Website demo saves changes in browser local storage

## Files
- `employee.c` — C program and BST operations
- `index.html` — website structure
- `style.css` — responsive design
- `app.js` — website features and local storage
- `README.md` — documentation
- `.gitignore` — ignores compiled output

## Important note
The C program is the actual BST implementation. The website is a separate HTML/CSS/JavaScript demo using local storage; it is not connected to the C program. This avoids needing a backend/database for a beginner project.

## Run C program
Windows with GCC:
```bash
gcc employee.c -o employee.exe
.\employee.exe
```
Linux/macOS:
```bash
gcc employee.c -o employee
./employee
```

## Run website
Open `index.html` in a browser or use the VS Code Live Server extension. Sample employee records appear on first use. Changes persist in that browser.

## How the BST works
Each node stores employee ID, name, department, salary and left/right pointers. Employee ID is the key:
- Smaller IDs go to the left subtree.
- Larger IDs go to the right subtree.
- Duplicate IDs are rejected.
- Inorder traversal (left, node, right) displays employees in ascending ID order.
- Deletion handles no child, one child, or two children by replacing a two-child node with its inorder successor.

## Time complexity
Let `h` be the tree height.

| Operation | Average (balanced-ish tree) | Worst case |
|---|---:|---:|
| Insert | O(log n) | O(n) |
| Search | O(log n) | O(n) |
| Update salary | O(log n) | O(n) |
| Delete | O(log n) | O(n) |
| Display all | O(n) | O(n) |

A plain BST may become unbalanced if IDs are inserted in sorted order.

## Presentation explanation
“My project is an Employee Management System using a Binary Search Tree in C. Each employee is stored as a node containing employee ID, name, department, salary and left and right pointers. Employee ID is the BST key. The system supports insertion, searching, salary updates, deletion and inorder traversal. Inorder traversal displays employee records in ascending order of ID. A separate responsive website demonstrates the same workflow in a user-friendly dashboard.”

## GitHub
Suggested repository: `employee-management-bst`

Description: `Beginner-friendly employee management DSA project in C using a Binary Search Tree, with a responsive website demo.`

Topics: `c`, `binary-search-tree`, `data-structures`, `employee-management`, `beginner-project`, `html`, `css`, `javascript`

## Future improvements
- Save C records to a file
- Add email, phone or joining date
- Connect a backend/database
- Use an AVL tree for self-balancing
