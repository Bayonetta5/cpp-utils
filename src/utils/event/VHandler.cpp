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
                p.second.clear();
                p.first->_unregister(this);
            }
            _callbacks.clear();
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
