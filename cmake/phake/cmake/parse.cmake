macro (ph_parse1)
    set(p       p)
    set(N0     )
    set(N1 )
    set(N  n0 n1 n ARGS)


    cmake_parse_arguments( ${p}
                            "${N0}"
                            "${N1}"
                            "${N}"
                            ${ARGN}
    )

        foreach (arg IN LISTS N)
        if ("${arg}" STREQUAL n0)
            # list (APPEND n0 ${${p}_${arg}})
            set (n0 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL n1)
            # list (APPEND n1 ${${p}_${arg}})
            # message (". ${${p}_${arg}} .")
        
            set (n1 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL n)
            set (n ${${p}_${arg}})
            # list (APPEND n ${${p}_${arg}})

        elseif ("${arg}" STREQUAL f0)
            # set (APPEND F0 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL f1)
            # set (APPEND F1 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL fn)
            # set (APPEND FN ${${p}_${arg}})

        elseif ("${arg}" STREQUAL ARGS)
            
            set (argsa ${${p}_${arg}})
        
            foreach (a ${argsa})
                list (APPEND res ${a})
            endforeach ()
            

        endif ()


        # message ("${argsa}")

        

    endforeach ()
    message (${res})
    set (ARGN ${res})

    function (cont)
       

            set(pp      ARG)
            set(NN0     ${n0})
            set(NN1 ${n1})
            set(NN ${n})


            cmake_parse_arguments( ${pp}
                                    "${n0}"
                                    "${n1}"
                                    "${n}"
                                    ${res}
            )

            message (${res})


            foreach (arg IN LISTS NN0)
                # message (${arg})
                if(${${pp}_${arg}})
                    # message("  ${arg} enabled")
                    N0 (${arg})
                else()
                    # message("  ${arg} disabled")
                endif()
            endforeach ()


            foreach (arg IN LISTS NN1)
                # message("  ${arg} = ${${pp}_${arg}}")
                if (${pp}_${arg})
                    # message("  ${arg} = ${${pp}_${arg}}")
                    N1 (${${pp}_${arg}})
                endif ()
                
            endforeach ()

            foreach (arg IN LISTS NN)
                if (${pp}_${arg})
                    # message("  ${arg} = ${${pp}_${arg}}")
                    # N (${${pp}_${arg}})
                    foreach (a ${${pp}_${arg}})
                        N (${a})
                    endforeach ()
                    
                endif ()
                
                
            endforeach ()

   
    endfunction ()

    cont (${res})

    
endmacro ()














macro (ph_parse2)
    set(p       p)
    set(N0     )
    set(N1 )
    set(N  n0 n1 n ARGS)


    cmake_parse_arguments( ${p}
                            "${N0}"
                            "${N1}"
                            "${N}"
                            ${ARGN}
    )

        foreach (arg IN LISTS N)
        if ("${arg}" STREQUAL n0)
            # list (APPEND n0 ${${p}_${arg}})
            set (n0 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL n1)
            # list (APPEND n1 ${${p}_${arg}})
            # message (". ${${p}_${arg}} .")
        
            set (n1 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL n)
            set (n ${${p}_${arg}})
            # list (APPEND n ${${p}_${arg}})

        elseif ("${arg}" STREQUAL f0)
            # set (APPEND F0 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL f1)
            # set (APPEND F1 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL fn)
            # set (APPEND FN ${${p}_${arg}})

        elseif ("${arg}" STREQUAL ARGS)
            
            set (argsa ${${p}_${arg}})
        
            foreach (a ${argsa})
                list (APPEND res ${a})
            endforeach ()
            

        endif ()


        # message ("${argsa}")

        

    endforeach ()
 
    set (ARGN ${res})

    function (cont)
       

            set(pp      ARG)
            set(NN0     ${n0})
            set(NN1 ${n1})
            set(NN ${n})


            cmake_parse_arguments( ${pp}
                                    "${n0}"
                                    "${n1}"
                                    "${n}"
                                    ${res}
            )

        


            foreach (arg IN LISTS NN0)
                # message (${arg})
                if(${${pp}_${arg}})
                    # message("  ${arg} enabled")
                    # cmake_language (CALL ${arg})
                    # cmake_language(DEFER CALL ${arg})
                else()
                    # message("  ${arg} disabled")
                endif()
            endforeach ()


            foreach (arg IN LISTS NN1)
                # message("  ${arg} = ${${pp}_${arg}}")
                if (${pp}_${arg})
                    message("  ${arg} = ${${pp}_${arg}}")
                    cmake_language (CALL ${arg} ${${pp}_${arg}})
                    # cmake_language(DEFER CALL ${arg} ${${pp}_${arg}})
                    # N1 (${${pp}_${arg}})
                endif ()
                
            endforeach ()

            foreach (arg IN LISTS NN)
                if (${pp}_${arg})
                    # message("  ${arg} = ${${pp}_${arg}}")
                    # N (${${pp}_${arg}})
                    # cmake_language (DEFER CALL ${arg} ${a})
                    foreach (a ${${pp}_${arg}})
                        # N (${a})
                      
                        function (ja)
                            if (COMMAND ${arg})
                                cmake_language (CALL ${arg} ${a})
                            endif ()
                            
                        endfunction ()
                        
              
                        # cmake_language(DEFER CALL ja)
                    endforeach ()
                    
                endif ()
                
                
            endforeach ()

   
    endfunction ()

    cont (${res})

    
