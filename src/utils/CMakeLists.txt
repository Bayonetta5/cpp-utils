set(INCROOT ${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME})
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME})

if(BUILD_JSON)
    add_subdirectory(json)
endif()

if(BUILD_ICPP)
    add_subdirectory(icpp)
endif()

set(ROOT_SRC
    ${SRCROOT}/log.cpp
    ${SRCROOT}/plot.cpp
    ${SRCROOT}/string.cpp
    ${SRCROOT}/sys.cpp
    ${SRCROOT}/thread.cpp
)

set(ROOT_HEADER
    ${INCROOT}/functional.hpp
    ${INCROOT}/functional.tpl
    ${INCROOT}/json.hpp
    ${INCROOT}/log.hpp
    ${INCROOT}/log.tpl
    ${INCROOT}/maths.hpp
    ${INCROOT}/maths.tpl
    ${INCROOT}/plot.hpp
    ${INCROOT}/plot.tpl
    ${INCROOT}/string.hpp
    ${INCROOT}/string.tpl
    ${INCROOT}/sys.hpp
    ${INCROOT}/sys.tpl
    ${INCROOT}/thread.hpp
    ${INCROOT}/thread.tpl
    ${INCROOT}/tr.hpp
)


set(ROOT_FILES
    ${ROOT_HEADER}
    ${ROOT_SRC}
)

#FILES
set(FILES_HEADER
    ${ROOT_HEADER}
)
set(FILES_SRC
    ${ROOT_SRC}
)

add_library(${CMAKE_PROJECT_NAME} SHARED ${FILES_SRC} ${FILES_HEADER})
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME}
    PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})
INSTALL(TARGETS ${CMAKE_PROJECT_NAME}
    DESTINATION lib
)

add_library(${CMAKE_PROJECT_NAME}-static STATIC ${FILES_HEADER} ${FILES_SRC})
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME}-static
    PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
target_link_libraries(${CMAKE_PROJECT_NAME}-static ${LIBS})
INSTALL(TARGETS ${CMAKE_PROJECT_NAME}-static
    DESTINATION lib
)


file(GLOB DEPLOY_FILES_AND_DIRS "${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/*")
foreach(ITEM ${DEPLOY_FILES_AND_DIRS})
   IF( IS_DIRECTORY "${ITEM}" )
      LIST( APPEND DIRS_TO_DEPLOY "${ITEM}" )
   ELSE()
      LIST( APPEND FILES_TO_DEPLOY "${ITEM}" )
   ENDIF()
endforeach()
INSTALL( FILES ${FILES_TO_DEPLOY} ${BisonOutputInc} DESTINATION include/${CMAKE_PROJECT_NAME} )
INSTALL( DIRECTORY ${DIRS_TO_DEPLOY} DESTINATION include/${CMAKE_PROJECT_NAME} )


########################################################################
# Create uninstall target
########################################################################
CONFIGURE_FILE(
    "${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake.in"
    "${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake"
  IMMEDIATE @ONLY)
ADD_CUSTOM_TARGET(uninstall
    "${CMAKE_COMMAND}" -P "${PROJECT_SOURCE_DIR}/cmake/cmake_uninstall.cmake"
)
