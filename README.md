# Fiduccia-Mattheyses
Implementation of the Fiduccia-Mattheyses heuristic to cut hypergraph in two partions.

Requires:
```
CMake
C++ 17 standart
```
Build:
```
mkdir build && cd build
cmake ..
cmake --build .
```
Launch:
```
.\Initial.exe [-m] path_to_benchmark
```
Out/Results:
```
path_to_benchmark nets cells cost time(ms) iterations
creates file path_to_benchmark.part.2 with final cut.
```