endmacro ()









macro (ph_parse)
    set (ARG_N ${ARGN})

    set(p       p)
    set(N0     )
    set(N1 )
    set(N  . .. ... args)


    cmake_parse_arguments( ${p}
                            "${N0}"
                            "${N1}"
                            "${N}"
                            ${ARG_N}
    )

        foreach (arg IN LISTS N)
        if ("${arg}" STREQUAL .)
            # list (APPEND n0 ${${p}_${arg}})
            set (n0 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL ..)
            # list (APPEND n1 ${${p}_${arg}})
            # message (". ${${p}_${arg}} .")
        
            set (n1 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL ...)
            set (n ${${p}_${arg}})
            # list (APPEND n ${${p}_${arg}})

        elseif ("${arg}" STREQUAL f0)
            # set (APPEND F0 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL f1)
            # set (APPEND F1 ${${p}_${arg}})

        elseif ("${arg}" STREQUAL fn)
            # set (APPEND FN ${${p}_${arg}})

        elseif ("${arg}" STREQUAL args)
            
            set (argsa ${${p}_${arg}})
        
            foreach (a ${argsa})
                list (APPEND res ${a})
            endforeach ()
            

        endif ()


        # message ("${argsa}")

        

    endforeach ()
    # message (${res})
    # set (ARG ${res})

    macro (cont)
       
    # message (${res})
    
            set(pp      ARG)
            set(NN0     ${n0})
            set(NN1 ${n1})
            set(NN ${n})

            
            cmake_parse_arguments( ${pp}
                                    "${n0}"
                                    "${n1}"
                                    "${n}"
                                    ${res}
            )

            # message (${res})


            foreach (arg IN LISTS NN0)
                # message (${arg})
                if(${${pp}_${arg}})
                    # message("  ${arg} enabled")
                    # cmake_language (CALL ${arg})
                    cmake_language(CALL ${arg})
                else()
                    # message("  ${arg} disabled")
                endif()
            endforeach ()


            foreach (arg IN LISTS NN1)
                # message("  ${arg} = ${${pp}_${arg}}")
                if (${pp}_${arg})
                    # message("  ${arg} = ${${pp}_${arg}}")
                    # cmake_language (CALL ${arg} ${${pp}_${arg}})
                    cmake_language(CALL ${arg} ${${pp}_${arg}})
                    # N1 (${${pp}_${arg}})
                endif ()
                
            endforeach ()

            foreach (arg IN LISTS NN)
                if (${pp}_${arg})
                    # message("  ${arg} = ${${pp}_${arg}}")
                    # N (${${pp}_${arg}})

                    if (COMMAND ${arg}...)
                            cmake_language(CALL ${arg}... ${${pp}_${arg}})

                    elseif (COMMAND ${arg})

                        foreach (a ${${pp}_${arg}})
                            cmake_language (CALL ${arg} ${a})
                        endforeach ()
                    endif ()
                    
                endif ()
                
                
            endforeach ()

   
            endmacro ()

    cont (${res})

    
endmacro ()
