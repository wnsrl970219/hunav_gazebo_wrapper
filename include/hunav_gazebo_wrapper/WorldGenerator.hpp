/***********************************************************************/
/**                                                                    */
/** WorldGenerator.hpp                                                 */
/**                                                                    */
/** Copyright (c) 2022, Service Robotics Lab (SRL).                    */
/**                     http://robotics.upo.es                         */
/**                                                                    */
/** All rights reserved.                                               */
/**                                                                    */
/** Authors:                                                           */
/** Noé Pérez-Higueras (maintainer)                                    */
/** email: noeperez@upo.es                                             */
/**                                                                    */
/** This software may be modified and distributed under the terms      */
/** of the BSD license. See the LICENSE file for details.              */
/**                                                                    */
/** http://www.opensource.org/licenses/BSD-3-Clause                    */
/**                                                                    */
/***********************************************************************/

#ifndef HUNAVPLUGIN_WORLDGENERATOR_HH_
#define HUNAVPLUGIN_WORLDGENERATOR_HH_

#include "hunav_msgs/msg/agents.hpp"
#include "rclcpp/rclcpp.hpp"
#include <functional>
#include <geometry_msgs/msg/pose.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <vector>
// XML parser
#include <tinyxml2.h>

namespace hunav {

class WorldGenerator : public rclcpp::Node {

public:
  /**
   * @brief Construct a new World Generator object
   *
   */
  WorldGenerator();
  /**
   * @brief Destroy the World Generator object
   *
   */
  ~WorldGenerator();

  /**
   * @brief read the simulation parameters from
   * the hunav_loader node
   *
   */
  void readAgentParams();

private:
  void tokenize(std::string const &str, const char delim,
                std::vector<std::string> &out) {
    // construct a stream from the string
    std::stringstream ss(str);

    std::string s;
    while (std::getline(ss, s, delim)) {
      out.push_back(s);
    }
  }

  std::vector<std::string> params_;
  std::vector<std::string> goal_params_;
  std::string base_world_;
  bool plug_use_gazebo_obs_;
  double plug_update_rate_;
  std::string plug_robot_name_;
  std::string plug_global_frame_;
  std::vector<std::string> plug_ignore_models_;
};
} // namespace hunav

#endif