# Student Management System

A console-based Student Management System developed in C++ using Object-Oriented Programming principles. This project provides a simple interface to manage student records, including operations like adding, updating, viewing, and deleting student data.

---

## Disclaimer

This program is for **educational/demo purposes only**. It is a simulation and does **not interact with any real student database or institution**.

---


## Core Features

| Role | What you can do |
|------|-----------------|
| **Admin** | • Initialise database<br> • Add / delete students, faculty, courses<br> • Full record view<br> • Auto-generates roll numbers, faculty IDs, and passwords |
| **Faculty** | • Edit profile<br> • Record marks & attendance<br> • View course details |
| **Faculty Advisor** | All faculty powers along with approve / reject leave requests |
| **Student** | • Edit profile<br> • Register extra courses (≤ 2/sem)<br> • Check marks & attendance<br> • Apply for leave |
| **Everyone** | Clean CLI with secured and masked password input |

---

## Concepts Used

- Object-Oriented Programming (OOP)
- CSV File Handling in C++
- Menu-Driven Console UI
- Input Validation and Data Formatting
- Vector and Class Usage
- Data Structures

---

## How to Run

1. **Clone the repository**
   ```bash
   git clone https://github.com/Vishwasdabhi/Student-Management-System
   cd Student-Management-System
   ```

2. **Compile the code**
   ```bash
   g++ main.cpp -o student_management.exe
   ```

3. **Run the program**
   ```bash
   ./student_management.exe
   ```
---
##  File Layout

```
.
├── driver.cpp      # Entry point & main loop
├── frontend.h      # CLI menus & input helpers
├── backend.h       # File I/O, simple cipher, global containers
├── classes.h       # User, Student, Faculty, FA, Course, Date
└── *.csv / *.txt   # Generated data files
```

---

## Console UI Highlights

- Clear menu-driven interface
- Intuitive prompts for each operation
- Simple and minimal layout for easy understanding

---

## Screenshots

Add terminal screenshots of:

- Add Student prompt
- Displaying student records
- Update/Delete operations

---

## Data Storage

| File | Contents |
|------|----------|
| `student_information.csv` | Student master table |
| `marks_semN.csv` | Marks per semester |
| `attendance_semN.csv` | Attendance per semester |
| `faculty_information.csv` | Faculty roster |
| `leave_applications.txt` | Leave request log |

---

## Resources Used

- C++ STL (vector, iostream, fstream)
- Simple console techniques for UI clarity

---

## Future Scope of improvement

* Replace the CLI with a GUI (Qt 6).  
* Switch CSV storage to SQLite for stronger querying.

---

## Authors

- [Vishwas Dabhi](https://github.com/Vishwasdabhi)
- [Shashank M N](https://github.com/Shashank-M-N)
- [Arit Gandhi](https://github.com/AritGandhi1)

  ---
