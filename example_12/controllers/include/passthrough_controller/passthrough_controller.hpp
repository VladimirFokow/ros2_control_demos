// Copyright (c) 2023, PAL Robotics
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef PASSTHROUGH_CONTROLLER__PASSTHROUGH_CONTROLLER_HPP_
#define PASSTHROUGH_CONTROLLER__PASSTHROUGH_CONTROLLER_HPP_

// system
#include <limits>
#include <memory>
#include <string>
#include <vector>

#include "controller_interface/chainable_controller_interface.hpp"
#include "realtime_tools/realtime_buffer.h"
#include "std_msgs/msg/float64_multi_array.hpp"
// auto-generated by generate_parameter_library
#include "passthrough_controller_parameters.hpp"

#include "passthrough_controller/visibility_control.h"

/**
 * PassthroughController is a simple chainable controller that exposes reference interfaces equal to
 * the number of it's command interfaces. This controller simply forwards the information commanded
 * to it's reference interface to it's own command interfaces without any modifications.
 */
namespace passthrough_controller
{
using DataType = std_msgs::msg::Float64MultiArray;
class PassthroughController : public controller_interface::ChainableControllerInterface
{
public:
  PASSTHROUGH_CONTROLLER_PUBLIC
  controller_interface::CallbackReturn on_init() override;

  PASSTHROUGH_CONTROLLER_PUBLIC
  controller_interface::InterfaceConfiguration command_interface_configuration() const override;

  PASSTHROUGH_CONTROLLER_PUBLIC
  controller_interface::InterfaceConfiguration state_interface_configuration() const override;

  PASSTHROUGH_CONTROLLER_PUBLIC
  controller_interface::CallbackReturn on_configure(
    const rclcpp_lifecycle::State & previous_state) override;

  PASSTHROUGH_CONTROLLER_PUBLIC
  controller_interface::CallbackReturn on_activate(
    const rclcpp_lifecycle::State & previous_state) override;

  PASSTHROUGH_CONTROLLER_PUBLIC
  controller_interface::CallbackReturn on_deactivate(
    const rclcpp_lifecycle::State & previous_state) override;

  PASSTHROUGH_CONTROLLER_PUBLIC
  bool on_set_chained_mode(bool chained_mode) override;

  PASSTHROUGH_CONTROLLER_PUBLIC
  controller_interface::return_type update_and_write_commands(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

protected:
  std::vector<hardware_interface::CommandInterface> on_export_reference_interfaces() override;

  controller_interface::return_type update_reference_from_subscribers(
    const rclcpp::Time & time, const rclcpp::Duration & period) override;

  std::shared_ptr<ParamListener> param_listener_;
  Params params_;

  realtime_tools::RealtimeBuffer<std::shared_ptr<DataType>> rt_buffer_ptr_;
  rclcpp::Subscription<DataType>::SharedPtr joints_cmd_sub_;

  std::vector<std::string> reference_interface_names_;

  std::vector<std::string> command_interface_names_;
};
}  // namespace passthrough_controller

#endif  // PASSTHROUGH_CONTROLLER__PASSTHROUGH_CONTROLLER_HPP_
