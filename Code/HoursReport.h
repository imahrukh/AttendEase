#ifndef HOURSREPORT_H
#define HOURSREPORT_H

#include "Reportable.h"
#include "AttendanceRecord.h"
#include <vector>
#include <iostream>


class HoursReport : public Reportable {
private:
    std::vector<AttendanceRecord> attendanceRecords;
    float requiredPercentage;

public:
    // Constructor
    HoursReport(const std::vector<AttendanceRecord>& records, float percentage)
        : attendanceRecords(records), requiredPercentage(percentage) {}

    // Generate report for employees with low hours
    void generateReport() override {
        const int totalExpectedHours = 40 * 4;  // 40 hours/week * 4 weeks
        std::cout << "Hours Report (Threshold: " << requiredPercentage << "%)\n";
        for (const auto& record : attendanceRecords) {
            float totalHours = record.getTotalHoursWorked();
            float percentage = (totalHours / totalExpectedHours) * 100;

            if (percentage < requiredPercentage) {
                std::cout << "Employee ID: " << record.getRecords().front().getHoursWorked()
                          << ", Total Hours: " << totalHours << " (" << percentage << "%)\n";
            }
        }
    }
};


#endif // HOURSREPORT_H
