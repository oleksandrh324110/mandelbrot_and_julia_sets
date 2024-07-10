# Mandelbrot and Julia Sets

## Cloning the Repository

To clone the repository with all submodules, use:

```bash
git clone git@github.com:oleksandrh324110/opengl-learn.git --recursive && cd opengl-learn
# or
git clone https://github.com/oleksandrh324110/opengl-learn.git --recursive && cd opengl-learn
```

If you forgot to use `--recursive`, you can initialize and update the submodules later:

```bash
git submodule init
git submodule update
```

## Building and Running

To build and run the project, follow these steps:

1. Create a build directory and navigate into it:

   ```bash
   mkdir build && cd build
   ```

2. Generate the build files using CMake:

   ```bash
   cmake ..
   ```

3. Compile the project using `make`:

   ```bash
   make -j12
   ```

   `-j12` is used to compile the project on more than one core

4. Run the executable:

   ```bash
   ./main
   ```
