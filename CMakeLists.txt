cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

############################################
### Project Configuration                ###
############################################

set(main_project_name "QMLDesktopAppTemplate")
project(${main_project_name}_Solution LANGUAGES CXX)

# Suppress specific compiler warnings
add_definitions("/wd4114")

############################################
### Build Options                        ###
############################################

# Set the build type for the target project
set(${main_project_name}_BUILD_TARGET_TYPE "executable" CACHE STRING "Build target options")
set_property(CACHE ${main_project_name}_BUILD_TARGET_TYPE PROPERTY STRINGS executable dynamic_library static_library)

# Option to build the test project
option(${main_project_name}_BUILD_TEST_PROJECT "Build test project" OFF)

# Path to ThirdParty directories
if (WIN32)
    set(DEFAULT_THIRD_PARTY_PATH "$ENV{USERPROFILE}/ThirdParty")
else()
    set(DEFAULT_THIRD_PARTY_PATH "$ENV{HOME}/ThirdParty")
endif()
set(THIRD_PARTY_INCLUDE_DIR ${DEFAULT_THIRD_PARTY_PATH} CACHE PATH "Third Party Directory")

############################################
### Global Properties                    ###
############################################

# Global properties for project organization
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${main_project_name})

# Include current directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)

############################################
### Build Type Configuration             ###
############################################

# Set the build type if not set
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel.")
endif()

############################################
### Subdirectories                       ###
############################################

# Add the main project
add_subdirectory(${main_project_name})

# Add the test project conditionally
if (${main_project_name}_BUILD_TEST_PROJECT)
  add_subdirectory(${main_project_name}_Tests)
endif()
