#include <type_traits>

#include <utils/event/Event.hpp>
#include <utils/event/VEventHandler.hpp>

namespace utils
{

namespace event
{

    template<typename T>
    void EventBus::emit(T& event)
    {
        static_assert(std::is_base_of<Event<T>,T>::value, "EventBus::emit(T&): T must be a class derived from Event<T>");

        for(auto&& handler : _handlers[T::family()])
            static_cast<VEventHandler<T>*>(handler)->exec(event);

    }
}
}
