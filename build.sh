if [ -d build ]; then rm -rf build; fi

mkdir build
cd build

# Release
mkdir Release
cd Release
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Release ../..
make

cd ..

# Debug
mkdir Debug
cd Debug
cmake -G "Unix Makefiles" -D CMAKE_BUILD_TYPE=Debug ../..
make

cd ..
