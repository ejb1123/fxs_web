#!/bin/sh

# fail on error

set -e

# add testing repository

echo http://dl-cdn.alpinelinux.org/alpine/edge/testing >> /etc/apk/repositories

# update apk cache

apk --no-cache update

apk --no-cache upgrade

# install runtime dependencies

apk add libc++ curl libssl1.0 libunwind libstdc++ zlib

# install compile-time dependencies

apk add --no-cache --virtual .dev-deps libc++-dev curl-dev clang clang-dev build-base linux-headers openssl-dev python2 py2-pip lua5.3 lua5.3-dev mono-dev

# install ply

pip install ply

# download and build premake

curl -sLo /tmp/premake.zip https://github.com/premake/premake-core/releases/download/v5.0.0-alpha11/premake-5.0.0-alpha11-src.zip

pushd /tmp

unzip -q premake.zip

rm premake.zip

cd premake-*

cd build/gmake.unix/

make -j4

cd ../../

mv bin/release/premake5 /usr/local/bin

cd ..

rm -rf premake-*

# download and extract boost

echo "Downloading Boost"
curl -sLo /tmp/boost.tar.bz2 https://dl.bintray.com/boostorg/release/1.64.0/source/boost_1_64_0.tar.bz2

echo "Extracting Boost"

tar xf boost.tar.bz2

rm boost.tar.bz2

mv boost_* boost

export BOOST_ROOT=/tmp/boost/

# build CitizenFX
popd
cd code

cp -a ../vendor/curl/include/curl/curlbuild.h.dist ../vendor/curl/include/curl/curlbuild.h

premake5 gmake --game=server --cc=clang --dotnet=msnet

echo '#pragma once' > shared/cfx_version.h

echo '#define GIT_DESCRIPTION "'$CI_BUILD_REF_NAME' v1.0.0.'$CI_PIPELINE_ID' linux"' >> shared/cfx_version.h

cd build/server/linux

export CXXFLAGS="-std=c++1z -stdlib=libc++"

make clean

make clean config=release

make -j4 config=release

cd ../../../


# clean up

rm -rf /tmp/boost

apk del .dev-deps