cmake_minimum_required(VERSION 3.8)

####################
#       BASIS      #
####################

# Name of the project
project(NEURACOM VERSION 1.0.0 LANGUAGES CXX)


####################
#      OPTIONS     #
####################

# Set it by adding "cmake -DNEURACOM_BUILD_SHARED_LIBS=[ON|OFF] [...]"
option(NEURACOM_BUILD_SHARED_LIBS
  "Build Neuracom shared library"
  ${BUILD_SHARED_LIBS})

# By default, set the lib to "static", except if the user chose the option "shared"
set(neuracom-type STATIC)
if (NEURACOM_BUILD_SHARED_LIBS)
  set(neuracom-type SHARED)
endif()


####################
#      SOURCES     #
####################

# Set the source files
set(src-pattern "src/*.cpp")
if (CMAKE_VERSION VERSION_GREATER 3.12)
  list(INSERT src-pattern 0 CONFIGURE_DEPENDS)
endif()

file(GLOB neuracom-sources ${src-pattern})


####################
#    COMPILATION   #
####################

# Add and compile the library
add_library(neuracom ${neuracom-type} "")
# Add an alias
add_library(Neuratio::neuracom ALIAS neuracom)

# Include libraries
target_link_libraries(neuracom PRIVATE -pthread Boost::boost)

# Include header files
target_include_directories(neuracom
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>

  PRIVATE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src>)

# Define the C++ standard
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set_target_properties(neuracom
    PROPERTIES
    CXX_STANDARD 17)
endif()

# Define the compilation options/flags
target_compile_options(neuracom
  PRIVATE
  -Wall -Wextra -Wshadow -Weffc++ -Wno-long-long
  -pedantic -pedantic-errors)

# Define the compilation source files
target_sources(neuracom
  PRIVATE
  ${neuracom-sources})


####################
#    PROPERTIES    #
####################

# Set the library properties
set_target_properties(neuracom PROPERTIES
  VERSION "${PROJECT_VERSION}"
  SOVERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}"
  PROJECT_LABEL "neuracom $<IF:${build-shared},shared,static>"
  DEBUG_POSTFIX d)
