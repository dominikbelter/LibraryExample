/** @file MessorII.h
 *
 * implementation - Messor II Robot
 *
 * @author Dominik Belter
 */
#ifndef MESSORII_H
#define MESSORII_H

#include "robot.h"
#include <memory>
#include <iostream>

class MessorII : public tutorial::Robot {

public:

    /// Pointer
    using Ptr = std::unique_ptr<MessorII>;

    /// Construction
    MessorII(void);

    /// move to goal configuration
    void move2conf(const std::vector<double>&& goalConfiguration);

protected:


private:


};


#endif // MESSORII_H
