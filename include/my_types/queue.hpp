#pragma once // no double declarations
#include <memory> // for unique pointers

namespace my_types { // to make it cool

  template <typename T> // any type ^w^
  class queue {
  private:

    struct Node { // for linked list implementation
      T data;
      std::unique_ptr<Node> next; // using unique_ptr for safe linking
      
      Node(const T& val) : data(std::move(val)), next(nullptr) {} // constructor
    };

    std::unique_ptr<Node> head; // creating a head node
    Node* tail = nullptr; // tracking tail node for fast enqueue()
    size_t sz = 0; // size var

  public:

    bool is_empty() {
      return sz == 0; // self-explainatory
    }

    void enqueue(const T& newElem) {
      std::unique_ptr<Node> newNode = std::make_unique<Node>(newElem); // creating new unique_ptr
      Node* rawNode = newNode.get(); // saving the raw pointer for the tail tracking
      if (sz > 0) {
        tail->next = std::move(newNode); // transferring the ownership to tail ...
      } else {
        head = std::move(newNode); // or the head, if size is 0
      }
      tail = rawNode; // remember the raw pointer saved? There it's used!
      sz++; // increment size
    }

    T dequeue() {
      if (is_empty()) {
        throw std::runtime_error("Queue is empty"); // can't dequeue from empty queue
      }
      T res = std::move(head->data); // getting head (ayo)
      head = std::move(head->next); // moving the head pointer to the next node
      sz--; // decrement size
      if (is_empty()) tail = nullptr; // if popped last element, empty the tail
      return res; // passing the head
    }

    size_t size() { // getting size
      return sz;
    }

    template <typename Func>
    void for_each(Func f) const {
      Node* current = head.get();
      while (current != nullptr) {
        f(current->data);
        current = current->next.get();
      }
    }

    ~queue() { // in case of deleting a queue
      while (!is_empty()) {
        dequeue(); // iterative cleanup prevents stack overflow
      }
    }
  };
}
