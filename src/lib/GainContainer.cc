#include "GainContainer.h"

#include "HGraph.h"
#include "Partitions.h"

GainContainer::GainContainer(HGraph const &HG, Partitions const &Prt) {
  unsigned const VertSize = Prt.getPart().size();
  VertGain.resize(VertSize);

  for (unsigned i = 0; i != VertSize; ++i) {
    int CurrentGain = 0;
    bool CurrentPart = Prt.getPart().at(i);

    for (unsigned EdgeId : HG.getVertices().at(i)) {
      bool IsAlone = true;
      bool IsEntirely = true;

      for (unsigned VertId : HG.getEdges().at(EdgeId)) {
        if (CurrentPart != Prt.getPart().at(VertId))
          IsEntirely = false;
        if (CurrentPart == Prt.getPart().at(VertId) && VertId != i)
          IsAlone = false;
      }

      if (IsAlone)
        ++CurrentGain;
      if (IsEntirely)
        --CurrentGain;
    }

    auto &SizeToUpd = getNeededSide(CurrentPart);
    SizeToUpd[CurrentGain].insert(i);
    VertGain[i] = CurrentGain;
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
  Vertices.erase(Vertex);

  if (Vertices.empty())
    SizeToUpd.erase(Gain);

  return std::make_pair(Vertex, Gain);
}

void GainContainer::update(unsigned Vertex, bool Side, int Value) {
  if (IsDeleted.count(Vertex))
    return;
  erase(Vertex, Side);
  auto &SizeToUpd = getNeededSide(Side);
  SizeToUpd[VertGain[Vertex]].insert(Vertex);
}

void GainContainer::erase(unsigned Vertex, bool Side) {
  auto &SizeToUpd = getNeededSide(Side);
  int const Gain = VertGain.at(Vertex);
  SizeToUpd[Gain].erase(Vertex);
  if (SizeToUpd[Gain].empty())
    SizeToUpd.erase(Gain);
}

void GainContainer::updateDeleted(unsigned Vertex) { IsDeleted.insert(Vertex); }
