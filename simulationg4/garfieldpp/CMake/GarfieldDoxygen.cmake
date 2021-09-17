find_package(Doxygen)
if(DOXYGEN_FOUND)
  configure_file(${CMAKE_SOURCE_DIR}/Doc/Doxyfile.in
                 ${CMAKE_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc
                    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Generating API documentation with Doxygen" VERBATIM)

  install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doxygen/
    DESTINATION ${CMAKE_INSTALL_DOCDIR}/doxygen
    OPTIONAL)
else()
  message(WARNING "Doxygen was not found. Documention target 'doc' not defined.")
endif()
