#include "Robot/LabMate.h"

using namespace tutorial;


LabMate::LabMate(void) : tutorial::Robot("LabMate", tutorial::Robot::TYPE_WHEELED, 2){

}

/// move to goal configuration
void LabMate::move2conf(const std::vector<double>& goalConfiguration){
    if (goalConfiguration.size()!=jointsNo)
        throw std::runtime_error("Incorrect number of joints");

    std::cout << "current configuration of the " << getName() << " robot is:\n";
    for (const auto& angle : configuration)
        std::cout << angle << ", ";
    std::cout << "\n";

    std::cout << "Motion exectution...\n";
    configuration = goalConfiguration;
    std::cout << "Done\n";

    std::cout << "Configuration of the " << getName() << " robot after motion execution is:\n";
    for (const auto& angle : configuration)
        std::cout << angle << ", ";
    std::cout << "\n";
}

