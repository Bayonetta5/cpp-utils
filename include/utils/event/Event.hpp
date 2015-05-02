#ifndef EVENT_EVENT_HPP
#define EVENT_EVENT_HPP

#include <utils/event/VEvent.hpp>

namespace utils
{
namespace event
{
    template<typename T>
    class Event : public priv::VEvent
    {
        public:
            Event(const Event<T>&) = default;
            Event& operator=(const Event<T>&) = default;

            Event() = default;
            ~Event() = default;

            static unsigned int family();
    };
}
}

#include <utils/event/Event.tpl>

#endif
