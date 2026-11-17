# >>> Roux: project. Rewritten on every Generate. Change Project.bechaml Instead!!1!
cmake_minimum_required(VERSION 3.16)
project("DemoApp" VERSION 0.1.0)
include("${CMAKE_CURRENT_SOURCE_DIR}/source/generated/Project.cmake")
# <<< Roux

message(STATUS "-- RetroFuturaGUI DemoApp CMake Configuration")
#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
message(STATUS "CMAKE_TOOLCHAIN_FILE: ${CMAKE_TOOLCHAIN_FILE}")

if(NOT DEFINED TARGETPLATFORM)
    if(WIN32)
        set(TARGETPLATFORM "x64-Windows" CACHE STRING "Target platform for the build")
    else()
        set(TARGETPLATFORM "x64-Linux" CACHE STRING "Target platform for the build")
    endif()
endif()

message(STATUS "-- Target Platform: ${TARGETPLATFORM}")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Before the targets on purpose: add_compile_options only reaches targets created after it.
# /utf-8 reads sources and writes narrow literals as UTF-8 - and it's what makes std::print hand
# text to the console as Unicode, instead of raw bytes the console decodes with the wrong code page.
if(MSVC)
    add_compile_options(/utf-8)
endif()

# >>> Roux: target. Rewritten on every Generate. The files come from source/code/ and source/generated/
if(ROUX_DYNLIB)
    add_library("DemoApp" SHARED ${ROUX_SOURCES})
    set_target_properties("DemoApp" PROPERTIES OUTPUT_NAME "DemoAppNative")
else()
    add_executable("DemoApp" ${ROUX_SOURCES})
    #<!--
    # MSVC only: sets the process codepage to UTF-8 so narrow paths work - see app.manifest.
    # Linux needs nothing; paths there are raw bytes the kernel never transcodes.
    if(MSVC)
        target_sources("DemoApp" PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/app.manifest")
    endif()
    #-->
endif()

target_include_directories("DemoApp" PRIVATE ${ROUX_INCLUDE_DIRECTORIES})
target_compile_options("DemoApp" PRIVATE ${ROUX_COMPILE_OPTIONS})
# <<< Roux

string(TOLOWER "${TARGETPLATFORM}" TARGETPLATFORM_LOWER)

if(TARGETPLATFORM_LOWER STREQUAL "x64-linux")
    target_compile_definitions(DemoApp PRIVATE TARGET_PLATFORM_LINUX)
elseif(TARGETPLATFORM_LOWER STREQUAL "x64-windows")
    target_compile_definitions(DemoApp PRIVATE
        TARGET_PLATFORM_WINDOWS
        WIN32 _WIN32 _WIN64
        UNICODE _UNICODE
        $<$<CONFIG:Debug>:_DEBUG>
        $<$<CONFIG:Release>:NDEBUG>
    )
else()
    message(WARNING "Unknown TARGETPLATFORM '${TARGETPLATFORM}'. clangd will not get platform-specific defines.")
endif()

# >>> Roux: library. Rewritten on every Generate.
# The same flags reach RetroFuturaGUI and what it builds, which set none of their own
add_compile_options(${ROUX_COMPILE_OPTIONS})
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI")
target_link_libraries("DemoApp" PRIVATE "RetroFuturaGUI")
# <<< Roux

# >>> Roux: assets. Rewritten on every Generate. The asset folders are listed in Project.bechaml.
# Copied on every build, after the program, so a changed asset or shader arrives even when the program isn't rebuilt
if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.26)
    set(ROUX_COPY_DIRECTORY copy_directory_if_different)
else()
    set(ROUX_COPY_DIRECTORY copy_directory)
endif()

add_custom_target("DemoAppAssets" ALL
    COMMAND ${CMAKE_COMMAND} -E ${ROUX_COPY_DIRECTORY}
        "${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI/source/Shaders/ShaderSource"
        "$<TARGET_FILE_DIR:DemoApp>/ShaderSource"
    COMMAND ${CMAKE_COMMAND} -E ${ROUX_COPY_DIRECTORY}
        "${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI/Resources"
        "$<TARGET_FILE_DIR:DemoApp>/Resources"
    COMMAND ${CMAKE_COMMAND} -E ${ROUX_COPY_DIRECTORY}
        "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
        "$<TARGET_FILE_DIR:DemoApp>/Assets"
    VERBATIM
)
add_dependencies("DemoAppAssets" "DemoApp")
# <<< Roux

if(LANG MATCHES "CSharp")
    add_custom_command(TARGET DemoApp
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI/Resources/Bindings/RetroFuturaGuiBinding.cs"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/code/CSharpProject/RetroFuturaGuiBinding.cs"
        COMMENT "Copying binding file"
    )

    add_custom_command(TARGET DemoApp POST_BUILD
        COMMAND dotnet build "${CMAKE_CURRENT_SOURCE_DIR}/source/code/CSharpProject/DemoApp.csproj" --configuration Debug
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source/code/CSharpProject"
        COMMENT "Building C# project after DLL..."
    )

    add_custom_command(TARGET DemoApp POST_BUILD
        COMMAND ${CMAKE_COMMAND}
                -DSOURCE_DIR="$<TARGET_FILE_DIR:DemoApp>" #where the library and the decoder helper land, with any generator
                -DDEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/source/code/CSharpProject/bin/${CMAKE_BUILD_TYPE}/net8.0"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/copy_script.cmake"
        COMMENT "Copying build output (including subfolders) to C# directory..."
    )
elseif(
LANG MATCHES "Rust")
        add_custom_command(TARGET DemoApp
        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI/Resources/Bindings/RetroFuturaGuiBinding.rs"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/code/RustProject/RetroFuturaGuiBinding.rs"
        COMMENT "Copying binding file"
    )

    add_custom_command(TARGET DemoApp POST_BUILD
        COMMAND cargo build --manifest-path "${CMAKE_CURRENT_SOURCE_DIR}/source/code/RustProject/Cargo.toml" --debug
        WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/source/code/RustProject"
        COMMENT "Building Rust project after DLL..."
)
elseif(LANG MATCHES "Python")
    add_custom_command(TARGET DemoApp POST_BUILD
        COMMAND ${CMAKE_COMMAND}
                -DSOURCE_DIR="$<TARGET_FILE_DIR:DemoApp>" #where the library and the decoder helper land, with any generator
                -DDEST_DIR="${CMAKE_CURRENT_SOURCE_DIR}/source/code/Python"
                -P "${CMAKE_CURRENT_SOURCE_DIR}/copy_script.cmake"
        COMMENT "Copying build output (including subfolders) to Python directory..."

        COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_CURRENT_SOURCE_DIR}/RetroFuturaGUI/Resources/Bindings/RetroFuturaGuiBinding.py"
        "${CMAKE_CURRENT_SOURCE_DIR}/source/code/Python/RetroFuturaGuiBinding.py"
    )
endif()