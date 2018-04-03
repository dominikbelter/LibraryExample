/** @file robot.h
 *
 * Robot interface
 *
 * @author Dominik Belter
 */

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include <iostream>
#include <string>
#include <vector>

namespace tutorial {
    /// Robot interface
    class Robot{
        public:

            /// Robot type
            enum Type {
                    /// six-legged
                    TYPE_SIX_LEGGED,
                    /// wheeled
                    TYPE_WHEELED
            };

            /// overloaded constructor
            Robot(const std::string _name, Type _type, size_t _jointsNo) : name(_name), type(_type), jointsNo(_jointsNo) {
                configuration.resize(jointsNo,0.0);
            }

            /// Get name of the robot
            virtual const std::string& getName() const {return name;}

            /// Get type of the robot
            virtual const Type& getType() const {return type;}

            /// move to goal configuration
            virtual void move2conf(const std::vector<double>& goalConfiguration) = 0;

            /// Virtual descrutor
            virtual ~Robot() {}

        protected:
            /// Robot type
            Type type;

            /// Robot name
            const std::string name;

            /// Number of joints
            size_t jointsNo;

            /// Current configuration of the robot
            std::vector<double> configuration;
	};
}

#endif // _ROBOT_H_
