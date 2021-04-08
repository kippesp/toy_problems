set(LIBRARY_TARGET_NAME fnv)

set(${LIBRARY_TARGET_NAME}_SRCS
    fnv1a.cpp
    hash_128a.cpp
)

add_library(${LIBRARY_TARGET_NAME} ${${LIBRARY_TARGET_NAME}_SRCS})
