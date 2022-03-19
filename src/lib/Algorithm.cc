#include "Algorithm.h"

#include "GainContainer.h"

namespace Alg {

void FM(HGraph const &HG, Partitions &Prt) {
  bool Improved = false;
  do {
    GainContainer GC{HG, Prt};
    Improved = true;
  } while (Improved);
}

void FMPass(GainContainer &GC, Partitions &Prt) {}

} // namespace Alg
