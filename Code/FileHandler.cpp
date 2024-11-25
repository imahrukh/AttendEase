#include "FileHandler.h"
#include "LeaveFactory.h"
#include "Employee.h"
#include"Supervisor.h"
#include"Director.h"
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

void FileHandler::readEmployeeData(std::vector<std::shared_ptr<Employee>>& employees) {
    std::ifstream file(employeeFile);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int id;
            std::string name, role;
            float totalHours;
            int casualLeaves, earnedLeaves;

            std::string temp;
            std::getline(ss, temp, '|'); id = std::stoi(temp);
            std::getline(ss, name, '|');
            std::getline(ss, temp, '|'); totalHours = std::stof(temp);
            std::getline(ss, temp, '|'); casualLeaves = std::stoi(temp);
            std::getline(ss, temp, '|'); earnedLeaves = std::stoi(temp);
            std::getline(ss, role, '|');

            std::shared_ptr<Employee> emp;
            if (role == "Supervisor") {
                emp = std::make_shared<Supervisor>(id, name);
            } else if (role == "Director") {
                emp = std::make_shared<Director>(id, name);
            } else {
                emp = std::make_shared<Employee>(id, name);  // default Employee class
            }

            emp->setTotalHoursWorked(totalHours);
            emp->setCasualLeaveBalance(casualLeaves);
            emp->setEarnedLeaveBalance(earnedLeaves);
            employees.push_back(emp);
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open employee data file for reading.\n";
    }
}


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
        for (const auto& attendance : record.getRecords()) {
            file << record.getEmployeeId() << "|" << attendance.getDate() << "|" << attendance.getHoursWorked() << "\n";
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open attendance file for writing.\n";
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

// Read leave data from leaves.txt
void FileHandler::readLeaveData(std::vector<std::shared_ptr<Leave>>& leaveRecords) {
    std::ifstream file(leaveFile);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int id;
            int empId;
            std::string type, startDate, endDate, reason, status, supervisorApproval, directorApproval;

            // Declare 'temp' to temporarily store each field
            std::string temp;

            // Read the data for each field
            std::getline(ss, temp, '|'); id = std::stoi(temp);  // Read ID and convert to integer
            std::getline(ss, temp, '|'); empId = std::stoi(temp);  // Read employee ID and convert to integer
            std::getline(ss, type, '|');  // Read leave type
            std::getline(ss, startDate, '|');  // Read start date
            std::getline(ss, endDate, '|');  // Read end date
            std::getline(ss, reason, '|');  // Read reason
            std::getline(ss, status, '|');  // Read status
            std::getline(ss, supervisorApproval, '|');  // Read supervisor approval status
            std::getline(ss, directorApproval, '|');  // Read director approval status

            // Create the appropriate leave object using the LeaveFactory
            std::shared_ptr<Leave> leave = LeaveFactory::createLeave(type, empId, startDate, endDate, reason);
            leave->setStatus(status);  // Set the status
            leave->setSupervisorApproval(supervisorApproval);  // Set supervisor approval
            leave->setDirectorApproval(directorApproval);  // Set director approval

            leaveRecords.push_back(leave);  // Add the leave object to the records vector
        }
        file.close();
    } else {
        std::cerr << "Error: Unable to open leave data file for reading.\n";
    }
}


// Write leave data to leaves.txt
void FileHandler::writeLeaveData(const Leave& leave) {
    std::ofstream file(leaveFile, std::ios::app);
    if (file.is_open()) {
        file << leave.getEmployeeId() << "|" << leave.getLeaveType() << "|"
             << leave.getStartDate() << "|" << leave.getEndDate() << "|"
             << leave.getReason() << "|" << leave.getStatus() << "\n";
        file.close();
    } else {
        std::cerr << "Error: Unable to open leave file for writing.\n";
    }
}


// Update leave status (approve/reject)
void FileHandler::updateLeaveStatus(int leaveId, const std::string& newStatus) {
    std::ifstream file(leaveFile);
    std::ofstream tempFile("temp.txt");
    std::string line;

    if (file.is_open() && tempFile.is_open()) {
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            int id;
            std::string type, startDate, endDate, reason, status, supervisorApproval, directorApproval;

            std::string temp;
            std::getline(ss, temp, '|'); id = std::stoi(temp);  // Read ID and convert to integer
            std::getline(ss, type, '|');  // Read leave type
            std::getline(ss, startDate, '|');  // Read start date
            std::getline(ss, endDate, '|');  // Read end date
            std::getline(ss, reason, '|');  // Read reason
            std::getline(ss, status, '|');  // Read status
            std::getline(ss, supervisorApproval, '|');  // Read supervisor approval
            std::getline(ss, directorApproval, '|');  // Read director approval

            // Update the status if the leave matches the provided leaveId
            if (id == leaveId) {
                status = newStatus;  // Update the status
            }

            // Write the updated data back to the temporary file
            tempFile << id << "|" << type << "|" << startDate << "|" << endDate << "|" << reason << "|" 
                     << status << "|" << supervisorApproval << "|" << directorApproval << "\n";
        }
        file.close();
        tempFile.close();

        // Rename the temporary file to replace the old file
        remove(leaveFile.c_str());
        rename("temp.txt", leaveFile.c_str());
    } else {
        std::cerr << "Error: Unable to open leave data file for updating.\n";
    }
}
