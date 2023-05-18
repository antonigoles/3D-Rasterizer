echo [1/2] Cleaning old build files...
rm ./build -r
mkdir ./build
cd build
cmake -G "Ninja" ..
echo [2/2] Building and running...
cd build
cmake --build .
"../bin/3DRasterizer.exe"