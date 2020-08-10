cmake_minimum_required(VERSION 3.15)

project(
  CppProject
  VERSION 0.1.0
  LANGUAGES CXX)

set(CMAKE_VERBOSE_MAKEFILE OFF)

site_name(HOSTNAME)

option(ENABLE_TESTING "Enable Test Builds" OFF)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(StandardProjectSettings)

# Link this 'library' to set the c++ standard / compile-time options requested
add_library(project_options INTERFACE)
target_compile_features(project_options INTERFACE cxx_std_17)

# Link this 'library' to use the warnings specified in CompilerWarnings.cmake
add_library(project_warnings INTERFACE)

# standard compiler warnings
include(CompilerWarnings)
set_project_warnings(project_warnings)

# sanitizer options if supported by compiler
include(Sanitizers)
enable_sanitizers(project_options)

# enable doxygen
include(Doxygen)
enable_doxygen()

# allow for static analysis options
include(StaticAnalyzers)
include(ProhibitInSourceBuild)
include(SetupNinjaColors)
include(SetupConan)
include(CodeCoverage)

add_subdirectory(src)

include(GNUInstallDirs)
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}Targets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  INCLUDES
  DESTINATION include
  PUBLIC_HEADER DESTINATION include)

install(
  EXPORT ${PROJECT_NAME}Targets
  FILE ${PROJECT_NAME}Targets.cmake
  NAMESPACE ${PROJECT_NAME}::
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/version.hpp.in
               include/${PROJECT_NAME_LOWERCASE}/version.hpp @ONLY)

install(
  FILES
    ${CMAKE_CURRENT_BINARY_DIR}/include/${PROJECT_NAME_LOWERCASE}/version.hpp
  DESTINATION include/${PROJECT_NAME_LOWERCASE})

#install(DIRECTORY include/${PROJECT_NAME_LOWERCASE} DESTINATION include)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${PROJECT_NAME}ConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion)

configure_package_config_file(
  ${CMAKE_CURRENT_LIST_DIR}/cmake/${PROJECT_NAME}Config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME})

if(ENABLE_TESTING)
  enable_testing()
  message("Building Unit Tests.")
  add_subdirectory(test)
endif()
