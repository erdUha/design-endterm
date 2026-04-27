#pragma once
#include <iostream>
#include <string>
#include <limits>
#include <MessageManager.hpp>
#include <my_types/queue.hpp>
#include <my_types/stack.hpp>
#include <Task.hpp> // Task class

namespace tasks_module {

  MessageManager msg("config/messages.yaml"); // getting messages from config

  my_types::queue<Task> tasks;
  my_types::stack<Task> task_completion_history;
  unsigned int task_id = 100;

  void complete_task();
  void prompt_new_task();

  void prompt_tasks() {
    bool running = true;

    while (running) {
      std::cout << msg.get("tasks_menu", "tasks_menu_message") << "\n";
      std::cout << msg.get("tasks_menu", "tasks_menu_options") << "\n";
      std::cout << msg.get("other", "choose");

      int input;
      if (!(std::cin >> input)) {
        std::cout << "\nInvalid input! Please enter a number.\n\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
        case 3:
          complete_task();
          break;
      }
    }
  }

  void complete_task() {
    if (tasks.is_empty()) {
      std::cout << "There Are No Tasks\n\n";
      return;
    }
    Task pending = tasks.dequeue();
    std::cout << pending << "\nCompleting...\n";
    if (pending.task_type == 1)
    {
      try {
        components_module::components.add_component(pending.component1);
      } catch (const std::exception& e) {
        std::cout << "Error While Adding a New Component: " << e.what() << "\n";
      }
    }
    if (pending.task_type == 2)
    {
      try {
        components_module::components._union(pending.component1, pending.component2);
      } catch (const std::exception& e) {
        std::cout << "Error While Union: " << e.what() << "\n";
      }
    }
    std::cout << "\n";
  }

  void new_task_add_component();
  void new_task_connect();

  void prompt_new_task() {
    bool running = true;

    while (running) {
      std::cout << msg.get("tasks_menu", "new_task_message") << "\n"; 
      std::cout << msg.get("tasks_menu", "new_task_options") << "\n"; 
      std::cout << msg.get("other", "choose");

      int input;
      if (!(std::cin >> input)) {
        std::cout << "\nInvalid input! Please enter a number.\n\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        continue;
      }
      std::cout << "\n";

      switch (input) {
        case 0:
          std::cout << "Going Back...\n";
          break;
        case 1:
          new_task_add_component();
          break;
        case 2:
          new_task_connect();
          break;
      }

      std::cout << "\n";
      running = false;
    }
  }

  void new_task_add_component() {
    std::string desc, new_component_id;
    std::cout << msg.get("tasks_menu", "new_task_description_prompt"); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, desc);
    std::cout << msg.get("tasks_menu", "new_task_new_component_prompt"); 
    std::getline(std::cin, new_component_id);
    tasks.enqueue(Task(task_id, new_component_id, desc));
    task_id++;
  }

  void new_task_connect() {
    std::string desc, first, second;
    std::cout << msg.get("tasks_menu", "new_task_description_prompt"); 
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, desc);
    std::cout << msg.get("tasks_menu", "new_task_connect_first_component_prompt"); 
    std::getline(std::cin, first);
    std::cout << msg.get("tasks_menu", "new_task_connect_second_component_prompt"); 
    std::getline(std::cin, second);
    tasks.enqueue(Task(task_id, first, second, desc));
    task_id++;
    std::cout << "\n";
  }
}
