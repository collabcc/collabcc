#!/bin/bash

set -e
source "$(dirname "${BASH_SOURCE[0]}")/ci_common.bashrc"
set -x

echo "Testing..."


docker_exec bash -c '
    set -xe
    export CTEST_OUTPUT_ON_FAILURE=1

    cd /coopcc-gcc
    make test -j "$NCPU"

    cd /coopcc-clang
    make test -j "$NCPU"
    '
