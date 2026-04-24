#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <my_types/queue.hpp>
#include <my_types/stack.hpp>
#include <my_types/union_find.hpp>
#include <yaml-cpp/yaml.h>

class MessageManager {
private:
  YAML::Node config;

public:
  MessageManager(const std::string& filename) {
    try {
      config = YAML::LoadFile(filename);
    } catch (const YAML::Exception& e) {
      std::cerr << "Could not load messages: " << e.what() << std::endl;
    }
  }

  std::string get(const std::string& category, const std::string& key) {
    if (config[category] && config[category][key]) {
      return config[category][key].as<std::string>();
    }
    return "Missing string: " + category + "." + key;
  }
} msg("config/messages.yaml");

void promptMain();

int main(int argc, char** argv)
{
  promptMain();
  return 0;
}

void promptMain() {
  std::cout << msg.get("menu_prompts", "main_menu") << "\n";
  std::cout << msg.get("menu_prompts", "main_menu_options") << "\n";
  std::cout << "Choose: ";
  std::string input;
  std::cin >> input;
  std::cout << "You chose: " << input << "\n";
  //promptMain();
}
