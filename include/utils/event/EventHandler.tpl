#include <type_traits>

#include <utils/event/Emitter.hpp>

namespace utils
{
namespace event
{
    ////////////// VEventHandler /////////////////
    template<typename T>
    VEventHandler<T>::VEventHandler() : VEventHandler<T>([](const T&){})
    {
    }

    template<typename T>
    VEventHandler<T>::VEventHandler(const VEventHandler<T>::FuncType& callback) : ::utils::event::priv::VEventHandler(T::family()), _callback(callback)
    {
        static_assert(std::is_base_of<Event<T>,T>::value, "VEventHandler<T>: T must be a class derived from Event<T>");
    }

    template<typename T>
    VEventHandler<T>::~VEventHandler()
    {
        for(auto&& emitter : _emitters)
            emitter.first->_unregister(this);
    }

    template<typename T>
    void VEventHandler<T>::connect(VEmitter<T>& emitter)
    {
        emitter._register(this);
        _register(&emitter);
    }

    template<typename T>
    void VEventHandler<T>::connect(VEmitter<T>& emitter,const FuncType& callback)
    {
        emitter._register(this);
        _register(&emitter,callback);
    }

    template<typename T>
    void VEventHandler<T>::disconnect(VEmitter<T>& emitter)
    {
        emitter._unregister(this);
        _unregister(&emitter);
    }

    template<typename T>
    void VEventHandler<T>::_register(VEmitter<T>* emitter)
    {
        _emitters.emplace(emitter,_callback);
    }

    template<typename T>
    void VEventHandler<T>::_register(VEmitter<T>* emitter,const FuncType& callback)
    {
        _emitters.emplace(emitter,callback);
    }

    template<typename T>
    void VEventHandler<T>::_unregister(VEmitter<T>* emitter)
    {
        auto search = _emitters.find(emitter);
        if(search != _emitters.end())
            _emitters.erase(search);
    }

    template<typename T>
    void VEventHandler<T>::exec(VEmitter<T>* emitter,const T& event)
    {
        _emitters.at(emitter)(event);
    }

    template<typename T>
    void VEventHandler<T>::exec(T& event)
    {
        _callback(event);
    }


    ///////////////////// EventHandler ////////////////////

    template<typename ... Args>
    EventHandler<Args ...>::EventHandler()
    {
    }
    
    template<typename ... Args>
    EventHandler<Args ...>::EventHandler(typename VEventHandler<Args>::FuncType& ... callbacks) :
        VEventHandler<Args>(callbacks) ...
    {
    }

    template<typename ... Args>
    template<typename T>
    void EventHandler<Args ...>::connect(VEmitter<T>& emmiter)
    {
    }

    template<typename ... Args>
    template<typename T>
    void EventHandler<Args ...>::connect(VEmitter<T>& emitter,const typename VEventHandler<T>::FuncType& callback)
    {
    }

    template<typename ... Args>
    template<typename T>
    void EventHandler<Args ...>::disconnect(VEmitter<T>& emitter)
    {
    }


}
}
