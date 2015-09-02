// Copyright 2015 Open Source Robotics Foundation, Inc.
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

#include <rclcpp/rclcpp.hpp>

#include "camera_node.hpp"
#include "image_view_node.hpp"
#include "watermark_node.hpp"

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::executors::SingleThreadedExecutor executor;

  // Connect the nodes as a pipeline: camera_node -> watermark_node -> image_view_node
  // And the extra image view as a fork:                           \-> image_view_node2
  auto camera_node = std::make_shared<CameraNode>("image");
  auto watermark_node =
    std::make_shared<WatermarkNode>("image", "watermarked_image", "Hello world!");
  auto image_view_node = std::make_shared<ImageViewNode>("watermarked_image");
  auto image_view_node2 = std::make_shared<ImageViewNode>("watermarked_image", "image_view_node2");

  executor.add_node(camera_node);
  executor.add_node(watermark_node);
  executor.add_node(image_view_node);
  executor.add_node(image_view_node2);

  executor.spin();
  return 0;
}
