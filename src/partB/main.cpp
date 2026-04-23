#include <iostream>
#include <set>
#include <vector>
#include "my_types/union_find.hpp"

int main(int argc, char** argv)
{
  std::set<std::string> components = {
    "A", "B", "C", "D", "E", "F"
  };
  my_types::union_find<std::string> CMM(components);
  CMM.visualize();
  CMM._union("B", "C");
  CMM._union("D", "E");
  CMM._union("B", "D");
  std::cout << "\n>>> union(\"B\", \"C\")\n";
  std::cout << ">>> union(\"D\", \"E\")\n";
  std::cout << ">>> union(\"B\", \"D\")\n";
  CMM.visualize("After Unions");
  CMM.find("B");
  std::cout << "\n>>> find(\"B\")\n";
  CMM.visualize("After the Path Compression");
  return 0;
}
