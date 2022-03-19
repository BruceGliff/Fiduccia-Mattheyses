#include "HGraph.h"

#include <cassert>

#include <sstream>
#include <string>

HGraph::HGraph(std::ifstream &FIn) {
  assert(FIn.is_open());

  unsigned EdgesNo = 0;
  unsigned VerticesNo = 0;
  FIn >> EdgesNo >> VerticesNo;

  Vertices.resize(VerticesNo);
  Edges.reserve(EdgesNo);

  unsigned CurrentVert{0};
  std::string Line;
  while (std::getline(FIn, Line)) {
    if (Line.size() < 2)
      continue;
    std::istringstream LineBuff{Line};
    std::vector<unsigned> EdgesTemp;
    while (LineBuff >> CurrentVert)
      EdgesTemp.push_back(CurrentVert - 1); // Vertex-1 to count from 0 to ..
    for (unsigned const &Vert : EdgesTemp)
      Vertices[Vert].push_back(Edges.size());
    Edges.emplace_back(std::move(EdgesTemp));
  }
}

void HGraph::dump(std::ostream &Out) {
  Out << "HGraph dumping:\nVerticesNo: " << Vertices.size()
      << " EdgesNo: " << Edges.size() << '\n';
  Out << "Vetices:\n";
  for (auto &&VertVec : Vertices) {
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
