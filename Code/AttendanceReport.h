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
    void addEmployeeAttendance(const AttendanceRecord& record) ;
    // Add leave requests to the report system
    void addLeaveRequest(Leave* leave);
    // Generate attendance report for employees with less than required percentage
    void generateAttendanceReport(float requiredPercentage) override;
    // Generate leave report for employees with unapproved/unfiled leaves
    void generateUnapprovedLeaveReport() ;
};

#endif // ATTENDANCEREPORT_H
