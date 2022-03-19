#include "HGraph.h"
#include "Partitions.h"

int main(int argc, char *argv[]) {
  std::ifstream File{"./benchmark/ISPD98_ibm01.hgr"};
  HGraph Graph{File};
  Partitions Prt{Graph};
}
