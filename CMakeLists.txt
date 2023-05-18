cmake_minimum_required(VERSION 3.21)

project(3DRasterizer)

# SETUP VARIABLES:

# list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/build/modules)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_PATH ${PROJECT_SOURCE_DIR}/include)
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${OUTPUT_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${OUTPUT_DIR}")


# SETUP SDL2

# NOTE: Folders here contain both SDL2 and SDL2_image files.
set(SDL2_LIB_DIR        ./libraries/SDL32/lib)
set(SDL2_INCLUDE_DIR    ./libraries/SDL32/include)
set(SDL2_LIBRARY        ./libraries/SDL32/bin)

# SETUP INCLUDE AND LINK DIRS:


include_directories(
    ${SDL2_INCLUDE_DIR}
    ${PROJECT_SOURCE_DIR}/include
)

link_directories(
    ${SDL2_LIB_DIR}
)


# INCLUDE FILES THAT SHOULD BE COMPILED:

AUX_SOURCE_DIRECTORY(src/                   D_MAIN)
AUX_SOURCE_DIRECTORY(src/Engine/            D_ENGINE)
AUX_SOURCE_DIRECTORY(src/Engine/core        D_CORE)
AUX_SOURCE_DIRECTORY(src/Engine/rendering   D_RENDERING)
AUX_SOURCE_DIRECTORY(src/Engine/resources   D_RESOURCES)

# message(STATUS "Add source files:")
# foreach(SRC_FILE IN LISTS SRC)
#     message(STATUS "${SRC_FILE}")
# endforeach()
# message(STATUS "")

add_executable(${PROJECT_NAME} ${D_CORE} ${D_RESOURCES} ${D_RENDERING} ${D_ENGINE} ${D_MAIN})


# LINK PROGRAM

target_link_libraries(
    ${PROJECT_NAME}
        mingw32
        SDL2main
        SDL2
        SDL2_image
)


# COPY OVER STATIC FILES

message(STATUS "Copying all assets to destination folder...")
file(
    COPY assets
    DESTINATION ${OUTPUT_DIR}
)

message(STATUS "Copying all dependencies to destination folder...")
file(GLOB PROJECT_DEPENDENCIES ${SDL2_LIBRARY}/*.dll)

foreach(Dependency IN LISTS PROJECT_DEPENDENCIES)
    file(
        COPY ${Dependency}
        DESTINATION ${OUTPUT_DIR}
    )
endforeach()