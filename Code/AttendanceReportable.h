#ifndef ATTENDANCEREPORTABLE_H
#define ATTENDANCEREPORTABLE_H

class AttendanceReportable {
public:
    virtual void generateAttendanceReport(float requiredPercentage) = 0;
    virtual ~AttendanceReportable() = default;
};


#endif // ATTENDANCEREPORTABLE_H
