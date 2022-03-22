#!/bin/bash

echo "File Edges Vertices Cut Time Iterations"
for file in ./benchmark/*.hgr
do
  ./Initial $file &
done
wait
