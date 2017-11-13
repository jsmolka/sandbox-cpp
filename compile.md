# Compile
This file contains some more or less important linker and cmake options used to compile programs.

## GCC / G++

### Flags
- ```-static``` switches the compiler linking to static
- ```-mwindows``` removes console
- ```-O3``` enables heavy code optimization

### Libraries
- ```-static-libstdc++``` standard C++ library
- ```-static-libgcc``` standard C library
- ```-lpthread``` winpthread library

### Statically link standard library
- ```-static-libstdc++ -static-libgcc -static -lpthread```

## CMake

### Functions
- ```set(CMAKE_EXE_LINKER_FLAGS "...")``` adds compiler flags
- ```target_link_libraries(project ...)``` adds libraries to the project
- ```add_definitions(...)``` adds preprocessor definitions

### Statically link standard library
- ```set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static -lwinpthread")```

### Statically link SFML
- ```add_definitions(-DSFML_STATIC)``` adds preprocessor definition
- ```target_link_libraries(project ... opengl32 winmm gdi32 jpeg freetype)``` links static libraries needed for graphics, window and system
