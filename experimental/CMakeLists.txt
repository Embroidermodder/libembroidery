# Set up swig
find_package(SWIG)
if(NOT SWIG_FOUND)
    message(WARNING "Swig not found. Skipping interface generation.")
    return()
endif()
include(${SWIG_USE_FILE})
option(SWIG_CSHARP "Wrap C#" ON)

if (SWIG_CSHARP)
    set (CMAKE_SWIG_FLAGS "" )
    SET_SOURCE_FILES_PROPERTIES(swig.i PROPERTIES C ON)
    SET_SOURCE_FILES_PROPERTIES(swig.i PROPERTIES SWIG_FLAGS "-I..")

    list(TRANSFORM LIBRARY_SOURCE_FILES PREPEND ${CMAKE_CURRENT_SOURCE_DIR}/../)
    swig_add_library(libembroidery TYPE SHARED
        LANGUAGE csharp
        OUTPUT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/csharp/binding
        SOURCES
        ${LIBRARY_SOURCE_FILES}
        swig.i
        ../embroidery.h
    )
    target_include_directories(libembroidery
        INTERFACE
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        PUBLIC
            include
    )
    target_compile_definitions(libembroidery PUBLIC LIBEMBROIDERY_SHARED)
    set_target_properties(libembroidery
        PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/csharp/binding
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/csharp/binding
    )
endif(SWIG_CSHARP)
