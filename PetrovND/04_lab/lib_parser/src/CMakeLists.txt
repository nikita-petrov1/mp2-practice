set(target ${MP2_LIBRARY_PARSER})

file(GLOB hdrs "*.h*" "${MP2_INCLUDE_PARSER}/*.h*")
file(GLOB srcs "*.cpp")

include_directories("${MP2_INCLUDE_PARSER}")

add_library(${target} STATIC ${srcs} ${hdrs})
