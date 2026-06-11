cmake_minimum_required(VERSION 3.15)
project(DungeonRPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_link_libraries(${PROJECT_NAME} PRIVATE winmm)

# === Static Linking for Release ===
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(MSVC)
        # MSVC:
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")
    else()
        # GCC:
        target_link_options(${PROJECT_NAME} PRIVATE -static -static-libgcc -static-libstdc++)
    endif()
endif()
# ====================================

# Copy assets after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Copying assets to build directory..."
)

# Release packaging
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION .)

set(CPACK_PACKAGE_NAME "DungeonRPG")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_GENERATOR "ZIP") 

set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/releases")

include(CPack)