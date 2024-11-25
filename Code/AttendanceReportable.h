#ifndef ATTENDANCEREPORTABLE_H
#define ATTENDANCEREPORTABLE_H

// Abstract base class for attendance reporting
class AttendanceReportable {
public:
    virtual void generateAttendanceReport(float requiredPercentage) = 0;  // Pure virtual function
    virtual ~AttendanceReportable() = default;  // Virtual destructor for proper cleanup
};

#endif // ATTENDANCEREPORTABLE_H
