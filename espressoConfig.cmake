# espressoConfig.cmake - CMake package configuration file for espresso



# Use relative paths for in-source builds
get_filename_component(_prefix "${CMAKE_CURRENT_LIST_DIR}/../../.." ABSOLUTE)
set(espresso_INCLUDE_DIR "${_prefix}/include")
set(espresso_LIBRARY_DIR "${_prefix}/lib")

# Set the library file (Release by default)
set(espresso_LIBRARIES "${espresso_LIBRARY_DIR}/libespresso.a")

# Optionally, set the debug library
if(EXISTS "${espresso_LIBRARY_DIR}/libespressod.a")
    set(espresso_LIBRARIES_DEBUG "${espresso_LIBRARY_DIR}/libespressod.a")
endif()

# Provide an imported target for easy linking
if(NOT TARGET espresso::espresso)
    add_library(espresso::espresso STATIC IMPORTED)
    set_target_properties(espresso::espresso PROPERTIES
        IMPORTED_LOCATION "${espresso_LIBRARIES}"
        INTERFACE_INCLUDE_DIRECTORIES "${espresso_INCLUDE_DIR}"
    )
    if(DEFINED espresso_LIBRARIES_DEBUG)
        set_target_properties(espresso::espresso PROPERTIES
            IMPORTED_LOCATION_DEBUG "${espresso_LIBRARIES_DEBUG}"
        )
    endif()
endif()
