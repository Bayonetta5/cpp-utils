#ifndef UTILS_EVENT_VEMITTER_HPP
#define UTILS_EVENT_VEMITTER_HPP

#include <unordered_map>
#include <set>
#include <cassert>

#include <utils/event/Handler.hpp>

namespace utils
{
    namespace event
    {
        class VEvent;

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

                void _register(const Handler* handler,unsigned int family);
                void _unregister(const Handler* handler,unsigned int family);

                virtual bool _checkFamily(unsigned int family)const = 0;

                std::unordered_map<unsigned int,std::set<Handler*>> _handlers;
        };
    }
}
#include <utils/event/VEmitter.tpl>
#endif
