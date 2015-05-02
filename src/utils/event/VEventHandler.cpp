#include <utils/event/VEventHandler.hpp>
#include <utils/event/EventBus.hpp>

namespace utils
{
namespace event
{
    namespace priv
    {
        VEventHandler::VEventHandler(unsigned int family) : _family(family)
        {
        }

        VEventHandler::~VEventHandler()
        {
            for(auto&& bus : _bus)
                bus->_unregister(_family,this);
        }

        void VEventHandler::_register(EventBus* bus)
        {
            _bus.emplace_back(bus);
        }

        void VEventHandler::_unregister(EventBus* bus)
        {
            _bus.remove(bus);
        }
    }
}
}
