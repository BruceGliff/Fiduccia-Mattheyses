#pragma once

#include <map>
#include <set>
#include <vector>

class HGraph;
class Partitions;

class GainContainer {

  using Branch = std::map<int, std::set<int>>;

  Branch Left;
  Branch Right;

  std::vector<int> VertGain;
  std::set<unsigned> IsDeleted;

public:
  GainContainer(HGraph const &HG, Partitions const &Prt);
};
