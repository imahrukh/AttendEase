#include "ReportGenerator.h"
#include <iostream>

ReportGenerator::ReportGenerator(const AttendanceManager& manager) : attendanceManager(manager) {}

void ReportGenerator::generateAttendanceReport(double threshold) const {
    // Logic to generate report based on attendance threshold
    // This is a placeholder for demonstration
    cout << "Generating attendance report for threshold: " << threshold << "%" << std::endl;
}