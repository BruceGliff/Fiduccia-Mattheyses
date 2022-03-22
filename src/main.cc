#include "Logger.h"

#include "Algorithm.h"
#include "HGraph.h"
#include "Partitions.h"

#include <chrono>

int main(int argc, char *argv[]) {
  using namespace std::literals;
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
  log() << InFile << ' ';

  std::ifstream File{InFile};
  std::ofstream OutFile{InFile + ".part.2"};

  HGraph Graph{File};
  log() << Graph.getEdges().size() << ' ' << Graph.getVertices().size() << ' ';
  Partitions Prt{Graph};

  auto const Start = std::chrono::steady_clock::now();
  unsigned const Iterations = Alg::FM(Graph, Prt);
  auto const End = std::chrono::steady_clock::now();
  log() << Prt.getCost() << ' ' << (End - Start) / 1ms << ' ' << Iterations
        << '\n';

  Prt.dump(log().setOnce(OutFile));

  return 0;
}
