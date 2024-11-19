#ifndef ATTENDANCEMANAGER_H
#define ATTENDANCEMANAGER_H

#include "Employee.h"
#include <vector>

using namespace std;

class AttendanceManager {
public:
    void addEmployee(const Employee& employee);
    void markAttendance(int employeeId, int hours);
    double getAttendancePercentage(int employeeId) const;

private:
    vector<Employee> employees;
};

#endif // ATTENDANCEMANAGER_H