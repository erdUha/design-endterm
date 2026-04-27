#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

class Task {
public:
  unsigned int task_id;
  unsigned int task_type; // 1 = New Component, 2 = Connect
  std::string description;
  std::string component1, component2;
  std::chrono::system_clock::time_point timestamp;

  // constructor for new component
  Task(
      unsigned int new_id,
      std::string new_component,
      std::string new_description
    ) :
    task_id(new_id),
    task_type(1),
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
    task_type(2),
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
    if (t.task_type == 1)
      os << "[" << t.get_formatted_time() << "] " << "Task #" << t.task_id << ": " << t.description << "; New Component: \"" << t.component1 << "\"";
    else if (t.task_type == 2)
      os << "[" << t.get_formatted_time() << "] " << "Task #" << t.task_id << ": " << t.description << "; Connect Components: \"" << t.component1 << "\", \"" << t.component2 << "\"";
    return os;
  }
};
