#pragma once

#include <fstream>
#include <iostream>
#include <vector>

class HGraph {

  using Connections = std::vector<std::vector<unsigned>>;

  Connections Vertices;
  Connections Edges;

public:
  HGraph(std::ifstream &FIn);

  void dump(std::ostream &Out = std::cout) const;

  Connections const &getVertices() const { return Vertices; }
  Connections const &getEdges() const { return Edges; }
};
