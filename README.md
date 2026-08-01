# 🎓 Student Management System

A console-based Student Management System built in **C**, developed as a Mini Lab Project for the course **CSE123: Data Structure**, Department of Computer Science and Engineering, Daffodil International University.

## 📖 Overview

This project centralizes student-related academic data into a structured, file-persisted system. It supports two roles — **Admin** and **Student** — each with password-based authentication, and stores all records (students, courses, results) in a binary file (`data.dat`) so data survives across program runs.

## ✨ Features

### Admin
- **Student Management** — Create, update, and delete student records
- **Course Management** — Create, display, delete courses; assign/unassign courses to students
- **Display Students / Courses** — View all stored records with full detail
- **Add Result** — Record Quiz 1–3, Midterm, and Final marks per course
- **Change Admin Password**
- **Save / Load** — Persist all data to/from `data.dat`

### Student
- **Login** — Authenticate with Student ID and password
- **View Profile** — See personal academic details
- **Registered Courses** — View enrolled courses
- **View Results** — See scores per course
- **Change Password**

## 🧱 Design

- **Core Data Structures:**
  - `Student` struct — ID, name, department, gender, DOB, blood group, address, phone, password, CGPA, enrolled course list, and results array
  - `Course` struct — code, title, credit
  - `Result` struct — course code, quiz1–3, mid, final marks
- **Storage:** Fixed-size arrays (`MAX_STU = 300`, `MAX_COU = 150`) hold student and course records in memory during runtime
- **Persistence:** Binary file I/O (`fread`/`fwrite`) saves and loads all student, course, and admin password data via `data.dat`
- **Two-role access control:** Separate menus and permissions for Admin vs. Student

## 🛠️ How to Compile & Run

```bash
gcc main.c -o student_system
./student_system
```

**Default admin login:**
- Username: `admin`
- Password: `1234`

## 📋 Menu Structure

```
=== Student Management System ===
1. Admin Login
2. Student Login
3. Exit
```

**Admin Menu:**
```
1. Student Mgmt (Create / Update / Delete)
2. Course Mgmt (Create / Display / Delete / Assign / Unassign)
3. Display Students
4. Display Courses
5. Add Result
6. Change Password
7. Save
8. Load
9. Logout
```

**Student Menu:**
```
1. View Profile
2. Registered Courses
3. View Results
4. Change Password
5. Logout
```

## 🧪 Testing

The system was tested for:
1. Creating a new student profile
2. Preventing duplicate student IDs
3. Updating student details and confirming changes persist
4. Assigning and unassigning courses
5. Adding and viewing results per course
6. Admin and student login authentication
7. Data persistence across program restarts via save/load

## 👥 Team Members

| Student Name | Student ID |
|---|---|
| Sadek Ahmed Raj | 251-15-511 |
| Toukir Ahmed | 251-15-216 |
| Tanvir Hossain | 251-15-203 |
| Khatheja Islam Mysha | 251-15-031 |

**Supervised by:** Raja Tariqul Hasan Tusher, Assistant Professor, Department of CSE, Daffodil International University

## 🚧 Limitations

- No graphical user interface (console-based only)
- No database support — all data stored in a flat binary file
- No multi-user or networked/online access

## 🔭 Future Work

- Database integration (e.g., MySQL) for better scalability
- GUI-based interface
- Role-based access control (Admin, Teacher, Student)
- Report export and automated result generation
- Web or mobile application support

## 📚 References

1. Jon Kleinberg and Eva Tardos — *Algorithm Design*, Pearson Education India, 2006
2. GeeksforGeeks — Student Management System in C
3. Brian W. Kernighan & Dennis M. Ritchie — *The C Programming Language*, PHI, 1988
4. TutorialsPoint — File Handling in C
5. StudyTonight — Data Structures in C
6. Roger S. Pressman — *Software Engineering: A Practitioner's Approach*, McGraw-Hill

## 📄 License

This project was developed for academic purposes as part of the CSE123 course at DIU.
