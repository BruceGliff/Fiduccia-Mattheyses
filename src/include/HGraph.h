#pragma once

#include <fstream>
#include <iostream>
#include <vector>

class HGraph {

  using Connections = std::vector<std::vector<int>>;

  Connections Vertices;
  Connections Edges;

public:
  HGraph(std::ifstream &FIn);

  void dump(std::ostream &Out = std::cout);

  Connections const &getVertices() const { return Vertices; }
  Connections const &getEdges() const { return Edges; }
};
