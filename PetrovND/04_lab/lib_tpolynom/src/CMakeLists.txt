set(target ${MP2_LIBRARY_POLYNOMS})

file(GLOB hdrs "*.h*" "${MP2_INCLUDE_POLYNOMS}/*.h*")
file(GLOB srcs "*.cpp")

include_directories("${MP2_INCLUDE_LISTS}" "${MP2_INCLUDE_POLYNOMS}" "${MP2_INCLUDE_PARSER}")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${MP2_LIBRARY_LISTS})
target_link_libraries(${target} ${MP2_LIBRARY_PARSER})
