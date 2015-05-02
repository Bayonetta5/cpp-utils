#include <type_traits>

#include <utils/event/Emitter.hpp>

namespace utils
{
namespace event
{

    template<typename T>
    EventHandler<T>::EventHandler() : EventHandler<T>([](T&){})
    {
    }

    template<typename T>
    EventHandler<T>::EventHandler(const EventHandler<T>::FuncType& callback) : ::utils::event::priv::VEventHandler(T::family()), _callback(callback)
    {
        static_assert(std::is_base_of<Event<T>,T>::value, "EventHandler<T>: T must be a class derived from Event<T>");
    }

    template<typename T>
    template<typename U>
    EventHandler<T>::EventHandler(void (U::*method)(T&) ) :
        EventHandler(std::bind(method,static_cast<U*>(this),std::placeholders::_1))
    {
        static_assert(std::is_base_of<EventHandler<T>,U>::value, "EventHandler<T>: the method as parameter must be from a class derived from EventHandler<T>");
    }

    template<typename T>
    EventHandler<T>::~EventHandler()
    {
        for(auto&& emitter : _emitters)
            emitter.first->_unregister(this);
    }

    template<typename T>
    void EventHandler<T>::connect(Emitter<T>& emitter)
    {
        emitter._register(this);
        _register(&emitter);
    }

    template<typename T>
    void EventHandler<T>::connect(Emitter<T>& emitter,const FuncType& callback)
    {
        emitter._register(this);
        _register(&emitter,callback);
    }

    template<typename T>
    void EventHandler<T>::disconnect(Emitter<T>& emitter)
    {
        emitter._unregister(this);
        _unregister(&emitter);
    }

    template<typename T>
    void EventHandler<T>::_register(Emitter<T>* emitter)
    {
        _emitters.emplace(emitter,_callback);
    }

    template<typename T>
    void EventHandler<T>::_register(Emitter<T>* emitter,const FuncType& callback)
    {
        _emitters.emplace(emitter,callback);
    }

    template<typename T>
    void EventHandler<T>::_unregister(Emitter<T>* emitter)
    {
        auto search = _emitters.find(emitter);
        if(search != _emitters.end())
            _emitters.erase(search);
    }

    template<typename T>
    void EventHandler<T>::exec(Emitter<T>* emitter,T& event)
    {
        _emitters.at(emitter)(event);
    }

    template<typename T>
    void EventHandler<T>::exec(T& event)
    {
        _callback(event);
    }

}
}
