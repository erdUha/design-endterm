#pragma once
#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

enum class TaskType {
  UNDEFINED,
  ADD_COMPONENT,
  CONNECT_COMPONENTS,
  TASK_DEQUEUED
};

class Task {
public:
  unsigned int task_id;
  TaskType task_type;
  std::string description;
  std::string component1, component2;
  std::chrono::system_clock::time_point timestamp;

  // constructor for empty task
  Task(): task_id(0), task_type(TaskType::UNDEFINED) {}

  // constructor for new component
  Task(
      unsigned int new_id,
      std::string new_component,
      std::string new_description
    ) :
    task_id(new_id),
    task_type(TaskType::ADD_COMPONENT),
    component1(new_component),
    description(new_description)
  {
    timestamp = std::chrono::system_clock::now();
  }

  // constructor for connecting components
  Task(
      unsigned int new_id,
      std::string new_component1, std::string new_component2,
      std::string new_description
    ) :
    task_id(new_id),
    task_type(TaskType::CONNECT_COMPONENTS),
    component1(new_component1),
    component2(new_component2),
    description(new_description)
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
    if (t.task_type == TaskType::ADD_COMPONENT)
      os << "[" << t.get_formatted_time() << "] " << "Task #" << t.task_id << ": " << t.description << "; New Component: \"" << t.component1 << "\"";
    else if (t.task_type == TaskType::CONNECT_COMPONENTS)
      os << "[" << t.get_formatted_time() << "] " << "Task #" << t.task_id << ": " << t.description << "; Connect Components: \"" << t.component1 << "\", \"" << t.component2 << "\"";
    return os;
  }
};
