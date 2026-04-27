#pragma once
#include <string>
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
};
