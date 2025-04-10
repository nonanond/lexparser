
set (boost_pch 
<boost/preprocessor/seq/for_each.hpp>
<boost/preprocessor/variadic/to_seq.hpp>
<boost/preprocessor/facilities/expand.hpp>
<boost/preprocessor/stringize.hpp>
<boost/preprocessor/repetition/enum_params.hpp>
<boost/preprocessor/cat.hpp>
<boost/preprocessor/seq/cat.hpp>
<boost/preprocessor/control/if.hpp>
<boost/preprocessor/facilities/empty.hpp>
<boost/preprocessor/facilities/identity.hpp>
<boost/preprocessor/seq/to_tuple.hpp>
<boost/preprocessor/seq/for_each_i.hpp>
<boost/preprocessor/arithmetic/inc.hpp>
<boost/preprocessor/comparison/not_equal.hpp>
<boost/preprocessor/repetition/for.hpp>
<boost/preprocessor/tuple/elem.hpp>
<boost/preprocessor/repetition.hpp>
<boost/preprocessor/arithmetic/sub.hpp>
<boost/preprocessor/punctuation/comma_if.hpp>
<boost/preprocessor/control/if.hpp>
<boost/preprocessor/facilities/empty.hpp>
<boost/preprocessor/facilities/identity.hpp>
<boost/tti/has_template.hpp>
<boost/tti/has_type.hpp>
<boost/tti/has_member_function.hpp>
<boost/tti/has_member_data.hpp>
<boost/tti/has_static_member_data.hpp>
<boost/tti/has_static_member_function.hpp>
<boost/tti/has_data.hpp>
<boost/tti/has_function.hpp>
<boost/tti/member_type.hpp>
<boost/preprocessor/variadic/to_tuple.hpp>
CACHE 
STRING 
"boost pch headers"
FORCE
)

set (std_pch
<cctype>
<set>
<queue>
<iostream>
<vector>
<string>
<utility>
<array>
<tuple>
<type_traits>
<filesystem>
<fstream>
<regex>
<optional>
<algorithm>
<cstring>
<cstdlib>
<filesystem>
<variant>
<any>
<charconv>
<concepts>
<thread>
<iterator>
<random>
<sstream>
# <future>
<atomic>

# <latch>
# <barrier>
CACHE 
STRING 
"std pch headers"
FORCE
)

set (ph_catch2_pch
<catch2/catch.hpp>
CACHE 
STRING 
"std pch headers"
FORCE
)



function(ph_boost target)
    cmake_parse_arguments(p "public;private;interface;no_pch" "" "" ${ARGN})
    if (${ARGC} EQUAL "1" OR p_public)
        set (t3 PUBLIC)
    elseif (p_private)
        set (t3 PRIVATE)
    elseif(p_interface)
        set (t3 INTERFACE)
    endif()
    cmake_language (EVAL CODE "
        target_link_libraries(${target} ${t3} ${Boost_LIBRARIES})
        target_include_directories (${target} ${t3} ${Boost_INCLUDE_DIRS})
    ")
    if (NOT p_no_pch)
        target_precompile_headers (${target} 
         PRIVATE 
            ${boost_preprocessor_pch}
        )
    endif ()
    
    
    
endfunction()




macro (ph_precompile)
# ph_parse (.. TARGET ... HEADERS PC)
    set(p       p)
    set(N0     PRIVATE PUBLIC)
    set(N1 TARGET)
    set(N  HEADERS PCH)

    set (availability PUBLIC)

    cmake_parse_arguments( ${p}
                            "${N0}"
                            "${N1}"
                            "${N}"
                            ${ARGN}
    )

    foreach(arg IN LISTS N0)
        if(${${p}_${arg}})
            set (availability "${arg}")
            break ()
        else()
        endif()
    endforeach()

    foreach(arg IN LISTS N1)
        if ("${arg}" STREQUAL TARGET)
            set (target ${${p}_${arg}})
        endif ()
        
    endforeach()
    

    foreach (arg IN LISTS N)
        if ("${arg}" STREQUAL HEADERS)
            # set (${headers} ${headers} ${${p}_${arg}})
            list (APPEND headers ${${p}_${arg}})
        elseif ("${arg}" STREQUAL PCH)
            # set (${headers} ${headers} ${${p}_${arg}})
            list (APPEND headers ${${p}_${arg}})
        endif ()
    endforeach ()
    # message(${target})
    # message (${headers})
    # message (${availability})
    target_precompile_headers (${target} ${availability} ${headers})


    
endmacro ()



