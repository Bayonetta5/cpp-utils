#ifndef EVENT_EVENT_HPP
#define EVENT_EVENT_HPP

#include <utils/event/VEvent.hpp>

namespace utils
{
namespace event
{
    /**
     * \brief A class that represent an Event. T is the parent class template parameter
     */
    template<typename T>
    class Event : public priv::VEvent
    {
        public:
            Event(const Event<T>&) = default;
            Event& operator=(const Event<T>&) = default;

            Event();
            virtual ~Event();


            /**
             * \brief internal class unique id
             * \return the unique id of the event class
             */
            static unsigned int family();
    };
}
}

#include <utils/event/Event.tpl>

#endif
