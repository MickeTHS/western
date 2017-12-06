#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.1)
set (CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()


project(western)

if (UNIX)
  set (show_contents_prog cat)
elseif (WIN32)
  set (show_contents_prog type)
endif()

set(BUILD_NUMBER_FILE ${PROJECT_SOURCE_DIR}/buildnumber.txt)

MESSAGE("build number stored in " ${BUILD_NUMBER_FILE})

if(NOT EXISTS ${BUILD_NUMBER_FILE})
  MESSAGE(${BUILD_NUMBER_FILE})
  FILE( WRITE ${BUILD_NUMBER_FILE} "1" )
endif() 

#execute_process(COMMAND ${show_contents_prog} buildnumber.txt OUTPUT_VARIABLE BUILD_NUMBER)
FILE (READ ${BUILD_NUMBER_FILE} BUILD_NUMBER)
MATH(EXPR BUILD_NUMBER ${BUILD_NUMBER}+1)
FILE( WRITE ${BUILD_NUMBER_FILE} ${BUILD_NUMBER} )

# Set version information in a config.h file
set(western_VERSION_MAJOR 0)
set(western_VERSION_MINOR 1)
set(western_VERSION_PATCH ${BUILD_NUMBER})
configure_file(
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SOURCE_DIR}")

# Copy full directories
macro(resource_dirs dirs)
    foreach(dir ${dirs})
        # Replace / at the end of the path (copy dir content VS copy dir)
        string(REGEX REPLACE "/+$" "" dirclean "${dir}")
        message(STATUS "Copying resource ${dirclean}")
        file(COPY ${dirclean} DESTINATION ${CMAKE_BINARY_DIR}/bin)
    endforeach()
endmacro()

# Define sources and executable
set(EXECUTABLE_NAME "western")

set(SOURCE main.cpp 
        wst_animation.cpp 
        wst_input_action.cpp 
        wst_screenrenderobj.cpp 
        wst_player_character.cpp
        wst_ai_character.cpp
        wst_stat_character.cpp
        wst_quest_character.cpp
        wst_npc.cpp
        wst_staticobj.cpp
        wst_worldobj.cpp
        wst_worldlocation.cpp
        wst_scene.cpp
        wst_json_resource.cpp
        wst_main.cpp
        wst_asset_manager.cpp
        wst_environment.cpp
        json11.cpp)

if (WIN32)
    set(SOURCE
        ${SOURCE}
        wst_win32.cpp)
else ()
    set(SOURCE
        ${SOURCE}
        wst_unix.cpp)
endif ()

add_executable(${EXECUTABLE_NAME} ${SOURCE})

resource_dirs(${PROJECT_SOURCE_DIR}/../resources)

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)


# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION bin)


# CPack packaging
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_VERSION_MAJOR "${western_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${western_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${western_VERSION_PATCH}")
include(CPack)
