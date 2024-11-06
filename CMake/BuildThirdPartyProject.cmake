
function (build_third_party_project Dont_Update_Build Target Git_Repo Git_Tag Third_Party_Project_Directory)
	# Create content of the CMakeLists which is used for downloading and building the third party lib
	set(CMakeList_Content "
cmake_minimum_required(VERSION ${CMAKE_MINIMUM_REQUIRED_VERSION})
project(${Target}_download)

include(ExternalProject)
ExternalProject_Add(${Target}
	GIT_REPOSITORY           ${Git_Repo}
	GIT_TAG                  ${Git_Tag}
	SOURCE_DIR		         \"${Third_Party_Project_Directory}/${Target}_src\"
	BINARY_DIR               \"${Third_Party_Project_Directory}/${Target}_build\"
	INSTALL_DIR              \"${Third_Party_Project_Directory}/${Target}_install/${CMAKE_BUILD_TYPE}\"
	CMAKE_GENERATOR          \"${CMAKE_GENERATOR}\"
	CMAKE_GENERATOR_PLATFORM \"${CMAKE_GENERATOR_PLATFORM}\"
	CMAKE_GENERATOR_TOOLSET  \"${CMAKE_GENERATOR_TOOLSET}\"
	CMAKE_GENERATOR_INSTANCE \"${CMAKE_GENERATOR_INSTANCE}\"
	UPDATE_DISCONNECTED ${Dont_Update_Build}
	CMAKE_ARGS
		-DCMAKE_INSTALL_PREFIX:PATH=${Third_Party_Project_Directory}/${Target}_install/
		-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
		${ARGN}
)
	")

	# Create download directory and copy CMakeList_Content to a CMakeLists.txt file
	set(Target_Download_Directory "${Third_Party_Project_Directory}/${Target}_download")
	file(MAKE_DIRECTORY ${Target_Download_Directory})
	file(WRITE "${Target_Download_Directory}/CMakeLists.txt" "${CMakeList_Content}")
	
	# Configure and build of the third party lib
	execute_process(COMMAND ${CMAKE_COMMAND}
		-G "${CMAKE_GENERATOR}"
		-A "${CMAKE_GENERATOR_PLATFORM}"
		-T "${CMAKE_GENERATOR_TOOLSET}"
		.
		WORKING_DIRECTORY "${Target_Download_Directory}"
	)
	
	execute_process(COMMAND ${CMAKE_COMMAND}
		--build .
		--config ${CMAKE_BUILD_TYPE}
		WORKING_DIRECTORY "${Target_Download_Directory}"
	)
endfunction()
