# Charity Donations Management System (C++)

First-semester **Computer Programming Fundamentals** course project.

This is a console-based C++ application to manage a small charity workflow with:
- **Admin panel** (collections, donors, receivers)
- **Donor panel** (register/login/add donation)
- **Receiver panel** (request/get donation + feedback)
- File-based data storage using `.txt` files

## Project Files
- `FINAL.cpp` – main C++ source code
- `donors.txt` – saved donor records and donation amounts
- `feedbacks.txt` – receiver request/feedback records
- `records.txt` – donor login credentials

## Default Admin Login
- Username: `admin`
- Password: `1234`

## How to Compile and Run

### On macOS / Linux
```bash
g++ FINAL.cpp -o charity
./charity
```

### On Windows (MinGW)
```bash
g++ FINAL.cpp -o charity.exe
charity.exe
```

## Program Flow
1. Open **Main Menu**
2. Choose **Admin Panel** or **User Panel**
3. Donors can register/login and add donations
4. Receivers can submit request details and receive amount
5. Admin can view/delete donors and receiver records
6. Total collection is calculated from donations and receiver deductions

## Notes
- Data is stored in plain text files in the same folder.
- Keep all `.txt` files with the executable, otherwise data may not load.
- The program uses `system("cls")` for screen clearing (Windows style). On macOS/Linux this may not clear the terminal.

## Learning Objectives Covered
- Functions and modular design
- `struct` usage
- Dynamic arrays (`new[]` / `delete[]`)
- File handling with `ifstream` / `ofstream`
- Menus, loops, and conditional logic

---
Developed as a semester project for C++ fundamentals.
