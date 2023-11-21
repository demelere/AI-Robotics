#include <iostream>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class BasicMotionNode : public rclcpp::Node {
public:
    BasicMotionNode() : Node("basic_motion") {
        publisher_ = this->create_publisher<std_msgs::msg::String>("robot_commands", 10);
    }

    void publishCommand(const std::string &command) {
        std_msgs::msg::String msg;
        msg.data = command;
        publisher_->publish(msg);
    }

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<BasicMotionNode>();

    std::string command;
    std::cout << "Enter robot commands (forward, backward, left, right, stop). Type 'exit' to quit.\n";

    while (rclcpp::ok()) {
        std::cout << "> ";
        std::getline(std::cin, command);

        if (command == "exit") {
            break;
        }

        node->publishCommand(command);
    }

    rclcpp::shutdown();
    return 0;
}
