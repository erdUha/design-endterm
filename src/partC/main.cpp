#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <my_types/queue.hpp>
#include <my_types/stack.hpp>
#include <my_types/union_find.hpp>
#include <message_manager.hpp>

message_manager msg("config/messages.yaml"); // getting messages from config

void prompt_main();

int main(int argc, char** argv)
{
  prompt_main();
  return 0;
}

void prompt_tasks();
void prompt_components();

void prompt_main() {
  bool running = true;

  while (running) {
    std::cout << msg.get("menu_prompts", "main_menu") << "\n";
    std::cout << msg.get("menu_prompts", "main_menu_options") << "\n";
    std::cout << "Choose (0 to Exit): ";

    int input;
    if (!(std::cin >> input)) {
      std::cout << "Invalid input! Please enter a number.\n";
      std::cin.clear();
      std::cin.ignore(1000, '\n');
    }
    std::cout << "\n";

    switch (input) {
      case 0:
        std::cout << "Exiting...\n";
        running = false;
        break;
      case 1:
        prompt_tasks();
        break;
      case 2:
        prompt_components();
        break;
      default:
        std::cout << "The Option is Not in the List\n";
    }

    std::cout << "\n";
  }
}

void prompt_tasks() {
  std::cout << "--- Tasks Module ---\n";
}

void prompt_components() {
  std::cout << "--- Components Module ---\n";
}
