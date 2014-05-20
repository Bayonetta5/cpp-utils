add_executable(utils-test utils-test.cpp)
target_link_libraries(utils-test ${CMAKE_PROJECT_NAME})

if(BUILD_JSON)
    add_executable(json-test json-test.cpp)
    target_link_libraries(json-test ${CMAKE_PROJECT_NAME} ${CMAKE_PROJECT_NAME}-json)
endif()
