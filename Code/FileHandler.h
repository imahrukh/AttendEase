#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include "Employee.h"
#include "Leave.h"

using namespace std;
// Class to handle file reading and writing
class FileHandler {
public:
    static void readEmployeeData(vector<Employee>& employees);
    static void writeEmployeeData(const Employee& employee);
    static void readAttendanceData(vector<AttendanceRecord>& attendanceRecords, int employeeId);
    static void writeAttendanceData(const AttendanceRecord& record);
    static void readLeaveData(vector<Leave*>& leaveRecords);
    static void writeLeaveData(const Leave& leave);
    static void updateLeaveStatus(int employeeId, const string& leaveType, const string& status);

private:
    static const string employeeFile;
    static const string attendanceFile;
    static const string leaveFile;
};

#endif // FILEHANDLER_H
