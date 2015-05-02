#ifndef EVENT_EMITTER_HPP
#define EVENT_EMITTER_HPP

#include <list>

namespace utils
{

namespace event
{
    template<typename> class EventHandler;

    template<typename> class Event;

    template<typename T>
    class Emitter
    {
        public:

            Emitter();
            virtual ~Emitter();

            void emit(T& event);

            void emit(T&& event);

            template<typename ... Args>
            void emit(Args&& ... args);

            void connect(EventHandler<T>& handler);
            void disconnect(EventHandler<T>& handler);

        private:
            friend class EventHandler<T>;

            void _register(EventHandler<T>* handler);
            void _unregister(EventHandler<T>* handler);

            std::list<EventHandler<T>*> _handlers;
    };
}
}

#include <utils/event/Emitter.tpl>

#endif
