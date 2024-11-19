#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include "AttendanceManager.h"

using namespace std;

class ReportGenerator {
public:
    ReportGenerator(const AttendanceManager& manager);
    void generateAttendanceReport(double threshold) const;

private:
    const AttendanceManager& attendanceManager;
};

#endif // REPORTGENERATOR_H