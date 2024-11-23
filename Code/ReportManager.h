#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include "Reportable.h"
#include <memory>  // For unique_ptr
#include <vector>
#include<iostream>

class ReportManager {
private:
    std::vector<std::unique_ptr<Reportable>> reports;  // To store multiple report types

public:
    // Set the report type dynamically (this is now flexible for multiple reports)
    void addReport(std::unique_ptr<Reportable> newReport) {
        reports.push_back(std::move(newReport));
    }

    // Generate all selected reports
    void generateReports() {
        if (!reports.empty()) {
            for (auto& report : reports) {
                report->generateReport();
            }
        } else {
            std::cout << "No report type selected.\n";
        }
    }
};

#endif // REPORTMANAGER_H
