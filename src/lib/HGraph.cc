#include "HGraph.h"

#include "Logger.h"

#include <cassert>

#include <sstream>
#include <string>

HGraph::HGraph(std::ifstream &FIn) {
  assert(FIn.is_open());

  unsigned EdgesNo = 0;
  unsigned VerticesNo = 0;
  FIn >> EdgesNo >> VerticesNo;

  Vertices.resize(VerticesNo + 1);
  Edges.resize(EdgesNo + 1);

  unsigned CurrentVert{0};
  std::string Line;
  unsigned EdgeC{0};
  while (getline(FIn, Line)) {
    std::istringstream Stream(Line);
    while (Stream >> CurrentVert) {
      Vertices[CurrentVert].push_back(EdgeC);
      Edges[EdgeC].push_back(CurrentVert);
    }
    ++EdgeC;
  }
}

void HGraph::dump(std::ostream &Out) const {
  Out << "HGraph dumping:\nVerticesNo: " << Vertices.size() - 1
      << " EdgesNo: " << Edges.size() - 1 << '\n';
  Out << "Vetices:\n";
  unsigned SkipFirst = 0;
  for (auto &&VertVec : Vertices) {
    if (!SkipFirst++)
      continue;
    for (auto &&Vert : VertVec)
      Out << Vert << ' ';
    Out << '\n';
  }
  Out << "Edges:\n";
  for (auto &&EdgesVec : Edges) {
    for (auto &&Edge : EdgesVec)
      Out << Edge << ' ';
    Out << '\n';
  }
}
