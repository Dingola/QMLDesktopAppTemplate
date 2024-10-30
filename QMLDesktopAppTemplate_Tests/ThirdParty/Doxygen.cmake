set(Build_Doc ${Doc_Sub_Target_Name}_BUILD_DOC)
option(${Build_Doc} "Build documentation (${Doc_Sub_Target_Name})" OFF)

if (${Build_Doc})
	find_package(Doxygen)

	if (DOXYGEN_FOUND)
		# set input and output files
		set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/Doxyfile.in)
		set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile)

		# request to configure the file
		configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
		message("Doxygen build started for ${Doc_Sub_Target_Name}")

		# note the option ALL which allows to build the docs together with the application
		add_custom_target(Doc_Doxygen_${Doc_Sub_Target_Name} ALL
			COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Generating API documentation with Doxygen"
			VERBATIM)
	else(DOXYGEN_FOUND)
	  message("Doxygen need to be installed to generate the doxygen documentation")
	endif(DOXYGEN_FOUND)
	
endif(${Build_Doc})
