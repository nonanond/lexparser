macro (ph_IDE)
    foreach(file ${HEADER_LIST})
        source_group(TREE include/${self}
            PREFIX "headers"               
            FILES  ${file}
        )
    endforeach()
    foreach(file ${SOURCE_LIST})
        source_group(TREE ${CMAKE_CURRENT_LIST_DIR}
            PREFIX "sources"               
            FILES  ${file}
        )
    endforeach()
endmacro ()
