



// Generate attendance report
void Employee::generateAttendanceReport() {
    std::cout << "Attendance Report for Employee: " << name << "\n";
    for (const auto& record : attendanceRecords) {
        std::cout << "Date: " << record.getDate() << ", Hours Worked: " << record.getHoursWorked() << "\n";
    }
}


//requestLeave method to request leave
void Employee::requestLeave(const std::string& leaveType, const std::string& startDate, const std::string& endDate, const std::string& reason) {
    int leaveDays = std::stoi(endDate.substr(8, 2)) - std::stoi(startDate.substr(8, 2)) + 1;

    // Check leave balance
    if (!hasSufficientLeave(leaveType, leaveDays)) {
        std::cout << "Insufficient leave balance for " << leaveType << ". Request denied.\n";
        return;
    }

    // Create leave using LeaveFactory
    std::shared_ptr<Leave> newLeave = LeaveFactory::createLeave(leaveType, employeeId, startDate, endDate, reason);

    if (newLeave) {
        leaveHistory.push_back(newLeave);  // Add to leave history

        // Save the leave to the file using FileHandler
        FileHandler::writeLeaveData(*newLeave);
        std::cout << leaveType << " leave request submitted successfully.\n";
    } else {
        std::cout << "Invalid leave type provided.\n";
    }
}


void Employee::checkLeaveStatus(int leaveId) {
    // Loop through leave history and check for the leave ID
    for (auto& leave : leaveHistory) {
        if (leave->getLeaveId() == leaveId) {
            std::cout << "Leave Status for Employee " << getName() << " (Leave ID: " << leaveId << "): "
                      << leave->getStatus() << "\n";
            return;
        }
    }
    std::cout << "Leave not found for Employee " << getName() << " (Leave ID: " << leaveId << ").\n";
}


// Add attendance record
void Employee::addAttendanceRecord(const AttendanceRecord& record) {
    attendanceRecords.push_back(record);
    totalHoursWorked += record.getTotalHoursWorked();
}


// Method to check if the employee has sufficient leave balance
bool Employee::hasSufficientLeave(const std::string& leaveType, int days) {
    if (leaveType == "Casual" && casualLeaveBalance >= days) {
        return true;
    } else if (leaveType == "Earned" && earnedLeaveBalance >= days) {
        return true;
    }
    return false;
}

// Method to update leave balance after leave approval
void Employee::updateLeaveBalance(const std::string& leaveType, int days) {
    if (leaveType == "Casual") {
        casualLeaveBalance -= days;
    } else if (leaveType == "Earned") {
        earnedLeaveBalance -= days;
    }
}

// Virtual method to notify employee when leave status changes (To be implemented in Supervisor/Director)
void Employee::notifyLeaveApproval(const std::string& status) {
    std::cout << "Employee " << name << " has been notified of leave status: " << status << "\n";
}

// Check leave requests (To be implemented in Supervisor/Director)
void Employee::checkLeaveRequests(std::vector<std::shared_ptr<Leave>>& leaveRequests) {
    std::cout << "Employee checking leave requests...\n";
    // Logic for the Employee to check leave requests
}

