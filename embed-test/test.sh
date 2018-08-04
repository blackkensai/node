#!/bin/bash -x
cd .. && make -j2 && cd - && \
gcc -o a.out test.cc -I../src -I../src/android -I../deps/v8 -I../deps/v8/src -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L`pwd`/../out/Release/lib.target -lnode && \
LD_LIBRARY_PATH=../out/Release/lib.target ./a.out
# make -C out BUILDTYPE=Debug V=1 && gcc -ggdb -o a.out test.cc -Isrc -Ideps/v8 -Ideps/v8/src -L`pwd`/out/Debug/lib.target -lnode && LD_LIBRARY_PATH=out/Debug/lib.target ./a.out

javac pkg/Test.java -h .
g++ -o libTest.so TestJava.cc -shared -fPIC -I../src -I../src/android -I../deps/v8 -I../deps/v8/src -I${JAVA_HOME}/include -I${JAVA_HOME}/include/linux -L`pwd`/../out/Release/lib.target -lnode 
LD_LIBRARY_PATH=../out/Release/lib.target java -cp . -Djava.library.path=$(pwd):`pwd`/../out/Release/lib.target pkg.Test