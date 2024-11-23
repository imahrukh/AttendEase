#include "FileHandler.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// Define file names
const string FileHandler::employeeFile = "employees.txt";
const string FileHandler::attendanceFile = "attendance.txt";
const string FileHandler::leaveFile = "leaves.txt";

// Read employee data from employees.txt and load into Employee objects
void FileHandler::readEmployeeData(vector<Employee>& employees) {
    ifstream file(employeeFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string name;
            float totalHours;
            int casualLeaves, earnedLeaves;

            string temp;
            getline(ss, temp, '|'); id = stoi(temp);
            getline(ss, name, '|');
            getline(ss, temp, '|'); totalHours = std::stof(temp);
            getline(ss, temp, '|'); casualLeaves = std::stoi(temp);
            getline(ss, temp, '|'); earnedLeaves = std::stoi(temp);

            employees.emplace_back(id, name);
            employees.back().markAttendance("2023-11-01", totalHours);  // This is just an example; you might want to adjust how to set total hours here
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open employee data file for reading.\n";
    }
}

// Write employee data to employees.txt
void FileHandler::writeEmployeeData(const Employee& employee) {
    ofstream file(employeeFile, ios::app);
    if (file.is_open()) {
        file << employee.getId() << "|" << employee.getName() << "|"
             << employee.getTotalHoursWorked() << "|"
             << employee.getCasualLeaveBalance() << "|"
             << employee.getEarnedLeaveBalance() << "\n";
        file.close();
    } else {
        cerr << "Error: Unable to open employee data file for writing.\n";
    }
}

// Read attendance data from attendance.txt
void FileHandler::readAttendanceData(vector<AttendanceRecord>& attendanceRecords, int employeeId) {
    ifstream file(attendanceFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string date;
            float hoursWorked;

            string temp;
            getline(ss, temp, '|'); id = std::stoi(temp);
            if (id == employeeId) {
                getline(ss, date, '|');
                getline(ss, temp, '|'); hoursWorked = std::stof(temp);

                attendanceRecords.emplace_back(date, hoursWorked);
            }
        }
        file.close();
    } else {
        cerr << "Error: Unable to open attendance data file for reading.\n";
    }
}

// Write an attendance record to attendance.txt
void FileHandler::writeAttendanceData(const AttendanceRecord& record) {
    ofstream file(attendanceFile, ios::app);
    if (file.is_open()) {
        file << record.getEmployeeId() << "|" << record.getDate() << "|"
             << record.getHoursWorked() << "\n";
        file.close();
    } else {
        cerr << "Error: Unable to open attendance data file for writing.\n";
    }
}

// Read leave data from leaves.txt
void FileHandler::readLeaveData(vector<Leave*>& leaveRecords) {
    ifstream file(leaveFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string type, startDate, endDate, status, reason, supervisorApproval, directorApproval;

            string temp;
            getline(ss, temp, '|'); id = std::stoi(temp);
            getline(ss, type, '|');
            getline(ss, startDate, '|');
            getline(ss, endDate, '|');
            getline(ss, reason, '|');
            getline(ss, status, '|');
            getline(ss, supervisorApproval, '|');
            getline(ss, directorApproval, '|');

            Leave* leave = LeaveFactory::createLeave(type, startDate, endDate, reason);
            leave->setStatus(status);
            leaveRecords.push_back(leave);
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open leave data file for reading.\n";
    }
}

// Write leave data to leaves.txt
void FileHandler::writeLeaveData(const Leave& leave) {
    ofstream file(leaveFile, std::ios::app);
    if (file.is_open()) {
        file << leave.getEmployeeId() << "|" << leave.getLeaveType() << "|"
             << leave.getStartDate() << "|" << leave.getEndDate() << "|"
             << leave.getReason() << "|" << leave.getStatus() << "|"
             << leave.getSupervisorApproval() << "|" << leave.getDirectorApproval() << "\n";
        file.close();
    } else {
        cerr << "Error: Unable to open leave data file for writing.\n";
    }
}

// Update leave status (approve/reject)
void FileHandler::updateLeaveStatus(int employeeId, const std::string& leaveType, const std::string& status) {
    ifstream file(leaveFile);
    ofstream tempFile("temp.txt");
    string line;

    if (file.is_open() && tempFile.is_open()) {
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string type, startDate, endDate, reason, currentStatus, supervisorApproval, directorApproval;
            getline(ss, temp, '|'); id = std::stoi(temp);
            
            if (id == employeeId && type == leaveType) {
                currentStatus = status;
            }

            // Write the updated leave data to temp file
            tempFile << id << "|" << type << "|" << startDate << "|" << endDate << "|"
                     << reason << "|" << currentStatus << "|" << supervisorApproval << "|" << directorApproval << "\n";
        }
        file.close();
        tempFile.close();

        // Rename temp file to replace old file
        remove(leaveFile.c_str());
        rename("temp.txt", leaveFile.c_str());
    } else {
        cerr << "Error: Unable to open leave data file for reading/writing.\n";
    }
}
