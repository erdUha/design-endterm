#pragma once // no double declarations
#include <iostream>
#include <unordered_map>
#include <set>
#include <vector>

namespace my_types { // to make it cool

  template <typename T> // any type ^w^
  class union_find {
  private:

    std::vector<unsigned int> parent;
    std::vector<unsigned int> rank;
    std::unordered_map<T, unsigned int> val_to_id;

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

    union_find(const std::set<T>& xs) {
      val_to_id.reserve(xs.size());
      parent.reserve(xs.size());
      rank.reserve(xs.size());

      for (const T& x : xs)
        add_component(x);
    }

    void add_component(const T& x) {
      if (val_to_id.find(x) != val_to_id.end()) // if already exists
        return;
      unsigned int new_id = parent.size();
      val_to_id[x] = new_id;
      parent.push_back(new_id);
      rank.push_back(0);
    }

    unsigned int find(const T& x) {
      auto it = val_to_id.find(x);
      if (it == val_to_id.end()) {
        throw std::runtime_error("Component not found");
      }
      return find_by_id(it->second);
    }

    void _union(const T& x, const T& y) {
      unsigned int x_root = find(x);
      unsigned int y_root = find(y);

      if (x_root == y_root) return;

      if (rank[x_root] < rank[y_root]) {
        parent[x_root] = y_root;
      } else if (rank[x_root] > rank[y_root]) {
        parent[y_root] = x_root;
      } else {
        parent[x_root] = y_root;
        rank[y_root]++;
      }
    }

    bool connected(const T& x, const T& y) {
      return find(x) == find(y);
    }

    void visualize(const std::string& message) {
      visualize_private(message);
    }

    void visualize() {
      visualize_private("");
    }
  };
}
