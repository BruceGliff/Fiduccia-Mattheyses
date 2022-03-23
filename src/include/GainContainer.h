#pragma once

#include <iostream>
#include <list>
#include <map>
#include <vector>

class HGraph;
class Partitions;

class GainContainer {

  using RLSide = std::map<int, std::list<int>>;
  using Move = std::pair<unsigned, int>;

  RLSide Left;
  RLSide Right;

  std::vector<int> VertGain;
  std::vector<bool> IsDeleted;
  std::vector<int> Deltas;
  std::vector<std::list<int>::iterator> Iterators;

  RLSide &getNeededSide(bool Side);
  RLSide const &getNeededSide(bool Side) const;

public:
  GainContainer(HGraph const &HG, Partitions const &Prt);
  bool isEmpty(bool Check) const;
  Move bestFeasibleMove(bool Side);
  void update(unsigned Vertex, bool Side, int Value);
  void erase(unsigned Vertex, bool Side);
  void updateDeleted(unsigned Vertex);
  std::vector<int> &getDeltas();
  std::vector<int> const &getDeltas() const;

  void dump(std::ostream &Out = std::cout) const;
};
