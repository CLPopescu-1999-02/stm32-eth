
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


function(add_hex_target targetname)
    add_custom_target(${targetname}.hex DEPENDS ${targetname}
                                    COMMAND ${CMAKE_OBJCOPY} -Oihex $<TARGET_FILE:${targetname}> ${targetname}.hex
                                    VERBATIM
                                    )
endfunction()


function(add_bin_target targetname)
    add_custom_target(${targetname}.bin DEPENDS ${targetname}
                                    COMMAND ${CMAKE_OBJCOPY} -Obinary $<TARGET_FILE:${targetname}> ${targetname}.bin
                                    VERBATIM
                                    )
endfunction()


find_program(SIZE_EXE size)

function(add_size_target targetname)
    if( NOT SIZE_EXE )
        message(WARNING "'size' not found!")
    else()
        add_custom_target(${targetname}.size DEPENDS ${targetname}
                                        COMMAND ${SIZE_EXE} -t --format=berkeley $<TARGET_FILE:${targetname}>
                                        VERBATIM
                                        )
    endif()
endfunction()



if( CMAKE_CROSSCOMPILING )
    set(CMAKE_EXECUTABLE_SUFFIX ".elf")
endif()

