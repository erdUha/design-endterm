#include <iostream>
#include <string>
#include "my_types/queue.hpp"
#include "my_types/stack.hpp"

class Task {
public:
  unsigned int taskID;
  std::string description;

  // constructor
  Task(unsigned int newID, std::string newDescription) :
    taskID(newID),
    description(newDescription)
  {}
};

int main(int argc, char** argv)
{
  my_types::queue<Task> tasks; // creating a new queue for tasks
  my_types::stack<Task> task_actions;
  for (size_t i = 0; i < 3; i++)
  {
    tasks.enqueue(Task(i, "Hello, World!"));
  }

  std::cout << "Processing Tasks:\n";
  while (!tasks.isEmpty())
  {
    Task processed_task = tasks.dequeue();
    task_actions.push(processed_task);
    std::cout << "\t" << processed_task.taskID << "\n";
  }

  std::cout << "\nUndo-ing Tasks:\n";
  while (!task_actions.isEmpty())
  {
    std::cout << "\t" << task_actions.pop().taskID << "\n";
  }

  return 0;
}
