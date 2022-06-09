#include <iostream>
#include "node_server.hpp"

int main() {
  Nodes::NodeServer server("127.0.0.1:50505");

  server.run();
  return 0;
}