set(INCROOT ${PROJECT_SOURCE_DIR}/include/${CMAKE_PROJECT_NAME}/json)
set(SRCROOT ${PROJECT_SOURCE_DIR}/src/${CMAKE_PROJECT_NAME}/json)

FIND_PACKAGE(BISON REQUIRED)
SET(BisonOutputSrc ${SRCROOT}/Parser.cpp)
set(BisonOutputInc ${SRCROOT}/Parser.hpp ${SRCROOT}/stack.hh)
IF(BISON_FOUND)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${BisonOutputSrc} ${BisonOutputInc}
      COMMAND ${BISON_EXECUTABLE}
      --output=${BisonOutputSrc}
              ${SRCROOT}/Parser.yy
      COMMENT "Generating Parser.cpp"
    )
else()
    message( SEND_ERROR "Bison is required" )
ENDIF()

FIND_PACKAGE(FLEX REQUIRED)
SET(FlexOutputSrc ${SRCROOT}/Lexer.cpp)
IF(FLEX_FOUND)
    ADD_CUSTOM_COMMAND(
        OUTPUT ${FlexOutputSrc}
      COMMAND ${FLEX_EXECUTABLE}
      --outfile=${FlexOutputSrc}
              ${SRCROOT}/Lexer.lex
              COMMENT "Generating Lexer.cpp"
    )
else()
    message( SEND_ERROR "Flex is required" )
ENDIF()

#ROOT files
set(ROOT_SRC
    ${SRCROOT}/Driver.cpp
    ${SRCROOT}/Scanner.cpp
    ${BisonOutputSrc}
    ${FlexOutputSrc}
)
set(ROOT_HEADER
    ${INCROOT}/Driver.hpp
    ${INCROOT}/FlexLexer.hpp
    ${INCROOT}/Scanner.hpp
    ${BisonOutputInc}
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

#SHARED lib
add_library(${CMAKE_PROJECT_NAME}-json SHARED ${FILES_HEADER} ${FILES_SRC})
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME}-json
    PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
INSTALL(TARGETS ${CMAKE_PROJECT_NAME}-json
    DESTINATION lib
)

#static lib
add_library(${CMAKE_PROJECT_NAME}-json-static STATIC ${FILES_HEADER} ${FILES_SRC})
SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME}-json-static
    PROPERTIES
    VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}
    SOVERSION ${VERSION_MAJOR}.${VERSION_MINOR}
)
INSTALL(TARGETS ${CMAKE_PROJECT_NAME}-json-static
    DESTINATION lib
)
