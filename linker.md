# Linker
This file contains some more or less important linker options.

### Linker flags
- ```-static-libstdc++``` links C++ standard library statically
- ```-static-libgcc``` links C standard library statically
- ```-static``` switches the compiler linking to static
- ```-lpthread``` links winpthread library dynamically

### Statically link standard library
- ```-static-libstdc++ -static-libgcc -static -lpthread```
- ```-static -lstdc++ -lwinpthread```

### Statically link standard library in CMake
- ```set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static -lwinpthread")```
- ```set(CMAKE_EXE_LINKER_FLAGS "-static -lstdc++ -lwinpthread")```
