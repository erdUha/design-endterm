#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <Task.hpp>
#include <message_manager.hpp>
#include "modules/tasks_module.hpp"
#include "modules/components_module.hpp"

message_manager msg("config/messages.yaml"); // getting messages from config

void prompt_main();

int main(int argc, char** argv)
{
  prompt_main(); // main menu loop
  return 0;
}

void prompt_main() {
  bool running = true;

  while (running) {
    std::cout << msg.get("main_menu", "main_menu_message") << "\n";
    std::cout << msg.get("main_menu", "main_menu_options") << "\n";
    std::cout << msg.get("other", "choose_main");

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
        std::cout << "Exiting...\n";
        running = false;
        break;
      case 1:
        tasks_module::prompt_tasks();
        break;
      case 2:
        components_module::prompt_components();
        break;
      default:
        std::cout << msg.get("other", "not_in_list") << "\n";
    }

    std::cout << "\n";
  }
}
