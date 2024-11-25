#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include "FileHandler.h"
#include "Supervisor.h"
#include "Director.h"
#include "Employee.h"
#include "AttendanceRecord.h"
#include "LeaveFactory.h"

using namespace std;

// Function prototypes
void displayEmployeeMenu(Employee& employee);
void displaySupervisorMenu(Supervisor& supervisor, vector<shared_ptr<Leave>>& leaveRequests);
void displayDirectorMenu(Director& director, vector<shared_ptr<Leave>>& leaveRequests);

// Main Function
int main() {
    // Load data using FileHandler
    std::vector<std::shared_ptr<Employee>> employees;
    vector<shared_ptr<Leave>> leaveRequests;  // Shared pointers for leave requests
    FileHandler::readEmployeeData(employees);
    FileHandler::readLeaveData(leaveRequests);

    // Role-based system
    cout << "Welcome to Attendance and Leave Management System!" << endl;
    cout << "Select your role:\n1. Employee\n2. Supervisor\n3. Director\nEnter your choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        // Employee Role
        int empId;
        cout << "Enter your Employee ID: ";
        cin >> empId;

        // Find the employee
         loggedInEmployee = nullptr;
        for (auto emp : employees) {
            if (emp->getEmployeeId() == empId) {
                loggedInEmployee = emp;
                break;
            }
        }

        if (loggedInEmployee) {
            displayEmployeeMenu(*loggedInEmployee);
        } else {
            cout << "Error: Employee not found!" << endl;
        }
    } else if (choice == 2) {
        // Supervisor Role
        Supervisor supervisor(999, "Supervisor");  // Temporary supervisor object
        displaySupervisorMenu(supervisor, leaveRequests);
    } else if (choice == 3) {
        // Director Role
        Director director(888, "Director");  // Temporary director object
        displayDirectorMenu(director, leaveRequests);
    } else {
        cout << "Invalid choice. Exiting system." << endl;
    }

    return 0;
}

// Function to display Employee Menu
void displayEmployeeMenu(Employee& employee) {
    int option;
    do {
        cout << "\n--- Employee Menu ---" << endl;
        cout << "1. View Attendance Details\n2. Request Leave\n3. View Leave Status\n4. View Leave Report\n5. Exit\nEnter your choice: ";
        cin >> option;

        switch (option) {
        case 1:
            employee.generateAttendanceReport();
            break;
        case 2: {
            string leaveType, startDate, endDate, reason;
            cout << "Enter Leave Type (Casual/Earned/Official/Unpaid): ";
            cin >> leaveType;
            cout << "Enter Start Date (YYYY-MM-DD): ";
            cin >> startDate;
            cout << "Enter End Date (YYYY-MM-DD): ";
            cin >> endDate;
            cout << "Enter Reason for Leave: ";
            cin.ignore();
            getline(cin, reason);
            employee.requestLeave(leaveType, startDate, endDate, reason);
            break;
        }
        case 3: {
            int leaveId;
            cout << "Enter Leave ID to check status: ";
            cin >> leaveId;
            employee.checkLeaveStatus(leaveId);
            break;
        }
        case 4:
            employee.generateLeaveReport();
            break;
        case 5:
            cout << "Exiting Employee Menu..." << endl;
            break;
        default:
            cout << "Invalid option. Try again!" << endl;
        }
    } while (option != 5);
}

// Function to display Supervisor Menu
void displaySupervisorMenu(Supervisor& supervisor, vector<shared_ptr<Leave>>& leaveRequests) {
    int option;
    do {
        cout << "\n--- Supervisor Menu ---" << endl;
        cout << "1. View Pending Leave Requests\n2. Approve/Reject Leave\n3. Exit\nEnter your choice: ";
        cin >> option;

        switch (option) {
        case 1:
            supervisor.checkLeaveRequests(leaveRequests);
            break;
        case 2: {
            int leaveId;
            string decision;
            cout << "Enter Leave ID to Approve/Reject: ";
            cin >> leaveId;
            cout << "Enter Decision (Approve/Reject): ";
            cin >> decision;

            for (auto& leave : leaveRequests) {
                if (leave->getLeaveId() == leaveId) {
                    leave->setStatus(decision);
                    supervisor.notifyLeaveApproval(decision);
                    break;
                }
            }
            break;
        }
        case 3:
            cout << "Exiting Supervisor Menu..." << endl;
            break;
        default:
            cout << "Invalid option. Try again!" << endl;
        }
    } while (option != 3);
}

// Function to display Director Menu
void displayDirectorMenu(Director& director, vector<shared_ptr<Leave>>& leaveRequests) {
    int option;
    do {
        cout << "\n--- Director Menu ---" << endl;
        cout << "1. View Pending Leave Requests\n2. Approve/Reject Leave\n3. Exit\nEnter your choice: ";
        cin >> option;

        switch (option) {
        case 1:
            director.checkLeaveRequests(leaveRequests);
            break;
        case 2: {
            int leaveId;
            string decision;
            cout << "Enter Leave ID to Approve/Reject: ";
            cin >> leaveId;
            cout << "Enter Decision (Approve/Reject): ";
            cin >> decision;

            for (auto& leave : leaveRequests) {
                if (leave->getLeaveId() == leaveId) {
                    leave->setStatus(decision);
                    director.notifyLeaveApproval(decision);
                    break;
                }
            }
            break;
        }
        case 3:
            cout << "Exiting Director Menu..." << endl;
            break;
        default:
            cout << "Invalid option. Try again!" << endl;
        }
    } while (option != 3);
}
