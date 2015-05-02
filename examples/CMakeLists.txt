add_executable(utils-test utils-test.cpp)
target_link_libraries(utils-test ${PROJECT_NAME}-shared)

add_executable(event-test event-test.cpp)
target_link_libraries(event-test ${PROJECT_NAME}-shared)

if(UTILS_BUILD_JSON)
    add_executable(json-test json-test.cpp)
    target_link_libraries(json-test ${PROJECT_NAME}-shared ${PROJECT_NAME}-json-shared)
endif()
