#!/bin/bash

set -ex

BUILD_DIR=${TRAVIS_BUILD_DIR}

mkdir -p "${DEPENDENCY_DIR}" && cd "${DEPENDENCY_DIR}"


# ---  GSL
if [[ ! -d "${DEPENDENCY_DIR}/gsl" ]]
then
    git clone --depth=1 https://github.com/Microsoft/GSL.git gsl
fi


cd ${DEPENDENCY_DIR}



# --- CppUTest
if [[ "$CXX" != "arm-none-eabi-g++" ]]
then
    if [[ ! -d "${DEPENDENCY_DIR}/cpputest" ]]
    then
        git --depth=1 https://github.com/cpputest/cpputest.git cpputest
    fi

    BUILD_FLAGS="-DC++11=ON -DTESTS=OFF"

    if [[ "$CXX" == clang* ]]
    then
        BUILD_FLAGS="${BUILD_FLAGS} -DCMAKE_CXX_FLAGS=-stdlib=libc++"
    fi

    mkdir -p _build && cd _build
    cmake ${BUILD_FLAGS} ..
    make -j4 && sudo make install
fi

cd ${DEPENDENCY_DIR}

