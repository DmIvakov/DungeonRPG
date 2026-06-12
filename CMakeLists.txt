cmake_minimum_required(VERSION 3.15)
project(DungeonRPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
set(SFML_STATIC_LIBRARIES TRUE) 
find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

file(GLOB_RECURSE SOURCES "src/main.cpp")
# file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# SFML static linking
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)

# === Static Linking for Release builds ===
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(MSVC)
        # MSVC Windows (Visual Studio)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    elseif(WIN32)
        # MSYS2/MinGW Windows
        target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++ -mwindows)
    else()
        # Linux/macOS
        target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
    endif()
endif()
# ===============================================

# Copy assets after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Copying assets to build directory..."
)

# Release package
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION .)

set(CPACK_PACKAGE_NAME "DungeonRPG")
set(CPACK_PACKAGE_VERSION "2.0.0")
set(CPACK_GENERATOR "ZIP") 
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/releases")

include(CPack)