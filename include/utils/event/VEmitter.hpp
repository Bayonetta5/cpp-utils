#ifndef UTILS_EVENT_VEMITTER_HPP
#define UTILS_EVENT_VEMITTER_HPP

#include <list>
#include <cassert>

#include <utils/event/Handler.hpp>

namespace utils
{
    namespace event
    {
        class VEvent;

        /**
         * \brief This is the common class for all the Emitter
         */
        class VEmitter
        {
            public:
                VEmitter(const VEmitter&) = delete;
                VEmitter& operator=(const VEmitter&) = delete;

                VEmitter();
                virtual ~VEmitter();

                /**
                 * \brief Send an event
                 * \param event the event to send
                 */
                bool emit(const VEvent& event) const;

            private:
                template <typename> friend class Event;
                friend class Handler;

                template <typename T>
                bool _dispatch(const T& event) const; //< used by VEvent

                void _register(const Handler* handler); //< used by Handler
                void _unregister(const Handler* handler); //< used by Handler

                virtual bool _checkFamily(unsigned int family)const = 0; //< check if this class can deal with a type of event

                std::list<Handler*> _handlers;
        };
    }
}
#include <utils/event/VEmitter.tpl>
#endif
