#include <type_traits>
#include <utils/event/EventHandler.hpp>

namespace utils
{
    namespace event
    {
        template<typename T>
        Emitter<T>::Emitter()
        {
            static_assert(std::is_base_of<Event<T>,T>::value, "Emitter<T>: T must be a class derived from Event<T>");
        }

        template<typename T>
        Emitter<T>::~Emitter()
        {
            for(auto&& handler : _handlers)
                handler->_unregister(this);
            _handlers.clear();

            clearLambdas();
        }

        template<typename T>
        void Emitter<T>::emit(T& event)
        {
            for(auto&& handler : _handlers)
                handler->exec(this,event);

            for(auto&& handler : _myHandlers)
                handler->exec(event);
        }

        template<typename T>
        void Emitter<T>::emit(T&& event)
        {
            emit(event);
        }

        template<typename T>
        template<typename ... Args>
        void Emitter<T>::emit(Args&& ... args)
        {
            T e(std::forward<Args>(args)...);
            emit(e);
        }


        template<typename T>
        void Emitter<T>::connect(EventHandler<T>& handler)
        {
             handler._register(this);
            _register(&handler);
        }

        template<typename T>
        void Emitter<T>::disconnect(EventHandler<T>& handler)
        {
            handler._unregister(this);
            _unregister(&handler);
        }

        template<typename T>
        template<typename ... Args>
        std::shared_ptr<EventHandler<T>> Emitter<T>::connect(Args&& ... args)
        {
            std::shared_ptr<EventHandler<T>> h(new EventHandler<T>(std::forward<Args&&>(args)...));
            _myHandlers.emplace_back(h);
            return h;
        }

        template<typename T>
        void Emitter<T>::disconnect(const std::shared_ptr<EventHandler<T>>& handler)
        {
            _myHandlers.remove(handler);
        }

        template<typename T>
        void Emitter<T>::clearLambdas()
        {
            for(auto&& handler : _myHandlers)
                handler->_unregister(this);
            _myHandlers.clear();
        }


        template<typename T>
        void Emitter<T>::_register(EventHandler<T>* handler)
        {
            _handlers.emplace_back(handler);
        }

        template<typename T>
        void Emitter<T>::_unregister(EventHandler<T>* handler)
        {
            _handlers.remove(handler);
        }
    }
}
