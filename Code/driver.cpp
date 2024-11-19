#include "AttendanceManager.h"
#include "ReportGenerator.h"
#include "LeaveFactory.h"
#include "LeaveRequest.h"
#include <iostream>
#include <ctime>

int main() {
    AttendanceManager attendanceManager;
    attendanceManager.addEmployee(Employee(1, "Alice"));
    attendanceManager.addEmployee(Employee(2, "Bob"));

    attendanceManager.markAttendance(1, 40);
    attendanceManager.markAttendance(2, 30);

    ReportGenerator reportGenerator(attendanceManager);
    reportGenerator.generateAttendanceReport(80.0);

    // Example of creating a leave request
    std::tm from = {};
    std::tm to = {};
    Leave* leave = LeaveFactory::createLeave("Casual");
    LeaveRequest leaveRequest(1, leave, from, to, "Sick");
    
    if (leaveRequest.isPending()) {
        leaveRequest.approve();
        std::cout << "Leave approved for employee ID: " << 1 << std::endl;
    }

    delete leave; // Clean up dynamically allocated memory
    return 0;
}