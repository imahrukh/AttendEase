#ifndef ATTENDANCEREPORT_H
#define ATTENDANCEREPORT_H

#include "AttendanceRecord.h"
#include "AttendanceReportable.h"
#include <vector>
#include <iostream>


class AttendanceReport : public AttendanceReportable {
private:
    std::vector<AttendanceRecord> records;  // List of attendance records

public:
    // Add an attendance record to the report system
    void addEmployeeAttendance(const AttendanceRecord& record) {
        records.push_back(record);
    }

    // Generate attendance report
    void generateAttendanceReport(float requiredPercentage) override {
        std::cout << "Attendance Report (Threshold: " << requiredPercentage << "%)\n";
        for (const auto& record : records) {
            float percentage = record.calculateAttendancePercentage(40 * 4);  // Assuming 40 hours per week for 4 weeks
            if (percentage < requiredPercentage) {
                std::cout << "Employee ID: " << record.getRecords().front().getHoursWorked()
                          << ", Attendance: " << percentage << "%\n";
            }
        }
    }
};

#endif // ATTENDANCEREPORT_H