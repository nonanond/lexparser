cmake_minimum_required (VERSION 3.19.6)




list (APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
		execute_process(
			# COMMAND ${GIT_EXECUTABLE} submodule update --remote --merge #--recursive
            COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive 
                        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT
		)

        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()


include (FetchContent)


file (GLOB_RECURSE cmakes cmake/*.cmake)

foreach (file ${cmakes})
    include (${file})
endforeach ()

