cmake_minimum_required(VERSION 3.19.0 FATAL_ERROR)

############################################
### Project Configuration                ###
############################################

get_filename_component(current_source_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)

project(${current_source_dir_name} LANGUAGES CXX VERSION "0.0.0")
configure_file(Config.h.in Config.h)

# Include CMake helper scripts
include(${CMAKE_SOURCE_DIR}/CMake/SourceGroups.cmake)
include(${CMAKE_SOURCE_DIR}/CMake/BuildThirdPartyProject.cmake)

############################################
### Global Properties                    ###
############################################

# Global properties for project organization
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})

# Include current directory
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Export all symbols for Windows
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

# Add linker flags
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ldwmapi")

############################################
### Documentation Configuration          ###
############################################

# Set the documentation sub-target name
set(doc_sub_target_name ${main_project_name})

############################################
### Setup Project File Includes          ###
############################################

file(GLOB_RECURSE Headers
     "Headers/*.h"
     "Headers/*/*.h"
)

file(GLOB_RECURSE Sources
     "main.cpp"
     "Sources/*.cpp"
     "Headers/QT/*/*.cpp"
     "Sources/QT/*.cpp"
     "Sources/QML/*.qml"
)

include_directories(Headers Sources)

############################################
### Qt6 Configuration                    ###
############################################

if ("$ENV{qt6_path}" STREQUAL "")
	set(qt6_path "E:\\Qt6\\6.3.1\\msvc2019_64\\")
else()
	set(qt6_path "$ENV{qt6_path}")
endif()

if (EXISTS ${qt6_path})
	set(CMAKE_PREFIX_PATH ${qt6_path})
else()
	message(WARNING "The specified qt6 path '${qt6_path}' does not exist")
endif()

find_package(Qt6 REQUIRED COMPONENTS Widgets Qml Quick QuickControls2 Gui)
qt_standard_project_setup()
qt6_add_resources(RSCS resources.qrc)
add_custom_target(gen_qrc DEPENDS ${RSCS})

############################################
### Setup Target Build Type              ###
############################################

if (${main_project_name}_BUILD_TARGET_TYPE STREQUAL executable)
	add_executable(${PROJECT_NAME})
elseif (${main_project_name}_BUILD_TARGET_TYPE STREQUAL dynamic_library)
	add_library(${PROJECT_NAME} SHARED)
elseif (${main_project_name}_BUILD_TARGET_TYPE STREQUAL static_library)
	add_library(${PROJECT_NAME})
else()
	message(FATAL_ERROR "Build type not specified")
endif()

target_link_libraries(${main_project_name} PRIVATE Qt6::Widgets Qt6::Gui Qt6::Qml Qt6::Quick Qt6::QuickControls2 dwmapi)
include(${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/Doxygen.cmake)

set_target_properties(${PROJECT_NAME} PROPERTIES 
	LINK_FLAGS /SUBSYSTEM:CONSOLE
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_sources(${PROJECT_NAME}
    PRIVATE
		${Headers}
        ${Sources}
		${RSCS}
)

# windeployqt takes an .exe file or a directory that contains an .exe file 
# as an argument, and scans the executable for dependencies
#
# Link: https://doc.qt.io/qt-6/windows-deployment.html
#
if (${main_project_name}_BUILD_TARGET_TYPE STREQUAL executable)
	# Retrieve the absolute path to qmake and then use that path to find
	# the windeployqt executable
	get_target_property(QMAKE_EXE Qt6::qmake IMPORTED_LOCATION)
	get_filename_component(QT_BIN_DIR "${QMAKE_EXE}" DIRECTORY)

	find_program(WINDEPLOYQT_ENV_SETUP qtenv2.bat HINTS "${QT_BIN_DIR}")
	find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_BIN_DIR}")

	# Run windeployqt immediately after build
	add_custom_command(TARGET ${PROJECT_NAME}
		POST_BUILD
		COMMAND "${WINDEPLOYQT_ENV_SETUP}" && "${WINDEPLOYQT_EXECUTABLE}" \"$<TARGET_FILE:${PROJECT_NAME}>\" "--qmldir=D:\\Projects\\VS_Projects\\QMLDesktopAppTemplate\\QMLDesktopAppTemplate\\Sources\\QML"
		COMMENT "Running windeployqt..."
	)
	
	# Run windeployqt immediately after build
	#add_custom_command(TARGET ${PROJECT_NAME}
	#	POST_BUILD
	#	COMMAND "${WINDEPLOYQT_ENV_SETUP}" && "${WINDEPLOYQT_EXECUTABLE}" \"$<TARGET_FILE:${PROJECT_NAME}>\" "--qmldir=D:\\Projects\\VS_Projects\\QMLDesktopAppTemplate\\QMLDesktopAppTemplate\\Style"
	#	COMMENT "Running windeployqt..."
	#)
endif()

############################################
### Setup source groups                  ###
############################################

group_files("${Sources}" "Source Files")
group_files("${Headers}" "Header Files")

# Specifies include directories to use when compiling a given target
set(include_dirs "${CMAKE_CURRENT_LIST_DIR} ${PROJECT_BINARY_DIR}")
target_include_directories(${PROJECT_NAME} PUBLIC 
	$<BUILD_INTERFACE:${include_dirs}>
	$<INSTALL_INTERFACE:include> 
)

############################################
### Install rules                        ###
############################################

include(CMake/install.cmake)
