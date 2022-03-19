#pragma once

class HGraph;
class Partitions;
class GainContainer;

namespace Alg {

void FM(HGraph const &, Partitions &);
void FMPass(GainContainer &, Partitions &);

} // namespace Alg
