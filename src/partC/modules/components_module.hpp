#include <iostream>
#include <string>
#include <my_types/union_find.hpp>

namespace components_module {

  message_manager msg("config/messages.yaml"); // getting messages from config

  void prompt_components() {
    std::cout << msg.get("components_menu", "components_menu_message") << "\n";
    std::cout << msg.get("components_menu", "components_menu_options") << "\n";
  }

}
