# _Attendance and Leave Management System_
# Overview
This Attendance and Leave Management System is designed for a commercial organization to handle employee attendance, leave requests, and approvals. It supports different user roles (Employee, Supervisor, Director) and provides features like leave application, attendance tracking, and generating detailed reports.

## System Features
### General Functionalities
+ **Role-based Access**: Supports three roles with unique functionalities:
1. **Employee**: Request leaves, view attendance and leave details.
2. **Supervisor**: Approve/reject leave requests for casual leaves.
3. **Director**: Approve/reject long-term leaves (earned, unpaid).
+ **Data Persistence**: Employee, attendance, and leave data are stored in and retrieved from external text files.
### Employee Functionalities
+ **Attendance Management**:
View attendance records, including dates and hours worked.
Automatically calculate total hours worked.
+ **Leave Management**:
Apply for leaves (Casual, Earned, Official, Unpaid) with details like start date, end date, and reason.
Check the status of previously applied leaves.
Generate a detailed leave report showing leave type, duration, and status.
+ **Data Validations**:
Ensures sufficient leave balance before allowing leave applications.
### Supervisor Functionalities
View all pending leave requests for employees under their supervision.
Approve or reject casual leave requests.
Notify employees about the status of their leave applications.
### Director Functionalities
View all pending leave requests requiring director-level approval (Earned and Unpaid leaves).
Approve or reject leave requests based on company policies.
Notify employees about leave decisions.
### Reporting Functionalities
+ **Attendance Reports**:
Generates reports of employees with less than the required attendance percentage.
+ **Leave Reports**:
Provides details of unapproved or pending leave requests.
Generates individual leave history for employees.
+ **Outstanding Leaves Report**:
Displays all pending leave requests for review.
## File Management
### Files Used in the System
+ **Employees.txt**:
Stores employee details: Employee ID, Name, Role, Total Hours Worked, Casual Leave Balance, Earned Leave Balance.
 **Attendance.txt**:
Stores attendance records: Employee ID, Date, Hours Worked.
+ **Leaves.txt**:
Stores leave details: Leave ID, Employee ID, Leave Type, Start/End Dates, Status, Supervisor Approval, Director Approval.
### File Operations
**Read Operations**:
Load employee, attendance, and leave data into memory at startup.
**Write Operations**:
Append new employee, attendance, and leave data to files.
**Update Operations**:
Modify employee or leave records to reflect changes (e.g., leave status updates).
## Key Design Principles
### Object-Oriented Design:
+ **Inheritance**: Employee class extended by Supervisor and Director.
+ **Polymorphism**: Role-based method overriding (e.g., applyLeave and notifyLeaveApproval).
+ **Encapsulation**: Data members are private, and access is provided through getters and setters.
### Design Patterns:
+ **Factory Pattern**: Used for creating leave objects dynamically.
+ **Strategy Pattern**: Different leave approval workflows for Supervisor and Director roles.
+ **Observer Pattern**: Notify employees upon leave status updates.
### Separation of Concerns:
+ FileHandler class handles all file-related operations.
+ Employee, AttendanceRecord, and Leave classes manage core functionality.
## How to Use
### Setup
Ensure the following text files are available in the project directory:
`Employees.txt`
`Attendance.txt`
`Leaves.txt`
Compile the project using a C++ compiler:

    g++ main.cpp -o attendance_management

Run the compiled executable:


    ./attendance_management

### Usage
1. Upon running the program, select your role (Employee, Supervisor, Director).
2. Perform actions based on the options in your role's menu.
3. View reports and manage data as per your responsibilities.
## Future Enhancements
+ Add graphical user interface (GUI) for better usability.
+ Introduce database integration for scalable and secure data storage.
+ Include automated email notifications for leave approvals/rejections.
+ Add login authentication for role-based access.
## Contributors
### _Mah Rukh, Aansa Younus_
