#include <iostream>

using namespace std;

// Abstract Base Class for Reports
class ReportGenerator {
public:
    virtual void generateReport() = 0;
    virtual ~ReportGenerator() = default;
};

class AttendanceReport : public ReportGenerator {
public:
    void generateReport() override {
        std::cout << "Generating Attendance Report...\n";
    }
};

class LeaveReport : public ReportGenerator {
public:
    void generateReport() override {
        std::cout << "Generating Leave Report...\n";
    }
};
