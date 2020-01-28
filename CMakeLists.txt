cmake_minimum_required(VERSION 3.8)

project(neuracom VERSION 1.0.0 LANGUAGES CXX)

# Sanity check : Check that all submodules are present
# =======================================================================

function(check_submodules_present)
	file(READ "${PROJECT_SOURCE_DIR}/.gitmodules" gitmodules)
	string(REGEX MATCHALL "path *= *[^ \t\r\n]*" gitmodules ${gitmodules})
	foreach(module ${gitmodules})
		string(REGEX REPLACE "path *= *" "" module ${module})
		if (NOT EXISTS "${PROJECT_SOURCE_DIR}/${module}/.git")
			message(FATAL_ERROR "Git submodule ${module} not found. "
				"Please run: git submodule update --init --recursive")
		endif()
	endforeach()
endfunction()
check_submodules_present()

# Configure C++ standard
# ===========================

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# System imported libraries
# ======================

find_package(Boost 1.66.0 QUIET)
if (NOT Boost_FOUND)
	message(STATUS "Boost 1.66.0 or newer not found, falling back to externals")

	set(BOOST_ROOT "${PROJECT_SOURCE_DIR}/externals/boost")
	set(Boost_NO_SYSTEM_PATHS OFF)
	find_package(Boost QUIET REQUIRED)
endif()

# Output binaries to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# Output static library to lib/
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Output neuracom library to lib/
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Include source code
# ===================

# This function should be passed a list of all files in a target. It will automatically generate
# file groups following the directory hierarchy, so that the layout of the files in IDEs matches the
# one in the filesystem.
function(create_target_directory_groups target_name)
	# Place any files that aren't in the source list in a separate group so that they don't get in
	# the way.
	source_group("Other Files" REGULAR_EXPRESSION ".")

	get_target_property(target_sources "${target_name}" project)

	foreach(file_name IN LISTS target_sources)
		get_filename_component(dir_name "${file_name}" PATH)
		# Group names use '\' as a separator even though the entire rest of CMake uses '/'...
		string(REPLACE "/" "\\" group_name "${dir_name}")
		source_group("${group_name}" FILES "${file_name}")
	endforeach()
endfunction()

enable_testing()
add_subdirectory(externals)
add_subdirectory(project)
