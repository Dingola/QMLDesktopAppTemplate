# CommonLib Integration
set(Third_Party_Target "CommonLib")
set(Git_Tag "main")
set(Project_Directory_Name "${Third_Party_Target}_${Git_Tag}")
set(Third_Party_Target_Directory "${THIRD_PARTY_INCLUDE_DIR}/${Project_Directory_Name}")
set(CMakeArgs "-D ${Third_Party_Target}_BUILD_TARGET_TYPE:STRING=static_library -D MAIN_PROJECT_NAME:STRING=CommonLib")
set(CommonLib_INCLUDE_DIR ${Third_Party_Target_Directory}/${Third_Party_Target}_install/include)
set(CommonLib_LIBRARY ${Third_Party_Target_Directory}/${Third_Party_Target}_install/lib/CommonLib.lib)
set(CommonLib_DIR "")

find_package(CommonLib HINTS ${Third_Party_Target_Directory}/${Third_Party_Target}_install/lib/cmake/CommonLib NO_DEFAULT_PATHS)

if(CommonLib_FOUND)
    message("CommonLib found")
else()
    message("CommonLib not found. Downloading and invoking cmake ..")
    build_third_party_project(
        false
        ${Third_Party_Target}
        https://github.com/Dingola/CommonLib.git
        ${Git_Tag}
        ${Third_Party_Target_Directory}
        ${CMAKE_BUILD_TYPE}
		${CMakeArgs}
    )
	
	find_package(CommonLib REQUIRED HINTS ${Third_Party_Target_Directory}/${Third_Party_Target}_install/lib/cmake/CommonLib NO_DEFAULT_PATHS)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE CommonLib)
