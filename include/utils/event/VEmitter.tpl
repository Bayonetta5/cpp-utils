namespace utils
{
    namespace event
    {
        template <typename T>
        bool VEmitter::_dispatch(const T& event) const
        {
            bool res = _checkFamily(T::family());
            assert(res);

            auto it = _handlers.find(T::family());
            if(it != _handlers.end())
            {
                for(Handler* handler: it->second)
                {
                    handler->_receive(*this,event);
                }
            }
            return res;
        }

        ////////////// HANDLERS /////////////////

        template <typename T>
        bool Handler::connect(VEmitter& emitter,const std::function<void(const T&)>& callback)
        {
            bool res = emitter._checkFamily(T::family());
            assert(res);

            emitter._register(this,T::family());
            _callbacks[&emitter][T::family()].reset(new Function<T>(callback));

            return res;
        }

        template <typename T>
        bool Handler::disconnect(VEmitter& emitter)
        {
            _callbacks[&emitter].erase(T::family());
        }
    }
}
