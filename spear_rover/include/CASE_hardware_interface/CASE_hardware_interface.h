// Defines available variables and class members
//

#ifndef ROS_CONTROL__CASE_HARDWARE_INTERFACE_H
#define ROS_CONTROL__CASE_HARDWARE_INTERFACE_H
#include <hardware_interface/joint_state_interface.h>
#include <hardware_interface/joint_command_interface.h>
#include <hardware_interface/robot_hw.h>
#include <joint_limits_interface/joint_limits_interface.h>
#include <joint_limits_interface/joint_limits.h>
#include <joint_limits_interface/joint_limits_urdf.h>
#include <joint_limits_interface/joint_limits_rosparam.h>
#include <controller_manager/controller_manager.h>
#include <boost/scoped_ptr.hpp>
#include <ros/ros.h>
#include <CASE_hardware_interface/CASE_hardware.h>

using namespace hardware_interface;
using joint_limits_interface::JointLimits;
using joint_limits_interface::SoftJointLimits;
using joint_limits_interface::VelocityJointSoftLimitsHandle;
using joint_limits_interface::VelocityJointSoftLimitsInterface;


namespace CASE_hardware_interface
{
    static const double POSITION_STEP_FACTOR = 10;
    static const double VELOCITY_STEP_FACTOR = 10;

    class CASEHardwareInterface: public CASE_hardware_interface::CASEHardware
    {
        public:
            CASEHardwareInterface(ros::NodeHandle& nh);
            ~CASEHardwareInterface();
            void init();
            void update(const ros::TimerEvent& e);
            void read();
            void write(ros::Duration elapsed_time);

        protected:
            ros::NodeHandle nh_;
            ros::Timer non_realtime_loop_;
            ros::Duration control_period_;
            ros::Duration elapsed_time_;
            VelocityJointInterface velocityJointInterface;
            VelocityJointSoftLimitsInterface velocityJointSoftLimitsInterface;
            double loop_hz_;
            boost::shared_ptr<controller_manager::ControllerManager> controller_manager_;
            double p_error_, v_error_, e_error_;
    };

}

#endif