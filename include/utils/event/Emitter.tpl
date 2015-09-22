#include <type_traits>
#include <utils/event/EventHandler.hpp>

namespace utils
{
    namespace event
    {

        ////////////////// VEvent ///////////////////
        template<typename T>
        VEmitter<T>::VEmitter()
        {
            static_assert(std::is_base_of<Event<T>,T>::value, "VEmitter<T>: T must be a class derived from Event<T>");
        }

        template<typename T>
        VEmitter<T>::~VEmitter()
        {
            for(auto&& handler : _handlers)
                handler->_unregister(this);
            _handlers.clear();
        }

        template<typename T>
        void VEmitter<T>::emit(const T& event)
        {
            for(auto&& handler : _handlers)
                handler->exec(this,event);
        }

        template<typename T>
        void VEmitter<T>::_register(VEventHandler<T>* handler)
        {
            _handlers.emplace_back(handler);
        }

        template<typename T>
        void VEmitter<T>::_unregister(VEventHandler<T>* handler)
        {
            _handlers.remove(handler);
        }

        ////////////////// Event /////////////////////
        template <typename ... Args>
        Emitter<Args ...>::Emitter()
        {
        }

        template <typename ... Args>
        Emitter<Args ...>::~Emitter()
        {
        }

        template <typename ... Args>
        template <typename T>
        void Emitter<Args ...>::emit(const T& event)
        {
            static_assert(std::is_base_of<Event<T>,T>::value, "T must be a class derived from Event<T>");
            static_assert(std::is_base_of<VEmitter<T>,Emitter<Args ...>>::value, "T must be an Event<T> calss based managed by the Emitter");

            VEmitter<T>::emit(event);

        }

    }

}
