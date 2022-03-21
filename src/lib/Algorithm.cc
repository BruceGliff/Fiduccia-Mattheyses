#include "Algorithm.h"

#include "Logger.h"

#include "GainContainer.h"
#include "Partitions.h"

static int FMPass(GainContainer &GC, Partitions &Prt, HGraph const &HG);
static void applyMove(GainContainer &GC, Partitions &Prt, HGraph const &HG,
                      unsigned MoveVertex);

namespace Alg {

void FM(HGraph const &HG, Partitions &Prt) {
  while (1) {
    GainContainer GC{HG, Prt};
    int const Best = FMPass(GC, Prt, HG);
    if (Best == Prt.getCost())
      break;

    Prt.setCost(Best);
  }
}

} // namespace Alg

int FMPass(GainContainer &GC, Partitions &Prt, HGraph const &HG) {
  int Cost = Prt.getCost();
  int BestCost = Cost;

  std::set<unsigned> VertToChange;

  while (!GC.isEmpty(Prt.getSide())) {
    auto [Vertex, Gain] = GC.bestFeasibleMove(Prt.getSide());
    VertToChange.insert(Vertex);
    Cost -= Gain;
    if (Cost < BestCost) {
      BestCost = Cost;
      VertToChange.clear();
    }
    applyMove(GC, Prt, HG, Vertex);
  }

  for (auto Vertex : VertToChange)
    Prt.update(Vertex);
  return BestCost;
}

void applyMove(GainContainer &GC, Partitions &Prt, HGraph const &HG,
               unsigned MoveVertex) {
  for (auto Edge : HG.getVertices().at(MoveVertex)) {
    bool IsNoVInDst = true;
    bool IsOneVInSrc = true;

    int CountInDst = 0;
    unsigned VertDst = 0;

    int CountInSrc = 0;
    unsigned VertSrc = 0;

    for (auto Vertex : HG.getEdges().at(Edge)) {
      if ((Prt.getSide() && !Prt.getPart().at(Vertex)) ||
          (!Prt.getSide() && Prt.getPart().at(Vertex))) {
        IsNoVInDst = false;
        ++CountInDst;
        VertDst = Vertex;
      } else if (Vertex != MoveVertex) {
        ++CountInSrc;
        VertSrc = Vertex;
      }
      if (Prt.getPart().at(MoveVertex) == Prt.getPart().at(Vertex) &&
          Vertex != MoveVertex)
        IsOneVInSrc = false;
    }

    int const UpdateVal = IsNoVInDst ? 1 : IsOneVInSrc ? -1 : 0;

    if (UpdateVal)
      for (auto Vertex : HG.getEdges().at(Edge))
        GC.update(Vertex, Prt.getPart().at(Vertex), UpdateVal);

    if (CountInSrc == 1)
      GC.update(VertSrc, Prt.getPart().at(VertSrc), 1);
    if (CountInDst == 1)
      GC.update(VertDst, Prt.getPart().at(VertDst), -1);
  }

  GC.erase(MoveVertex, Prt.getPart().at(MoveVertex));
  GC.updateDeleted(MoveVertex);
  Prt.update(MoveVertex);
}
