add_library(vocabulary Vocabulary.cpp)
target_include_directories(vocabulary PUBLIC .)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE vocabulary)
target_code_coverage(${PROJECT_NAME} AUTO)
