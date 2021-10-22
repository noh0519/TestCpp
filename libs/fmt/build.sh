#!/bin/bash

tar xvf 8.0.1.tar
mv fmt-8.0.1/ fmt/
mkdir fmt/build
pushd fmt/build
cmake ..
make
popd
