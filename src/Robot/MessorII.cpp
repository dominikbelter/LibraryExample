#include "Robot/MessorII.h"

using namespace tutorial;


MessorII::MessorII(void) : tutorial::Robot("Messor II", tutorial::Robot::Type::SIX_LEGGED, 18){

}

/// move to goal configuration
void MessorII::move2conf(const std::vector<double>&& goalConfiguration){
    if (goalConfiguration.size()!=jointsNo)
        throw std::runtime_error("Incorrect number of joints");

    std::cout << "current configuration of the " << getName() << " robot is:\n";
    for (const auto& angle : configuration)
        std::cout << angle << ", ";
    std::cout << "\n";

    // Insert robot specific code here for motion execution
    std::cout << "Motion exectution...\n";
    configuration = std::move(goalConfiguration);
    std::cout << "Done\n";

    std::cout << "Configuration of the " << getName() << " robot after motion execution is:\n";
    for (const auto& angle : configuration)
        std::cout << angle << ", ";
    std::cout << "\n\n";
}
