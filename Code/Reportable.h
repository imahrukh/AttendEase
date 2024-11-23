#ifndef REPORTABLE_H
#define REPORTABLE_H

#include <string>


class Reportable {
public:
    virtual void generateReport() = 0;  // Pure virtual function for generating a report
    virtual ~Reportable() = default;   // Virtual destructor for proper cleanup
};


#endif // REPORTABLE_H
