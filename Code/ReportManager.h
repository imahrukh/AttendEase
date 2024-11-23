#ifndef REPORTMANAGER_H
#define REPORTMANAGER_H

#include "Reportable.h"
#include <memory>  // For unique_ptr
#include<iostream>

class ReportManager {
private:
    std::unique_ptr<Reportable> report;  // Pointer to the current report type

public:
    // Set the report type dynamically
    void setReport(std::unique_ptr<Reportable> newReport) {
        report = std::move(newReport);
    }

    // Generate the selected report
    void generateReport() {
        if (report) {
            report->generateReport();
        } else {
            std::cout << "No report type selected.\n";
        }
    }
};


#endif // REPORTMANAGER_H
