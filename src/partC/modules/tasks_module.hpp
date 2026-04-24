#include <iostream>
#include <string>
#include <my_types/queue.hpp>
#include <my_types/stack.hpp>

namespace tasks_module {

  message_manager msg("config/messages.yaml"); // getting messages from config

  my_types::queue<Task> tasks;
  my_types::stack<Task> task_completion_history;
  unsigned int task_id = 100;

  void prompt_new_task();

  void prompt_tasks() {
    bool running = true;

    while (running) {
      std::cout << msg.get("tasks_menu", "tasks_menu_message") << "\n";
      std::cout << msg.get("tasks_menu", "tasks_menu_options") << "\n";
      std::cout << msg.get("other", "choose_inner");

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
          prompt_new_task();
          break;
        case 2:
          tasks.for_each([](const Task& t) {
            std::cout << t << "\n";
          });
          std::cout << "\n";
          break;
      }
    }
  }

  void prompt_new_task() {
    bool running = true;

    while (running) {
      std::cout << "New Task's Name: "; 

      std::string input;
      std::cin >> input;
      tasks.enqueue(Task(task_id, input));
      task_id++;
      running = false;
      std::cout << "\n";
    }
  }
}
