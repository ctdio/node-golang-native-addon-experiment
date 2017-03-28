#!/bin/bash

export DYLD_FALLBACK_LIBRARY_PATH=./lib:$DYLD_FALLBACK_LIBRARY_PATH

pushd lib

# build c shared lib from go source
go build -buildmode=c-shared -o libgo.so

popd

# configure then build
node-gyp rebuild

