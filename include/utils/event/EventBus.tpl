#include <type_traits>

#include <utils/event/Event.hpp>
#include <utils/event/VEventHandler.hpp>

namespace utils
{

namespace event
{
    template<typename T>
    void EventBus::connect(EventHandler<T>& handler)
    {
        static_assert(std::is_base_of<Event<T>,T>::value, "EventBus::connect<T>(EventHandler<T>&): T must be a class derived from Event<T>");

        static_cast<priv::VEventHandler&>(handler)._register(this);
        _handlers[T::family()].emplace_back(&handler);

    }

    /*template<typename T>
    void EventBus::connect(EventHandler<T>& handler,const std::function<void(T& event)>& callback)
    {
        static_assert(std::is_base_of<Event<T>,T>::value, "EventBus::connect<T>(EventHandler<T>&): T must be a class derived from Event<T>");
    }*/

    template<typename T>
    void EventBus::disconnect(EventHandler<T>& handler)
    {
        static_assert(std::is_base_of<Event<T>,T>::value, "EventBus::disconnect<T>(EventHandler<T>&): T must be a class derived from Event<T>");


        handler._unregister(this);
        _unregister(T::family,&handler);
    }

    template<typename T>
    void EventBus::emit(T& event)
    {
        static_assert(std::is_base_of<Event<T>,T>::value, "EventBus::emit(T&): T must be a class derived from Event<T>");

        for(auto&& handler : _handlers[T::family()])
            static_cast<EventHandler<T>*>(handler)->exec(event);

    }
}
}
