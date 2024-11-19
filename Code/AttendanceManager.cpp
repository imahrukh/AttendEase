#include "AttendanceManager.h"

void AttendanceManager::addEmployee(const Employee& employee) {
    employees.push_back(employee);
}

void AttendanceManager::markAttendance(int employeeId, int hours) {
    for (auto& employee : employees) {
        if (employee.getId() == employeeId) {
            employee.addAttendance(hours);
            break;
        }
    }
}

double AttendanceManager::getAttendancePercentage(int employeeId) const {
    for (const auto& employee : employees) {
        if (employee.getId() == employeeId) {
            return employee.getAttendancePercentage(40); // Assuming 40 hours in a week
        }
    }
    return 0.0;
}