#include <chrono>
#include <iomanip>
#include <string>
#include <sstream>

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
    os << "[" << t.get_formatted_time() << "] " << "Task #" << t.taskID << ": " << t.description;
    return os;
  }
};
