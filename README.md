# DemoApp

A project to test, help, develope, and demonstrate RetroFuturaGUI.

Check out the repository recursively (`git clone --recursive`, or `git submodule update --init --recursive` afterwards).

## Building with Roux

Roux (the `Roux/` submodule) checks the tools, generates the CMake files and builds. It needs Node 22 or newer:

```
cd Roux
npm install
npm run serve
```

This opens Roux in the browser. Setup checks the tools. The Build tab runs Generate, Configure, Build and Run for the
platform and build type chosen there, in `build/<Platform>-<BuildType>`.

`node Roux/cli/out/main.js generate` (from the project folder) only generates, from `Project.bechaml` and the .bechaml
files in `source/code/`:
- `source/generated/Project.cmake` and the regions in `CMakeLists.txt` marked `# >>> Roux: <name>` … `# <<< Roux`. Lines
  outside the regions are the project's own and stay as they are; inside a region, only lines between `#<!--` and `#-->`
  are kept.
- The scenes and windows in `source/generated/impl/`, and the start function `main.cpp` calls.

You can install Roux as a VS Code extension by installing `Roux/dist/roux-vscpde-<version>.vsix` or install it as a Jetbrains plugin by installing `Roux/dist/roux-jetbrains-<version>.zip`.

## The test app

One window, ***MainWindow***, with a title bar (title, drag, minimize, maximize, close) and a main menu whose buttons load a
scene:
- ***Colorful Pop*** (a window featuring the [*Colorful Pop* aesthetic](https://aesthetics.fandom.com/wiki/Colorful_Pop))
- ***Note***: A scene to tst text flow direction, unicode coverage and text styling effects.
- ***Y2K Futurism***: A Scene featuring the [*Y2K Futurism* aesthetic](https://aesthetics.fandom.com/wiki/Y2K_Futurism) (WIP).
- **Markup:** `source/code/Windows/MainWindow.bechaml`, `source/code/Scenes/*.bechaml`.


## Building by hand

Run ***Generate*** first whenever `Project.bechaml` changed. On Windows, run CMake from the Visual Studio developer
environment (`vcvars64.bat`), or the compiler can't find its headers and libraries.

Windows:

```
cmake -S . -B build/Windows-Debug -G Ninja -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DTARGETPLATFORM=x64-windows -DROUX_PLATFORM=Windows -DCMAKE_BUILD_TYPE=Debug
cmake --build build/Windows-Debug
build/Windows-Debug/DemoApp.exe
```

Linux:

(implementation might be slightly behind)

```
cmake -S . -B build/Linux-Debug -G Ninja -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-linux -DTARGETPLATFORM=x64-linux -DROUX_PLATFORM=Linux -DCMAKE_BUILD_TYPE=Debug
cmake --build build/Linux-Debug
./build/Linux-Debug/DemoApp
```

For a release build, use `Release` in the folder name and in `-DCMAKE_BUILD_TYPE`.

## The shared library for C#, Python and Rust

Set the platform's language in `Project.bechaml` (Roux's Project tab) to C#, Python or Rust and run Generate: the build then makes the shared library `DemoAppNative` and runs the language's steps at
the end of `CMakeLists.txt` (copying the binding file and the build output into `source/code/CSharpProject`,
`source/code/RustProject` or `source/code/Python`).
