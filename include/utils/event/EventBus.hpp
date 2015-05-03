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

    /**
     * \brief A class that can link multiple Emitters and multiple EventHandlers
     */
    class EventBus
    {
        public:
            ~EventBus();

            /**
             * \brief add an EventHandler to manage.
             */
            template<typename T>
            void connect(EventHandler<T>& handler);

            /*template<typename T>
            void connect(EventHandler<T>& handler,const std::function<void(T& event)>& callback);*/

            /**
             * \brief remove an EventHandler from the managed handlers
             */
            template<typename T>
            void disconnect(EventHandler<T>& handler);

            /**
             * \brief send an event througth the bus to all the manager EventHandler
             */
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
