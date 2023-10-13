## Prerequisites
N.B.: This softwre will not build without satisfying the prerequisites.

- Eigen: 3.4.0 (local source)
- GoogleTest: 1.1.4.0 (local source)
- VTK: 9.3.0.rc1 (build locally)
- CMake: v3.14

To retrieve Eigen and GoogleTest, execute `make check_libs`.

### VTK
VTK will need to be built locally, as a library to be included. This is relatively straightforward, but may seem very complex to first timers. Stick with it.

Instructions for building: https://docs.vtk.org/en/latest/build_instructions/index.html

Note that the least documented aspect is the configuration of the build using `ccmake`. You will need to repeat the configuration using `c`, until the generate, `g`, option becomes available. Execute generate. With this step complete, you can then build vtk. Please note that you are building specific versions of vtk. I.e., with debugging or without, etc.

Once you've completed the build, you will need to provide a path to your vtk build. This must be done in a `config.cmake`. You must construct this file.

### Mandatory Configuration: config.cmake
You must create a config.cmake. An example of a `config.cmake`:
```
# Set path to the vtk build location to be used
set(VTK_DIR "/home/<username>/vtk/build")
```
In this case, the vtk build is located at `/home/<username>/vtk/build`, where username was my personal username.