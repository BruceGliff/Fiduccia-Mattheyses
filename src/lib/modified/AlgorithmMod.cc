#include "AlgorithmMod.h"

#include "Logger.h"

#include "GainContainer.h"
#include "Partitions.h"

using namespace AlgMod;

static int FMPass(GainContainer &GC, Partitions &Prt, HGraph const &HG);
static void applyMove(GainContainer &GC, Partitions &Prt, HGraph const &HG,
                      unsigned MoveVertex, unsigned it);

namespace AlgMod {

unsigned FM(HGraph const &HG, Partitions &Prt) {
  unsigned Iteration = 0;
  while (1) {
    ++Iteration;
    GainContainer GC{HG, Prt};
    int const Best = FMPass(GC, Prt, HG);
    if (Best == Prt.getCost())
      break;

    Prt.setCost(Best);
  }
  return Iteration;
}

} // namespace AlgMod

int FMPass(GainContainer &GC, Partitions &Prt, HGraph const &HG) {
  int Cost = Prt.getCost();
  int BestCost = Cost;

  std::vector<unsigned> VertToChange;

  unsigned it = 0;
  while (!GC.isEmpty()) {
    auto [Vertex, Gain] = GC.bestFeasibleMove(Prt.getSide());
    VertToChange.push_back(Vertex);
    Cost -= Gain;
    if (Cost < BestCost) {
      BestCost = Cost;
      VertToChange.clear();
    }
    applyMove(GC, Prt, HG, Vertex, it);
  }

  for (auto Vertex : VertToChange)
    Prt.update(Vertex);

  return BestCost;
}

void applyMove(GainContainer &GC, Partitions &Prt, HGraph const &HG,
               unsigned MoveVertex, unsigned it) {
  for (auto Edge : HG.getVertices().at(MoveVertex)) {
    bool IsNoVInDst = true;
    bool IsOneVInSrc = true;

    int CountInDst = 0;
    unsigned VertDst = 0;

    int CountInSrc = 0;
    unsigned VertSrc = 0;

    for (auto Vertex : HG.getEdges().at(Edge)) {
      if (Prt.getPart().at(MoveVertex)) {
        if (!Prt.getPart().at(Vertex)) {
          IsNoVInDst = false;
          CountInDst++;
          VertDst = Vertex;
        } else if (Vertex != MoveVertex) {
          CountInSrc++;
          VertSrc = Vertex;
        }
      } else {
        if (Prt.getPart().at(Vertex)) {
          IsNoVInDst = false;
          CountInDst++;
          VertDst = Vertex;
        } else if (Vertex != MoveVertex) {
          CountInSrc++;
          VertSrc = Vertex;
        }
      }

      if (Prt.getPart().at(MoveVertex) == Prt.getPart().at(Vertex) && Vertex != MoveVertex)
        IsOneVInSrc = false;
    }

    int const UpdateVal = IsNoVInDst ? 1 : IsOneVInSrc ? -1 : 0;

    if (UpdateVal)
      for (auto Vertex : HG.getEdges().at(Edge))
        GC.getDeltas().at(Vertex) += UpdateVal;

    if (CountInSrc == 1)
      ++GC.getDeltas().at(VertSrc);
    if (CountInDst == 1)
      --GC.getDeltas().at(VertDst);
  }

  GC.erase(MoveVertex, Prt.getPart().at(MoveVertex));
  GC.updateDeleted(MoveVertex);

  for (unsigned Edge : HG.getVertices().at(MoveVertex))
    for (unsigned Vertex : HG.getEdges().at(Edge))
      if (GC.getDeltas().at(Vertex)) {
        GC.update(Vertex, Prt.getPart().at(Vertex), GC.getDeltas().at(Vertex));
        GC.getDeltas().at(Vertex) = 0;
      }

  Prt.update(MoveVertex);

}
