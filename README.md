# DemoApp

A project to test and help develope RetroFuturaGUI.

Check out the repository recursively (`git clone --recursive`, or `git submodule update --init --recursive` afterwards).

## Building with Roux

Roux (the `Roux/` submodule) checks the tools, generates the CMake files and builds. It needs Node 22 or newer:

```
cd Roux
npm install
npm run serve
```

This opens Roux in the browser. Setup checks the tools; the Build tab runs Generate, Configure, Build and Run for the
platform and build type chosen there, in `build/<Platform>-<BuildType>`.

`node Roux/cli/out/main.js generate` (from the project folder) only generates, from `Project.bechaml` and the .bechaml
files in `source/code/`:
- `source/generated/Project.cmake` and the regions in `CMakeLists.txt` marked `# >>> Roux: <name>` … `# <<< Roux`. Lines
  outside the regions are the project's own and stay as they are; inside a region, only lines between `#<!--` and `#-->`
  are kept.
- The scenes and windows in `source/generated/impl/`, and the start function `main.cpp` calls.

## The test app

One window, `MainWindow`, with a title bar (title, drag, minimize, maximize, close) and a main menu whose buttons load a
scene: ColorfulPop, and the Note scene with its text effects and sample texts. Each has a Back button in the bottom right.
- **Markup:** `source/code/Windows/MainWindow.bechaml`, `source/code/Scenes/*.bechaml`.
- **Your code:** the classes next to them (slots, and in `MainWindow.cpp` the character sets until App Settings are
  generated) and `source/code/main.cpp`.
- **The old hand-written app** is in `backup/`, which git ignores.

## Building by hand

Run Generate first whenever `Project.bechaml` changed. On Windows, run CMake from the Visual Studio developer
environment (`vcvars64.bat`), or the compiler can't find its headers and libraries.

Windows:

```
cmake -S . -B build/Windows-Debug -G Ninja -DCMAKE_TOOLCHAIN_FILE="$env:VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DTARGETPLATFORM=x64-windows -DROUX_PLATFORM=Windows -DCMAKE_BUILD_TYPE=Debug
cmake --build build/Windows-Debug
build/Windows-Debug/DemoApp.exe
```

Linux:

```
cmake -S . -B build/Linux-Debug -G Ninja -DCMAKE_TOOLCHAIN_FILE="$VCPKG_ROOT/scripts/buildsystems/vcpkg.cmake" -DVCPKG_TARGET_TRIPLET=x64-linux -DTARGETPLATFORM=x64-linux -DROUX_PLATFORM=Linux -DCMAKE_BUILD_TYPE=Debug
cmake --build build/Linux-Debug
./build/Linux-Debug/DemoApp
```

For a release build, use `Release` in the folder name and in `-DCMAKE_BUILD_TYPE`.

## The shared library for C#, Python and Rust

`-DLANG=<LANG>` no longer picks it. Set the platform's language in `Project.bechaml` (Roux's Project tab) to C#, Python
or Rust and run Generate: the build then makes the shared library `DemoAppNative` and runs the language's steps at
the end of `CMakeLists.txt` (copying the binding file and the build output into `source/code/CSharpProject`,
`source/code/RustProject` or `source/code/Python`).
