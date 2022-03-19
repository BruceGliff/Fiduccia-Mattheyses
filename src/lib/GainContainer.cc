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

    if (!CurrentPart)
      Left[CurrentGain].insert(i);
    else
      Right[CurrentGain].insert(i);
    VertGain[i] = CurrentGain;
  }
}
