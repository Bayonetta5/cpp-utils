set(INCROOT ${INCROOT}/event)
set(SRCROOT ${SRCROOT}/event)

list(APPEND FILES_SRC
    ${SRCROOT}/EventBus.cpp
    ${SRCROOT}/VEvent.cpp
    ${SRCROOT}/VEventHandler.cpp
)
set(FILES_SRC "${FILES_SRC}" PARENT_SCOPE)

list(APPEND FILES_HEADER
    ${INCROOT}/Emitter.hpp
    ${INCROOT}/Emitter.tpl
    ${INCROOT}/Event.hpp
    ${INCROOT}/Event.tpl
    ${INCROOT}/EventBus.hpp
    ${INCROOT}/EventHandler.hpp
    ${INCROOT}/VEvent.hpp
    ${INCROOT}/VEventHandler.hpp
    ${INCROOT}/VEventHandler.tpl
)
set(FILES_HEADER "${FILES_HEADER}" PARENT_SCOPE)

