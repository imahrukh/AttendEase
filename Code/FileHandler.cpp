#include "FileHandler.h"
#include "LeaveFactory.h"
#include "Employee.h"
#include "AttendanceRecord.h"
#include "Leave.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <memory>


// Define file names
const std::string FileHandler::employeeFile = "Employees.txt";
const std::string FileHandler::attendanceFile = "Attendance.txt";
const std::string FileHandler::leaveFile = "Leaves.txt";

/*
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

            // Create Employee object and set the data
            Employee emp(id, name);
            emp.setTotalHoursWorked(totalHours);
            emp.setCasualLeaveBalance(casualLeaves);
            emp.setEarnedLeaveBalance(earnedLeaves);
            
            employees.push_back(emp);
        }
        file.close();
    } else {
        cerr << "Error: Unable to open employee data file for reading.\n";
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
*/
// Read attendance data from attendance.txt and load into AttendanceRecord objects
void FileHandler::readAttendanceData(std::vector<AttendanceRecord>& attendanceRecords, int employeeId) {
    std::ifstream file(attendanceFile);
    if (file.is_open()) {
        std::string line;
        while (getline(file, line)) {
            std::stringstream ss(line);
            int empId;
            std::string date;
            float hoursWorked;

            std::string temp;
            getline(ss, temp, '|'); empId = std::stoi(temp);  // Get Employee ID
            if (empId == employeeId) {  // Check if the employee ID matches
                getline(ss, date, '|');
                getline(ss, temp, '|'); hoursWorked = std::stof(temp);

                // Find the corresponding AttendanceRecord for the employeeId
                bool employeeFound = false;
                for (auto& record : attendanceRecords) {
                    if (record.getEmployeeId() == employeeId) {
                        record.addAttendance(date, hoursWorked);  // Add attendance record
                        employeeFound = true;
                        break;
                    }
                }

                // If employee not found, create a new record for the employee
                if (!employeeFound) {
                    AttendanceRecord newRecord(employeeId);
                    newRecord.addAttendance(date, hoursWorked);
                    attendanceRecords.push_back(newRecord);
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open attendance data file for reading.\n";
    }
}

// Write an attendance record to attendance.txt
void FileHandler::writeAttendanceData(const AttendanceRecord& record) {
    std::ofstream file(attendanceFile, std::ios::app);
    if (file.is_open()) {
        // Write each attendance record for the employee
        for (const auto& attendance : record.getRecords()) {
            file << record.getEmployeeId() << "|" << attendance.getDate() << "|"
                 << attendance.getHoursWorked() << "\n";
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open attendance data file for writing.\n";
    }
}

// Update attendance data (for a specific employee's attendance)
void FileHandler::updateAttendanceData(int employeeId, const AttendanceRecord& record) {
    std::ifstream file(attendanceFile);
    std::ofstream tempFile("temp.txt");
    std::string line;

    if (file.is_open() && tempFile.is_open()) {
        while (getline(file, line)) {
            std::stringstream ss(line);
            int empId;
            std::string date;
            float hoursWorked;

            std::string temp;
            getline(ss, temp, '|'); empId = std::stoi(temp);
            getline(ss, date, '|');
            getline(ss, temp, '|'); hoursWorked = std::stof(temp);

            // If the employee ID matches and we are updating their attendance, modify the record
            if (empId == employeeId) {
                for (const auto& attendance : record.getRecords()) {
                    if (attendance.getDate() == date) {
                        hoursWorked = attendance.getHoursWorked();  // Update the hours worked
                    }
                }
            }

            // Write the updated or unchanged attendance record to the temp file
            tempFile << empId << "|" << date << "|" << hoursWorked << "\n";
        }
        file.close();
        tempFile.close();

        // Replace the original file with the updated file
        remove(attendanceFile.c_str());
        rename("temp.txt", attendanceFile.c_str());
    } else {
        std::cerr << "Error: Unable to open attendance data file for reading or writing.\n";
    }
}

/*
// Read leave data from leaves.txt and create Leave objects using LeaveFactory
void FileHandler::readLeaveData(vector<Leave*>& leaveRecords) {
    ifstream file(leaveFile);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            int id;
            string type, startDate, endDate, reason, status, supervisorApproval, directorApproval;

            string temp;
            getline(ss, temp, '|'); id = std::stoi(temp);
            getline(ss, type, '|');
            getline(ss, startDate, '|');
            getline(ss, endDate, '|');
            getline(ss, reason, '|');
            getline(ss, status, '|');
            getline(ss, supervisorApproval, '|');
            getline(ss, directorApproval, '|');

            // Create leave object using LeaveFactory based on the leave type
            Leave* leave = LeaveFactory::createLeave(type, id, startDate, endDate, reason);
            leave->setStatus(status);
            leave->setSupervisorApproval(supervisorApproval);
            leave->setDirectorApproval(directorApproval);

            leaveRecords.push_back(leave);
        }
        file.close();
    } else {
        cerr << "Error: Unable to open leave data file for reading.\n";
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
                currentStatus = status;  // Update status to the provided status
            } else {
                currentStatus = leaveType; // leave the status unchanged
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
*/

