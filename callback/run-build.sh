#!/bin/bash

set -e

#export DYLD_FALLBACK_LIBRARY_PATH="$PWD/lib/:$DYLD_FALLBACK_LIBRARY_PATH";

#echo $DYLD_FALLBACK_LIBRARY_PATH

pushd lib

# build c shared lib from go source
go build -buildmode=c-archive -o libgo.a

popd

# configure then build
node-gyp rebuild

