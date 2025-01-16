set(build_doc ${doc_sub_target_name}_BUILD_DOC)
option(${build_doc} "Build documentation (${doc_sub_target_name})" OFF)

if (${build_doc})
	find_package(Doxygen)

	if (DOXYGEN_FOUND)
		# set input and output files
		set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/Doxyfile.in)
		set(DOXYGEN_OUT ${CMAKE_CURRENT_SOURCE_DIR}/Docs/Doxyfile)

		# request to configure the file
		configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
		message("Doxygen build started for ${doc_sub_target_name}")

		# note the option ALL which allows to build the docs together with the application
		add_custom_target(Doc_Doxygen_${doc_sub_target_name} ALL
			COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
			WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
			COMMENT "Generating API documentation with Doxygen"
			VERBATIM)
	else(DOXYGEN_FOUND)
	  message("Doxygen need to be installed to generate the doxygen documentation")
	endif(DOXYGEN_FOUND)
	
endif(${build_doc})
