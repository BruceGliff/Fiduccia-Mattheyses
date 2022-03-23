#include "Logger.h"

#include "Algorithm.h"
#include "AlgorithmMod.h"

#include "HGraph.h"
#include "Partitions.h"

#include <chrono>

int main(int argc, char *argv[]) {
  using namespace std::literals;
  if (argc == 1) {
    log().setOnce(std::cerr) << "No input file" << '\n';
    return -1;
  }
  std::string const Arg{argv[1]};
  bool const IsModified = Arg.compare("-m") == 0 ? true : false;
  int const FileIdx = IsModified ? 2 : Arg.size() == 0 ? 2 : 1;
  if (argc < FileIdx + 1) {
    log().setOnce(std::cerr) << "No input file" << '\n';
    return -1;
  }

  std::string const InFile{argv[FileIdx]};

  std::ifstream File{InFile};
  std::ofstream OutFile{InFile + ".part.2"};

  HGraph Graph{File};
  Partitions Prt{Graph};

  auto const Start = std::chrono::steady_clock::now();
  unsigned const Iterations =
      IsModified ? AlgMod::FM(Graph, Prt) : Alg::FM(Graph, Prt);
  auto const End = std::chrono::steady_clock::now();
  log() << InFile << ' ' << Graph.getEdges().size() << ' '
        << Graph.getVertices().size() << ' ' << Prt.getCost() << ' '
        << (End - Start) / 1ms << ' ' << Iterations << '\n';
  log().flush();

  Prt.dump(log().setOnce(OutFile));

  return 0;
}
