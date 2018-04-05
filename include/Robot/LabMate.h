/** @file LabMate.h
 *
 * implementation - LabMate Robot
 *
 * @author Dominik Belter
 */

#ifndef LABMATE_H
#define LABMATE_H

#include "robot.h"
#include <memory>
#include <iostream>

class LabMate : public tutorial::Robot {

public:

    /// Pointer
    using Ptr = std::unique_ptr<LabMate>;

    /// Construction
    LabMate(void);

    /// move to goal configuration
    void move2conf(const std::vector<double>&& goalConfiguration);

protected:


private:


};


#endif // LABMATE_H
