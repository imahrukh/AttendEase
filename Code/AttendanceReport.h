#ifndef ATTENDANCEREPORT_H
#define ATTENDANCEREPORT_H

#include "AttendanceRecord.h"
#include "AttendanceReportable.h"
#include "Leave.h"
#include <vector>
#include <iostream>

class AttendanceReport : public AttendanceReportable {
private:
    std::vector<AttendanceRecord> records;  // List of attendance records
    std::vector<Leave*> leaveRequests;      // List of leave requests

public:
    // Add an attendance record to the report system
    void addEmployeeAttendance(const AttendanceRecord& record) {
        records.push_back(record);
    }

    // Add leave requests to the report system
    void addLeaveRequest(Leave* leave) {
        leaveRequests.push_back(leave);
    }

    // Generate attendance report for employees with less than required percentage
    void generateAttendanceReport(float requiredPercentage) override {
        const int totalExpectedHours = 40 * 4;  // Assuming 40 hours/week * 4 weeks
        std::cout << "Low Attendance Report (Threshold: " << requiredPercentage << "%)\n";
        for (const auto& record : records) {
            float totalHours = record.getTotalHoursWorked();
            float percentage = (totalHours / totalExpectedHours) * 100;

            if (percentage < requiredPercentage) {
                std::cout << "Employee ID: " << record.getRecords().front().getHoursWorked()
                          << ", Total Hours: " << totalHours << " (" << percentage << "%)\n";
            }
        }
    }

    // Generate leave report for employees with unapproved/unfiled leaves
    void generateUnapprovedLeaveReport() {
        std::cout << "Unapproved Leave Report\n";
        for (const auto& leave : leaveRequests) {
            if (leave->getStatus() == "Pending" || leave->getStatus().empty()) {
                std::cout << "Employee ID: " << leave->getEmployeeId()
                          << ", Leave Type: " << leave->getLeaveType()
                          << ", Status: " << leave->getStatus()
                          << ", Reason: " << leave->getReason() << "\n";
            }
        }
    }
};

#endif // ATTENDANCEREPORT_H
