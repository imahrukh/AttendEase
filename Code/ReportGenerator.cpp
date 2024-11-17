#include <iostream>
#include"Employee.cpp"
#include"Leave.cpp"
#include <vector>

using namespace std;

// Abstract Base Class for Reports
class ReportGenerator {
public:
    virtual void generateReport() = 0;
    virtual ~ReportGenerator() = default;
};

class AttendanceBelowThresholdReport : public ReportGenerator {
    const vector<Employee>& employees;
    float threshold;

public:
    AttendanceBelowThresholdReport(const std::vector<Employee>& emps, float t)
        : employees(emps), threshold(t) {}

    void generateReport() override {
        cout << "Employees with attendance below " << threshold << "%:\n";
        for (const auto& emp : employees) {
            if (emp.calculateAttendancePercentage(160) < threshold) {
                emp.displayAttendance();
            }
        }
    }
};

class OutstandingLeavesReport : public ReportGenerator {
    const vector<std::shared_ptr<Leave>>& leaves;

public:
    OutstandingLeavesReport(const std::vector<std::shared_ptr<Leave>>& ls) : leaves(ls) {}

    void generateReport() override {
        cout << "Outstanding Leaves:\n";
        for (const auto& leave : leaves) {
            if (leave->getStatus() == "Pending") {
                leave->displayLeaveDetails();
            }
        }
    }
};
