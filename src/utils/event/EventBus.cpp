#include <utils/event/EventBus.hpp>
#include <utils/event/VEventHandler.hpp>

namespace utils
{
namespace event
{

    EventBus::~EventBus()
    {
        for(auto&& pair : _handlers)
        {
            for(auto&& handler : pair.second)
                handler->_unregister(this);
        }
    }

    void EventBus::connect(priv::VEventHandler& handler)
    {
        handler._register(this);
        _handlers[handler._family].emplace_back(&handler);

    }

    void EventBus::disconnect(priv::VEventHandler& handler)
    {
        handler._unregister(this);
        _unregister(handler._family,&handler);
    }


    void EventBus::_unregister(unsigned int family,::utils::event::priv::VEventHandler* handler)
    {
        _handlers[family].remove(handler);
    }
}
}
