#!/bin/bash

for file in ./benchmark/*.hgr
do
  echo $file
  ./Initial $file
done
