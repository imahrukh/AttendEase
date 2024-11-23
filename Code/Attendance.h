#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include<iostream>
#include <string>

class Attendance {
    private:
        std::string date;  // Format: YYYY-MM-DD
        float hoursWorked;

    public:
        // Constructor
        Attendance(const std::string& date, float hours) : date(date), hoursWorked(hours) {}

        // Getters
        const std::string& getDate() const { return date; }
        float getHoursWorked() const { return hoursWorked; }

        // Setters
        void setHoursWorked(float hours) { hoursWorked = hours; }

        // Display attendance details
        void displayAttendance() const {
            std::cout << "Date: " << date << ", Hours Worked: " << hoursWorked << " hours\n";
        }
    };


#endif // ATTENDANCE_H
