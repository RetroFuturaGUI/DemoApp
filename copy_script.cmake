#Copies what a program using the library needs beside it from SOURCE_DIR to DEST_DIR: the libraries, the decoder helper,
#their debug symbols, the shaders and the resources. Not the rest of the build folder (CMakeFiles, object files)
file(GLOB files_to_copy
    "${SOURCE_DIR}/*.dll"
    "${SOURCE_DIR}/*.so"
    "${SOURCE_DIR}/*.so.*"
    "${SOURCE_DIR}/*.pdb"
    "${SOURCE_DIR}/RetroFuturaGUIDecoder"
    "${SOURCE_DIR}/RetroFuturaGUIDecoder.exe")

file(MAKE_DIRECTORY "${DEST_DIR}")

if(files_to_copy)
    file(COPY ${files_to_copy} DESTINATION "${DEST_DIR}")
endif()

foreach(folder Resources ShaderSource)
    if(EXISTS "${SOURCE_DIR}/${folder}")
        file(COPY "${SOURCE_DIR}/${folder}" DESTINATION "${DEST_DIR}")
    endif()
endforeach()
