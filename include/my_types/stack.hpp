#pragma once // no double declarations
#include <vector>

namespace my_types { // to make it cool

  template <typename T> // any type ^w^
  class stack {
  private:
    std::vector<T> data; // dynamic array

  public:
    bool is_empty() {
      return data.empty(); // checking if empty
    }

    void push(const T& newVar) {
      data.push_back(newVar); // just pushing onto the stack
    }

    T pop() {
      if (is_empty()) {
        throw std::runtime_error("Stack is empty");
      }
      T res = data.back(); // getting the element
      data.pop_back(); // removing the element
      return res;
    }

    T peek() {
      if (is_empty()) {
        throw std::runtime_error("Stack is empty");
      }
      return data.back(); // just getting the element
    }
  };
}
