rem Use this batch file to build box2d for Visual Studio
rmdir /s /q build
mkdir build
cd build
cmake -DBOX2D_BUILD_DOCS=OFF -DCMAKE_INSTALL_PREFIX="C:/packages" .. -G "MinGW Makefiles"
cmake --build . --config Release

