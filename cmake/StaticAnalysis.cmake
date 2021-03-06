set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
option(ENABLE_CLANG_TIDY "Enable static analysis with clang-tidy" ON)

if(ENABLE_CLANG_TIDY)
    find_program(CLANGTIDY clang-tidy)
    if(CLANGTIDY)
        set(CMAKE_CXX_CLANG_TIDY
            ${CLANGTIDY}
            -header-filter=.*
            -checks=cppcoreguidelines-*,misc-*,modernize-*,performance-*,readability-*
            -extra-arg=-Wno-unknown-warning-option)
        message(STATUS "Enabling static analysis using clang-tidy.")
    else()
        message(SEND_ERROR "clang-tidy requested but executable not found")
    endif()
endif()
