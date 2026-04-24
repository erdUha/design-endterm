#include <iostream>
#include <string>
#include <sstream>
#include <set>
#include <vector>
#include <chrono>
#include <iomanip>
#include <my_types/queue.hpp>
#include <my_types/stack.hpp>
#include <my_types/union_find.hpp>
#include <message_manager.hpp>

message_manager msg("config/messages.yaml"); // getting messages from config

class Task {
public:
  unsigned int taskID;
  std::string description;
  std::chrono::system_clock::time_point timestamp;

  // constructor
  Task(unsigned int newID, std::string newDescription) :
    taskID(newID),
    description(newDescription)
  {
    timestamp = std::chrono::system_clock::now();
  }

  std::string get_formatted_time() const {
    std::time_t time_now = std::chrono::system_clock::to_time_t(timestamp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_now), "%Y-%m-%d %H:%M:%S");
    return ss.str();
  }

  friend std::ostream& operator<<(std::ostream& os, const Task& t) {
    os << "Task #" << t.taskID << "[" << t.get_formatted_time() << "]" << ": " << t.description;
    return os;
  }
};

my_types::queue<Task> tasks;
my_types::stack<Task> task_completion_history;

void prompt_main();

int main(int argc, char** argv)
{
  prompt_main(); // main menu loop
  tasks.enqueue(Task(1, "Fuck"));
  return 0;
}

void prompt_tasks();
void prompt_components();

void prompt_main() {
  bool running = true;

  while (running) {
    std::cout << msg.get("main_menu", "main_menu_message") << "\n";
    std::cout << msg.get("main_menu", "main_menu_options") << "\n";
    std::cout << "Choose (0 to Exit): ";

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
        prompt_tasks();
        break;
      case 2:
        prompt_components();
        break;
      default:
        std::cout << msg.get("other", "not_in_list") << "\n";
    }

    std::cout << "\n";
  }
}

void prompt_tasks() {
  bool running = true;

  while (running) {
    std::cout << msg.get("tasks_menu", "tasks_menu_message") << "\n";
    std::cout << msg.get("tasks_menu", "tasks_menu_options") << "\n";
    std::cout << "Choose (0 to Exit): ";

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
        0 == 0;
        break;
    }
  }
}

void prompt_components() {
  std::cout << msg.get("components_menu", "components_menu_message") << "\n";
  std::cout << msg.get("components_menu", "components_menu_options") << "\n";
}
