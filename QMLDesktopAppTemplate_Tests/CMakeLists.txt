cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

############################################
### Setup project                        ###
############################################

get_filename_component(current_source_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${current_source_dir_name} LANGUAGES CXX VERSION "0.0.0")

# Include CMake helper scripts
include(${CMAKE_SOURCE_DIR}/CMake/SourceGroups.cmake)
include(${CMAKE_SOURCE_DIR}/CMake/BuildThirdPartyProject.cmake)

############################################
### Global Properties                    ###
############################################

# Global properties for project organization
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Include current directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)

############################################
### Documentation Configuration          ###
############################################

# Set the documentation sub-target name
set(doc_sub_target_name ${PROJECT_NAME})

############################################
### Setup Project File Includes          ###
############################################

file(GLOB_RECURSE Headers
     "Headers/*.h"
)
file(GLOB_RECURSE Sources
     "main.cpp"
	 "Sources/*.cpp"
)

include_directories(Headers Sources)

############################################
### Qt6 Configuration                    ###
############################################

if ("$ENV{qt6_path}" STREQUAL "")
	set(qt6_path "E:\\Qt\\6.8.0\\msvc2022_64\\")
else()
	set(qt6_path "$ENV{qt6_path}")
endif()

if (EXISTS ${qt6_path})
	set(CMAKE_PREFIX_PATH ${qt6_path})
else()
	message(WARNING "The specified qt6 path '${qt6_path}' does not exist")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets Qml Quick QuickControls2 Gui LinguistTools)
qt_standard_project_setup()
#qt6_add_resources(RSCS resources.qrc)
#add_custom_target(gen_qrc DEPENDS ${RSCS})

############################################
### Configuration Information            ###
############################################

message(STATUS "###############################################################")
message(STATUS "###          Configuration Information")
message(STATUS "###          Project: ${PROJECT_NAME}")
message(STATUS "###############################################################")
message(STATUS "")
message(STATUS "  CMake Version:                ${CMAKE_VERSION}")
message(STATUS "  CMake Prefix Path:            ${CMAKE_PREFIX_PATH}")
message(STATUS "  CMake Install Prefix Path:    ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  Host System Name:             ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "  Host System Version:          ${CMAKE_HOST_SYSTEM_VERSION}")
message(STATUS "  Target System Name:           ${CMAKE_SYSTEM_NAME}")
message(STATUS "  Target System Version:        ${CMAKE_SYSTEM_VERSION}")
message(STATUS "  Source Directory:             ${CMAKE_SOURCE_DIR}")
message(STATUS "  Build Type:                   ${CMAKE_BUILD_TYPE}")
message(STATUS "  Toolchain File:               ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS "  C++ Compiler:                 ${CMAKE_CXX_COMPILER}")
message(STATUS "  C Compiler:                   ${CMAKE_C_COMPILER}")
message(STATUS "  Build Tool:                   ${CMAKE_BUILD_TOOL}")
message(STATUS "  Module Path:                  ${CMAKE_MODULE_PATH}")
message(STATUS "  Binary Directory:             ${CMAKE_BINARY_DIR}")
message(STATUS "  Current Source Directory:     ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "  Current Binary Directory:     ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "")
message(STATUS "-----------------------------------------------")
message(STATUS "")
message(STATUS "  Third Party Include Directory:            ${THIRD_PARTY_INCLUDE_DIR}")
message(STATUS "  ${doc_sub_target_name}_BUILD_DOC:          ${${doc_sub_target_name}_BUILD_DOC}")
message(STATUS "  Qt6 Directory (qt6_path env):             ${qt6_path}")
message(STATUS "")
message(STATUS "-----------------------------------------------")
message(STATUS "")
message(STATUS "###############################################################")

############################################
### Setup executable build               ###
############################################

add_executable(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2)
include(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Doxygen.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/GoogleTest.cmake)

if (WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        LINK_FLAGS "/SUBSYSTEM:CONSOLE"
        WIN32_EXECUTABLE ON
    )
elseif (APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES 
        MACOSX_BUNDLE ON
    )
endif()
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_sources(${PROJECT_NAME}
    PRIVATE
		${Headers}
		${Sources}
)

if (WIN32)
	# Retrieve the absolute path to qmake and then use that path to find
	# the windeployqt executable
	get_target_property(QMAKE_EXE Qt6::qmake IMPORTED_LOCATION)
	get_filename_component(QT_BIN_DIR "${QMAKE_EXE}" DIRECTORY)

	find_program(WINDEPLOYQT_ENV_SETUP qtenv2.bat HINTS "${QT_BIN_DIR}")
	find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_BIN_DIR}")

	# Run windeployqt immediately after build
	add_custom_command(TARGET ${PROJECT_NAME}
		POST_BUILD
		COMMAND "${WINDEPLOYQT_ENV_SETUP}" && "${WINDEPLOYQT_EXECUTABLE}" \"$<TARGET_FILE:${PROJECT_NAME}>\"
	)
endif()

############################################
### Setup source groups                  ###
############################################

GROUP_FILES("${Sources}" "Source Files")
GROUP_FILES("${Headers}" "Header Files")

# Specifies include libraries
target_link_libraries(${PROJECT_NAME} PUBLIC ${main_project_name})

# Specifies include directories to use when compiling a given target
target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_LIST_DIR} 
	${CMAKE_SOURCE_DIR}/${main_project_name}/Headers)
