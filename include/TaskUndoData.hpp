#pragma once
#include <string>
#include <my_types/queue.hpp>
#include <my_types/union_find.hpp>
#include <Task.hpp>

class TaskUndoData {
public:
  Task task_snapshot;
  my_types::union_find<std::string> components_snapshot;
  bool was_successful;

  TaskUndoData() {}

  TaskUndoData(const Task& task, const my_types::union_find<std::string>& components_before) // execute before task completion
    : task_snapshot(task), components_snapshot(components_before) {}
};
