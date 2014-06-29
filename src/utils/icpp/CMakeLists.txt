set(INCROOT ${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/icpp)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME}/icpp)


#SET(BisonOutputSrc ${SRCROOT}/Parser.cpp)
#set(BisonOutputInc ${SRCROOT}/Parser.hpp)
#set(BisonOutputExtra ${SRCROOT}/stack.hh)
#SET(FlexOutputSrc ${SRCROOT}/Lexer.cpp)
#
#if(BUILD_PARSER)
#    FIND_PACKAGE(BISON REQUIRED)
#    IF(BISON_FOUND)
#        ADD_CUSTOM_COMMAND(
#            OUTPUT ${BisonOutputSrc} ${BisonOutputInc} ${BisonOutputExtra}
#          COMMAND ${BISON_EXECUTABLE}
#          --output=${BisonOutputSrc}
#          --defines=${BisonOutputInc}
#                  ${SRCROOT}/Parser.yy
#          COMMENT "Generating Parser.cpp"
#        )
#        INSTALL( FILES ${BisonOutputExtra} ${BisonOutputInc} DESTINATION include/${CMAKE_PROJECT_NAME}/json )
#    else()
#        message( SEND_ERROR "Bison is required" )
#    ENDIF()
#
#    FIND_PACKAGE(FLEX REQUIRED)
#    IF(FLEX_FOUND)
#        ADD_CUSTOM_COMMAND(
#            OUTPUT ${FlexOutputSrc}
#          COMMAND ${FLEX_EXECUTABLE}
#          --outfile=${FlexOutputSrc}
#                  ${SRCROOT}/Lexer.lex
#                  COMMENT "Generating Lexer.cpp"
#        )
#    else()
#        message( SEND_ERROR "Flex is required" )
#    ENDIF()
#endif()

#ROOT files
set(ROOT_SRC
    ${SRCROOT}/test.cpp
    #${SRCROOT}/Driver.cpp
    #${SRCROOT}/Scanner.cpp
    #${BisonOutputSrc}
    #${FlexOutputSrc}
)
set(ROOT_HEADER
    ${INCROOT}/test.hpp
    #${INCROOT}/Driver.hpp
    #${INCROOT}/FlexLexer.hpp
    #${INCROOT}/Scanner.hpp
    #${BisonOutputInc}
    #${BisonOutputExtra}
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

add_executable(${CMAKE_PROJECT_NAME}-icpp ${FILES_HEADER} ${FILES_SRC})
target_link_libraries(${CMAKE_PROJECT_NAME}-icpp ${CMAKE_PROJECT_NAME})

##SHARED lib
#add_library(${CMAKE_PROJECT_NAME}-icpp SHARED ${FILES_HEADER} ${FILES_SRC})
#SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME}-icpp
#    PROPERTIES
#    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
#    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
#)
#target_link_libraries(${CMAKE_PROJECT_NAME}-icpp ${CMAKE_PROJECT_NAME})
#INSTALL(TARGETS ${CMAKE_PROJECT_NAME}-icpp
#    DESTINATION lib
#)
#
##static lib
#add_library(${CMAKE_PROJECT_NAME}-icpp-static STATIC ${FILES_HEADER} ${FILES_SRC})
#SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME}-icpp-static
#    PROPERTIES
#    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
#    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
#)
#target_link_libraries(${CMAKE_PROJECT_NAME}-icpp-static ${CMAKE_PROJECT_NAME})
#INSTALL(TARGETS ${CMAKE_PROJECT_NAME}-icpp-static
#    DESTINATION lib
#)


