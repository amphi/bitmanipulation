set(CLANG_WARNINGS
    -Wall
    -Wextra              # reasonable and standard
    -Wshadow             # warn the user if a variable declaration shadows one
                         # from a parent context
    -Wnon-virtual-dtor   # warn the user if a class with a virtual function
                         # has a non-virtual destructor. This helps catch hard
                         # to track down memory errors
    -Wold-style-cast     # warn for c-style casts
    -Wcast-align         # warn for potential performance problem casts
    -Wunused             # warn on anything unused
    -Woverloaded-virtual # warn if you overload (not override) a virtual
                         # function
    -Wpedantic           # warn if non-standard C++ is used
    -Wconversion         # warn on type conversions that may lose data
    -Wsign-conversion    # warn on sign conversions
    -Wnull-dereference   # warn if a null dereference is detected
    -Wdouble-promotion   # warn if float is implicit promoted to double
    -Wformat=2           # warn on security issues around functions that format
                         # output (i.e. printf)
)

if(NOT CMAKE_BUILD_TYPE MATCHES Debug)
    set(CLANG_WARNINGS ${CLANG_WARNINGS} -Werror)
    message(STATUS "Treating compiler warnings as errors.")
endif()

if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(CLANG_WARNINGS ${CLANG_WARNINGS} -g)
    message(STATUS "Building with debug-flag.")
endif()

set(GCC_WARNINGS
    ${CLANG_WARNINGS}
    -Wmisleading-indentation # warn if indentation implies blocks where
                             # blocks do not exist
    -Wduplicated-cond        # warn if if / else chain has duplicated
                             # conditions
    -Wduplicated-branches    # warn if if / else branches have duplicated code
    -Wlogical-op             # warn about logical operations being used where
                             # bitwise
                             # were probably wanted
    -Wuseless-cast           # warn if you perform a cast to the same type
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(PROJECT_WARNINGS ${CLANG_WARNINGS})
    message(STATUS "Building with clang.")
else()
    set(PROJECT_WARNINGS ${GCC_WARNINGS})
    message(STATUS "Building with gcc.")
endif()

string(REPLACE ";" " " PROJECT_WARNINGS_STRING "${PROJECT_WARNINGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROJECT_WARNINGS_STRING}")
