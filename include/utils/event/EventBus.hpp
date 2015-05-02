#ifndef EVENT_EVENTBUS_HPP
#define EVENT_EVENTBUS_HPP

#include <list>
#include <unordered_map>

namespace utils
{

namespace event
{
    namespace priv
    {
        class VEventHandler;
    }

    template<typename> class EventHandler;

    class EventBus
    {
        public:
            ~EventBus();

            template<typename T>
            void connect(EventHandler<T>& handler);

            /*template<typename T>
            void connect(EventHandler<T>& handler,const std::function<void(T& event)>& callback);*/


            template<typename T>
            void disconnect(EventHandler<T>& handler);

            template<typename T>
            void emit(T& event);
        private:

            friend class ::utils::event::priv::VEventHandler;

            void _unregister(unsigned int family,::utils::event::priv::VEventHandler* handler);

            std::unordered_map<unsigned int,std::list<::utils::event::priv::VEventHandler*>> _handlers;
    };
}
}

#include <utils/event/EventBus.tpl>
#endif
