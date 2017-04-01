#!/bin/bash

set -e

pushd lib

# build c shared lib from go source
go build -buildmode=c-archive -o libgo.a

popd

# configure then build
node-gyp rebuild

