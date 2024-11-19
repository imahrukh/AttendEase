#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <string>
#include <vector>
#include <ctime>

using namespace std;

class Employee {
public:
    Employee(int id, const string& name);
    virtual ~Employee() {}

    int getId() const;
    string getName() const;

    // Attendance-related methods
    void markAttendance(const tm& date);
    const vector<tm>& getAttendanceRecords() const;

    // Other employee functionalities can be added here

protected:
    int id;
    string name;
    vector<tm> attendanceRecords; // Stores attendance records
};

#endif // EMPLOYEE_H