cd .. && make -j2 && cd - && gcc -o a.out test.cc -I../src -I../deps/v8 -I../deps/v8/src -L`pwd`/../out/Release/lib.target -lnode && LD_LIBRARY_PATH=../out/Release/lib.target ./a.out
# make -C out BUILDTYPE=Debug V=1 && gcc -ggdb -o a.out test.cc -Isrc -Ideps/v8 -Ideps/v8/src -L`pwd`/out/Debug/lib.target -lnode && LD_LIBRARY_PATH=out/Debug/lib.target ./a.out
