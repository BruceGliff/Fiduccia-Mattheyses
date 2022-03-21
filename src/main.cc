#include "Logger.h"

#include "Algorithm.h"
#include "HGraph.h"
#include "Partitions.h"

int main(int argc, char *argv[]) {

  if (argc == 1) {
    log().setOnce(std::cerr) << "No input file" << '\n';
    return -1;
  }
  bool const IsModified =
      std::string{argv[1]}.compare("-m") == 0 ? true : false;
  int const FileIdx = IsModified ? 2 : 1;
  if (argc < FileIdx + 1) {
    log().setOnce(std::cerr) << "No input file" << '\n';
    return -1;
  }

  std::string const InFile{argv[FileIdx]};

  std::ifstream File{InFile};
  std::ofstream OutFile{InFile + ".part.2"};

  HGraph Graph{File};
  Partitions Prt{Graph};

  Alg::FM(Graph, Prt);

  Prt.dump(log().setOnce(OutFile));

  return 0;
}
