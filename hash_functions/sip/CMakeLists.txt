set(LIBRARY_TARGET_NAME sip)

set(${LIBRARY_TARGET_NAME}_SRCS
    sip.cpp
)

add_library(${LIBRARY_TARGET_NAME} ${${LIBRARY_TARGET_NAME}_SRCS})

if (NOT MSVC)
    target_compile_options(${LIBRARY_TARGET_NAME} PRIVATE -Wno-implicit-fallthrough)
endif()
