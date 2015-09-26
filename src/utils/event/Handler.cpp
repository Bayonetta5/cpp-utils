#include <utils/event/Handler.hpp>
#include <utils/event/VEmitter.hpp>

namespace utils
{
    namespace event
    {
        
        Handler::Handler()
        {
        }

        Handler::~Handler()
        {
            for(auto& p : _callbacks)
            {
                for(auto& p2 : p.second)
                {
                    p.first->_unregister(this,p2.first);
                }
                p.second.clear();
            }
            _callbacks.clear();
        }

        void Handler::_unregister(const VEmitter* emitter)
        {
            _callbacks.erase(const_cast<VEmitter*>(emitter));
        }
        
        //////////// PROTECTED /////////////////
        
        Handler::VFunction::VFunction()
        {
        }

        Handler::VFunction::~VFunction()
        {
        }
    }
}
