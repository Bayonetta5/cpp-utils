#ifndef EVENT_PRIV_VEVENTHANDLER_HPP
#define EVENT_PRIV_VEVENTHANDLER_HPP

#include <list>

namespace utils
{
namespace event
{
    class EventBus;

    namespace priv
    {
        class VEventHandler
        {
            public:
                VEventHandler(const VEventHandler&) = delete;
                VEventHandler& operator=(const VEventHandler&) = delete;

                virtual ~VEventHandler();

            protected:
                VEventHandler(unsigned int family);
                
            private:
                friend class ::utils::event::EventBus;

                void _register(EventBus* bus);
                void _unregister(EventBus* bus);

                const unsigned int _family;
                std::list<EventBus*> _bus;
        };
    }
}
}
#endif
