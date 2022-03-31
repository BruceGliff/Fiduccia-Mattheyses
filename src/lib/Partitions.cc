#include "Partitions.h"

#include "Logger.h"

#include <algorithm>

void Partitions::calculateCost() {
  unsigned Skip = 0;
  for (auto &&EdgesVec : Graph.getEdges()) {
    if (!Skip++)
      continue;
    bool const CurrentPartition = VertPartitions[EdgesVec[0]];
    bool const Inc =
        std::any_of(EdgesVec.begin() + 1, EdgesVec.end(),
                    [&CurrentPartition, this](int Edge) {
                      return VertPartitions[Edge] != CurrentPartition;
                    });
    if (Inc)
      ++Cost;
  }
}

Partitions::Partitions(HGraph const GraphIn) : Graph{GraphIn} {
  unsigned const Size = Graph.getVertices().size() - 1;
  VertPartitions.resize(Size + 1);
  // TODO remake static partition initialization,
  for (unsigned i = 1; i <= Size / 2; ++i)
    VertPartitions[i] = false;
  for (unsigned i = Size / 2 + 1; i <= Size; ++i)
    VertPartitions[i] = true;

  Side = Size % 2;
  calculateCost();
}

void Partitions::update(unsigned Vertex) {
  int const Inc = VertPartitions.at(Vertex) ? -1 : 1;
  Side += Inc;
  VertPartitions.at(Vertex) = !VertPartitions.at(Vertex);
}

void Partitions::dump(std::ostream &Out) const {
  Out << "Left: ";
  unsigned const Size = VertPartitions.size();
  for (unsigned i = 1; i != Size; ++i)
    if (!VertPartitions[i])
      Out << i << " ";
  Out << "\nRight: ";
  for (unsigned i = 1; i != Size; ++i)
    if (VertPartitions[i])
      Out << i << " ";
  Out << "\nSolution cost: " << Cost << '\n';
}

void Partitions::out(std::ostream &Out) const {
  unsigned Skip = 0;
  for (auto &&Part : VertPartitions) {
    if (!Skip++)
      continue;
    Out << Part << '\n';
  }
}