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
  // Vertices.resize(VerticesNo);
  // Edges.reserve(EdgesNo);

  unsigned CurrentVert{0};
  std::string Line;
  // while (std::getline(FIn, Line)) {
  //   if (Line.size() < 2)
  //     continue;
  //   std::istringstream LineBuff{Line};
  //   std::vector<unsigned> EdgesTemp;
  //   while (LineBuff >> CurrentVert)
  //     EdgesTemp.push_back(CurrentVert - 1); // Vertex-1 to count from 0 to ..
  //   for (unsigned const &Vert : EdgesTemp)
  //     Vertices[Vert].push_back(Edges.size());
  //   Edges.emplace_back(std::move(EdgesTemp));
  // }

  int edge_count = 0, vert_curr = 0;
  while (getline(FIn, Line)) {
    std::istringstream tmp_str_stm(Line);
    while (tmp_str_stm >> vert_curr) {
      Vertices[vert_curr].push_back(edge_count);
      Edges[edge_count].push_back(vert_curr);
    }
    edge_count++;
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
