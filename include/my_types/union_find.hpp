#pragma once // no double declarations
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

namespace my_types { // to make it cool

  template <typename T> // any type ^w^
  class union_find {
  private:

    std::vector<unsigned int> parent; // disjoint set
    std::vector<unsigned int> rank; // rank set
    std::unordered_map<T, unsigned int> val_to_id; // supporting any unique values, like strings (A, B, C etc.)

    unsigned int find_by_id(unsigned int id) {
      if (parent[id] == id) return id;
      return parent[id] = find_by_id(parent[id]); // recursive path compression
    }

    void visualize_private(const std::string& message) {
      // 1. Create a reverse map to turn ID -> Name
      // This makes the output "Component A -> Component B" instead of "0 -> 1"
      std::unordered_map<unsigned int, T> id_to_val;
      for (const auto& pair : val_to_id) {
          id_to_val[pair.second] = pair.first;
      }

      if (message.empty())
        std::cout << "\n--- Connectivity Tree Structure ---\n";
      else
        std::cout << "\n--- Connectivity Tree Structure " << message << " ---\n";

      for (unsigned int i = 0; i < parent.size(); i++) {
          T current_name = id_to_val[i];
          
          if (parent[i] == i) {
              // This node is a Root
              std::cout << "[ROOT] " << current_name << "\n";
          } else {
              // This node points to a parent
              T parent_name = id_to_val[parent[i]];
              std::cout << "  " << current_name << " --> " << parent_name << "\n";
          }
      }
      std::cout << "-----------------------------------\n";
    }

  public:

    union_find(const std::set<T>& xs) { // constructor
      val_to_id.reserve(xs.size());
      parent.reserve(xs.size());
      rank.reserve(xs.size());

      for (const T& x : xs)
        add_component(x);
    }
    
    union_find() { // constructor without initial set
    }

    void add_component(const T& x) {
      if (val_to_id.find(x) != val_to_id.end()) // if already exists
        throw std::runtime_error("The Element Already Exists");
      unsigned int new_id = parent.size();
      val_to_id[x] = new_id; // creating a new component
      parent.push_back(new_id); // and making it in it's own set
      rank.push_back(0); // setting rank to 0 (no childs)
    }

    unsigned int find(const T& x) {
      auto it = val_to_id.find(x); // checking if the element exists
      if (it == val_to_id.end()) {
        throw std::runtime_error("Component not Found");
      }
      return find_by_id(it->second); // using private method for everyting else
    }

    void _union(const T& x, const T& y) { // union is reserved keyword, so _union was used
      unsigned int x_root = find(x);
      unsigned int y_root = find(y);

      if (x_root == y_root) return; // if they are already connected, don't do anything

      if (rank[x_root] < rank[y_root]) {
        parent[x_root] = y_root; // connect x tree to y if x is smaller
      } else if (rank[x_root] > rank[y_root]) {
        parent[y_root] = x_root; // otherwise, connect y tree to x
      } else {
        parent[x_root] = y_root; // or just increment rank of the shared root
        rank[y_root]++;
      }
    }

    bool connected(const T& x, const T& y) {
      return find(x) == find(y);
    }

    void visualize() { // overloading for no message
      visualize_private("");
    }

    void visualize(const std::string& message) { // overloading for message support
      visualize_private(message);
    }
  };
}
