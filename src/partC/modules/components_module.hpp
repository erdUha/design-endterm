#pragma once
#include <iostream>
#include <string>
#include <set>
#include <MessageManager.hpp>
#include <my_types/union_find.hpp>
#include <my_types/stack.hpp>
#include <TaskUndoData.hpp>

namespace components_module {

  MessageManager msg("config/messages.yaml"); // getting messages from config
  
  my_types::union_find<std::string> components;

  void prompt_new_component();
  void union_prompt();
  void check_connectivity_prompt();

  void prompt_components() {
    bool running = true;

    while (running) {
      std::cout << msg.get("components_menu", "components_menu_message") << "\n";
      std::cout << msg.get("components_menu", "components_menu_options") << "\n";
      std::cout << msg.get("other", "choose");

      int input;
      if (!(std::cin >> input)) {
        std::cout << "\nInvalid input! Please enter a number.\n\n";
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        continue;
      }
      std::cout << "\n";

      switch (input) {
        case 0:
          std::cout << "Going Back...\n";
          running = false;
          break;
        case 1:
          prompt_new_component();
          break;
        case 2:
          components.visualize();
          std::cout << "\n";
          break;
        case 3:
          union_prompt();
          break;
        case 4:
          check_connectivity_prompt();
          break;
        default:
          std::cout << msg.get("other", "not_in_list") << "\n\n";
      }
    }
  }

  void prompt_new_component() {
    std::cout << msg.get("components_menu", "new_component_prompt"); 

    std::string input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, input);
    try {
      components.add_component(input);
      std::cout << "Successfully Added Component \"" << input << "\"\n";
    } catch (const std::exception& e) {
      std::cout << "Error: " << e.what() << "\n";
    }
    std::cout << "\n";
  }

  void union_prompt() {
    std::cout << msg.get("components_menu", "union_prompt_message");
    components.visualize("for Union");

    std::string first, second;

    std::cout << msg.get("components_menu", "union_prompt_first");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, first);
    std::cout << msg.get("components_menu", "union_prompt_second");
    std::getline(std::cin, second);

    try {
      components._union(first, second);
      std::cout << "Successfully Connected Components \"" << first << "\" and \"" << second << "\"\n";
    } catch (const std::exception& e) {
      std::cout << "Error: " << e.what() << "\n";
    }
    
    std::cout << "\n";
  }

  void check_connectivity_prompt() {
    std::cout << msg.get("components_menu", "check_connectivity_prompt_message") << "\n";

    std::string first, second;

    std::cout << msg.get("components_menu", "check_connectivity_prompt_first");
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, first);
    std::cout << msg.get("components_menu", "check_connectivity_prompt_second");
    std::getline(std::cin, second);

    try {
      if (components.connected(first, second)) {
        std::cout << "Components \"" << first << "\" and \"" << second << "\" are Connected\n";
      } else {
        std::cout << "Components \"" << first << "\" and \"" << second << "\" are Not Connected\n";
      }
    } catch (const std::exception& e) {
      std::cout << "Error: " << e.what() << "\n";
    }

    std::cout << "\n";
  }
}
