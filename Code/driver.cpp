#include <iostream>

using namespace std;

int main() {
    // Create Employee
    Employee emp(1, "John Doe");
    emp.addAttendance("2023-11-01", 8.0);
    emp.addAttendance("2023-11-02", 7.5);
    emp.displayAttendance();

    // Apply for Leave
    auto leave = LeaveFactory::createLeave("Casual", "2023-11-05", "2023-11-06", "Family Emergency");
    leave->applyLeave();

    // Supervisor Approval
    SupervisorApproval supervisor;
    supervisor.approveLeave(leave);

    // Generate Reports
    AttendanceReport attendanceReport;
    attendanceReport.generateReport();

    LeaveReport leaveReport;
    leaveReport.generateReport();

    return 0;
}
