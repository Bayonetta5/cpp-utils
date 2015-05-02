#ifndef EVENT_EVENTHANDLER_HPP
#define EVENT_EVENTHANDLER_HPP

#include <unordered_map>
#include <functional>

#include <utils/event/VEventHandler.hpp>

namespace utils
{
namespace event
{
    template<typename T> class Emitter;
    class EventBus;

    template<typename T>
    class EventHandler : public ::utils::event::priv::VEventHandler
    {
        public:

            using FuncType = std::function<void(T&)>;

            EventHandler();
            EventHandler(const FuncType& callback);

            template<typename U>
            EventHandler(void (U::*method)(T&) );

            virtual ~EventHandler();

            void connect(Emitter<T>& emitter);
            void connect(Emitter<T>& emitter,const FuncType& callback);
            void disconnect(Emitter<T>& emitter);

        private:
            friend class Emitter<T>;
            friend class EventBus;

            void _register(Emitter<T>* emitter);
            void _register(Emitter<T>* emitter,const FuncType& callback);
            void _unregister(Emitter<T>* emitter);

            void exec(Emitter<T>*emitter,T& event);
            void exec(T& event);

            std::unordered_map<Emitter<T>*,const FuncType> _emitters;
            const FuncType _callback;
    };
}
}

#include <utils/event/EventHandler.tpl>

#endif
