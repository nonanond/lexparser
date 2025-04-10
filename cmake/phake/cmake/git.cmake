

macro (ph_git)
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
# Update submodules as needed
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        # execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
        #                 WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        #                 RESULT_VARIABLE GIT_SUBMOD_RESULT)
		execute_process(
			# COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
			COMMAND ${GIT_EXECUTABLE} submodule update --remote --merge origin/master#submodule update --remote --merge --init --recursive

						# COMMAND ${GIT_EXECUTABLE} submodule foreach git pull main
                        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                        RESULT_VARIABLE GIT_SUBMOD_RESULT
		)

        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()
    
endmacro ()
