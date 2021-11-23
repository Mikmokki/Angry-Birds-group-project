Remove-Item -Recurse -Force build
New-Item -ItemType Directory -Path build
cd build
cmake .. -G "MinGW Makefiles"
cmake --build .