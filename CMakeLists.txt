cmake_minimum_required(VERSION 3.15)
project(DungeonRPG LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML (Standard dynamic linking mode)
find_package(SFML 3 COMPONENTS Graphics Window System Audio CONFIG)

if(NOT SFML_FOUND)
    message(STATUS "SFML 3 not found locally. Fetching from GitHub...")
    include(FetchContent)
    FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com
        GIT_TAG        3.0.2
    )
    set(SFML_BUILD_EXAMPLES OFF CACHE INTERNAL "")
    set(SFML_BUILD_DOC OFF CACHE INTERNAL "")
    
    FetchContent_MakeAvailable(SFML)
endif()


file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")

# === Linking and flags for Release builds ===
if(NOT CMAKE_BUILD_TYPE STREQUAL "Debug")
    if(MSVC)
        set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")
    elseif(WIN32)
        # Hide the console window for the Windows Release build
        target_link_options(${PROJECT_NAME} PRIVATE -mwindows)
    endif()
endif()

# Standard dynamic linking against SFML targets
target_link_libraries(${PROJECT_NAME} PRIVATE SFML::Graphics SFML::Window SFML::System SFML::Audio)

# Copy assets to the build directory after compilation (for local testing)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/assets"
    "$<TARGET_FILE_DIR:${PROJECT_NAME}>/assets"
    COMMENT "Copying assets to build directory..."
)

# === Package Deployment via CPack ===

# 1. Install the executable and the assets folder into the archive root
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION .)
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets" DESTINATION .)

# 2. Robust Custom Deployment for MSYS2/MinGW Dependencies
if(WIN32 AND NOT MSVC)
    # Get absolute Windows path to current MSYS2 binary folder (e.g., C:/msys64/mingw64/bin)
    get_filename_component(MINGW_BIN_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)

    install(CODE "
        # Run ldd to scan the executable
        execute_process(
            COMMAND ldd \$<TARGET_FILE:${PROJECT_NAME}>
            OUTPUT_VARIABLE LDD_OUTPUT
        )
        
        string(REPLACE \"\\n\" \";\" LDD_LINES \"\${LDD_OUTPUT}\")
        foreach(LINE \${LDD_LINES})
            if(LINE MATCHES \"=> ([^ ]+)\")
                set(DLL_PATH \"\${CMAKE_MATCH_1}\")
                
                # Extract just the file name (e.g., sfml-window-3.dll)
                get_filename_component(DLL_NAME \"\${DLL_PATH}\" NAME)
                
                # FIXED FILTER: Strictly ignore only Microsoft System32 / SysWOW64 / Windows folders
                string(TOLOWER \"\${DLL_PATH}\" DLL_PATH_LOWER)
                if(NOT DLL_PATH_LOWER MATCHES \"system32\" AND NOT DLL_PATH_LOWER MATCHES \"syswow64\" AND NOT DLL_PATH_LOWER MATCHES \"c:/windows\")
                    
                    # Force resolve path using the actual compiler directory
                    set(RESOLVED_PATH \"${MINGW_BIN_DIR}/\${DLL_NAME}\")
                    
                    if(EXISTS \"\${RESOLVED_PATH}\")
                        message(STATUS \"Deploying dependency: \${RESOLVED_PATH}\")
                        file(INSTALL DESTINATION \"\${CMAKE_INSTALL_PREFIX}/.\" TYPE FILE FILES \"\${RESOLVED_PATH}\")
                    endif()
                endif()
            endif()
        endforeach()
    ")
endif()

# CPack configuration
set(CPACK_PACKAGE_NAME "DungeonRPG")
set(CPACK_PACKAGE_VERSION "2.0.0")
set(CPACK_GENERATOR "ZIP") 
set(CPACK_PACKAGE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/releases")

include(CPack)
