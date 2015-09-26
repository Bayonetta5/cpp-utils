#include <utils/event/VEmitter.hpp>
#include <utils/event/VEvent.hpp>

namespace utils
{
    namespace event
    {
        
        VEmitter::VEmitter()
        {
        }

        VEmitter::~VEmitter()
        {
            std::set<Handler*> handlers;
            for(auto& p : _handlers)
            {
                handlers.insert(p.second.begin(),p.second.end());
            }

            for(Handler* h: handlers)
            {
                h->_unregister(this);
            }
        }

        bool VEmitter::emit(const VEvent& event) const
        {
            return event._dispatch(*this);
        }


        ////////////////// PRIVATE //////////////

        void VEmitter::_register(const Handler* handler, unsigned int family)
        {
            _handlers[family].insert(const_cast<Handler*>(handler));
        }

        void VEmitter::_unregister(const Handler* handler, unsigned int family)
        {
            std::set<Handler*>& l = _handlers[family];
            auto it = l.find(const_cast<Handler*>(handler));
            if(it != l.end())
                l.erase(it);
        }

    }
}
