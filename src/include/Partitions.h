#pragma once

#include "HGraph.h"

#include <iostream>
#include <vector>

class Partitions {

  // TODO Why wont use set?
  std::vector<bool> VertPartitions;
  HGraph const &Graph;

  int Cost{0};
  bool Balance;

  void calculateCost();

public:
  Partitions(HGraph const GraphIn);
  void dump(std::ostream &Out = std::cout) const;
};
