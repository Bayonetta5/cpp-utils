namespace utils
{
    namespace event
    {
        
        template <typename T>
        bool Handler::connect(VEmitter& emitter)
        {
        }

        template <typename T>
        bool Handler::disconnect(VEmitter& emitter)
        {
        }

        //////////// PROTECTED /////////////////

        template <typename T>
        Handler::Function<T>::Function(const std::function<void(const T&)>& callback) : _callback(callback)
        {
        }

        template <typename T>
        Handler::Function<T>::~Function()
        {
        }

        template <typename T>
        void Handler::Function<T>::exec(const VEmitter& emitter,const VEvent& event)const
        {
            _callback(static_cast<const T&>(event));
        }

        //////////// PRIVATE /////////////////

        template <typename T>
        void Handler::_receive(const VEmitter& emitter,const T& event)const
        {
            auto it = _callbacks.find(const_cast<VEmitter*>(&emitter));
            if(it != _callbacks.end())
            {
                auto it2 = it->second.find(T::family());
                if(it2 != it->second.end())
                {
                    it2->second->exec(emitter,event);
                }
            }
        }
    }
}
