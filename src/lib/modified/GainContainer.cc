#include "GainContainer.h"

#include "Logger.h"

#include "HGraph.h"
#include "Partitions.h"

using namespace AlgMod;

GainContainer::GainContainer(HGraph const &HG, Partitions const &Prt) {
  unsigned const VertSize = Prt.getPart().size();
  VertGain.resize(VertSize);
  IsDeleted.resize(VertSize);
  Deltas.resize(VertSize);
  Iterators.resize(VertSize);

  unsigned SkipFirst = 0;
  for (auto &&VecEdges : HG.getEdges()) {
    if (!SkipFirst++)
      continue;
    int VLeft = 0, VRight = 0;
    unsigned VLeftId = 0, VRightId = 0;
    for (unsigned Vertex : VecEdges)
      if (!Prt.getPart().at(Vertex)) {
        VLeft++;
        VLeftId = Vertex;
      } else {
        VRight++;
        VRightId = Vertex;
      }

    if ((VRight == 0 && VLeft != 1) || (VLeft == 0 && VRight != 1))
      for (unsigned Vertex : VecEdges)
        --VertGain[Vertex];

    if (VLeft == 1 && VRight != 0)
      ++VertGain[VLeftId];
    if (VRight == 1 && VLeft != 0)
      ++VertGain[VRightId];
  }

  for (unsigned i = 1; i != Prt.getPart().size(); ++i) {
    auto &&Side = getNeededSide(Prt.getPart().at(i));
    auto &Item = Side[VertGain[i]];
    Item.push_front(i);
    Iterators[i] = Item.begin();
  }
}

GainContainer::RLSide &GainContainer::getNeededSide(bool Side) {
  return Side ? Right : Left;
}
GainContainer::RLSide const &GainContainer::getNeededSide(bool Side) const {
  return Side ? Right : Left;
}

bool GainContainer::isEmpty(bool Side) const {
  auto const &SizeToUpd = getNeededSide(Side);
  return SizeToUpd.empty();
}

GainContainer::Move GainContainer::bestFeasibleMove(bool Side) {
  auto &SizeToUpd = getNeededSide(Side);

  auto &&[Gain, Vertices] = *SizeToUpd.rbegin();
  unsigned Vertex = *Vertices.begin();
  Vertices.pop_front();
  IsDeleted[Vertex] = true;
  if (Vertices.empty())
    SizeToUpd.erase(Gain);

  return std::make_pair(Vertex, Gain);
}

void GainContainer::update(unsigned Vertex, bool Side, int Value) {
  if (IsDeleted[Vertex])
    return;
  erase(Vertex, Side);
  VertGain[Vertex] += Value;
  auto &SizeToUpd = getNeededSide(Side);
  SizeToUpd[VertGain[Vertex]].push_front(Vertex);
  Iterators[Vertex] = SizeToUpd[VertGain[Vertex]].begin();
}

void GainContainer::erase(unsigned Vertex, bool Side) {
  if (IsDeleted[Vertex])
    return;
  auto &SizeToUpd = getNeededSide(Side);
  int const Gain = VertGain.at(Vertex);
  SizeToUpd[Gain].erase(Iterators[Vertex]);
  if (SizeToUpd[Gain].empty())
    SizeToUpd.erase(Gain);
}

void GainContainer::updateDeleted(unsigned Vertex) { IsDeleted[Vertex] = true; }

std::vector<int> const &GainContainer::getDeltas() const { return Deltas; }
std::vector<int> &GainContainer::getDeltas() { return Deltas; }

void GainContainer::dump(std::ostream &Out) const {
  Out << "Left\n";
  for (auto &&Item : Left) {
    Out << Item.first << ": ";
    for (auto Vert : Item.second)
      Out << Vert << ' ';
    Out << '\n';
  }
  Out << "Right\n";
  for (auto &&Item : Right) {
    Out << Item.first << ": ";
    for (auto Vert : Item.second)
      Out << Vert << ' ';
    Out << '\n';
  }
}
