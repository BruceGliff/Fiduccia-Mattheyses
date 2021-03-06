#pragma once

#include "HGraph.h"

#include <iostream>
#include <vector>

class Partitions {
  std::vector<bool> VertPartitions;
  HGraph const &Graph;

  int Cost{0};
  int Side{0};

  void calculateCost();

public:
  Partitions(HGraph const GraphIn);
  void dump(std::ostream &Out = std::cout) const;
  void out(std::ostream &Out = std::cout) const;
  int getCost() const { return Cost; }
  void setCost(int CostIn) { Cost = CostIn; }
  int getSide() const { return Side; }
  void update(unsigned Vertex);

  std::vector<bool> const &getPart() const { return VertPartitions; }
};
