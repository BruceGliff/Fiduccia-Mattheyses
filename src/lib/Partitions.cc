#include "Partitions.h"

#include <algorithm>

void Partitions::calculateCost() {
  for (auto &&EdgesVec : Graph.getEdges()) {
    bool const CurrentPartition = VertPartitions[EdgesVec[0]];
    bool const Inc = std::any_of(
        EdgesVec.begin(), EdgesVec.end(), [&CurrentPartition, this](int Edge) {
          return VertPartitions[Edge] != CurrentPartition;
        });
    if (Inc)
      ++Cost;
  }
}

Partitions::Partitions(HGraph const GraphIn) : Graph{GraphIn} {
  unsigned const Size = Graph.getVertices().size();
  VertPartitions.resize(Size);
  // TODO remake static partition initialization,
  for (unsigned i = 0; i <= Size / 2; ++i)
    VertPartitions[i] = false;
  for (unsigned i = Size / 2 + 1; i != Size; ++i)
    VertPartitions[i] = true;

  Balance = Size % 2;
  calculateCost();
}

void Partitions::dump(std::ostream &Out) const {
  Out << "Left: ";
  unsigned const Size = VertPartitions.size();
  for (unsigned i = 0; i != Size; ++i)
    if (!VertPartitions[i])
      Out << i << " ";
  Out << "\nRight: ";
  for (unsigned i = 0; i != Size; ++i)
    if (VertPartitions[i])
      Out << i << " ";
  Out << "\nSolution cost: " << Cost << '\n';
}
