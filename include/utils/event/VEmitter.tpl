namespace utils
{
    namespace event
    {
        template <typename T>
        bool VEmitter::_dispatch(const T& event) const
        {
            bool res = _checkFamily(T::family());
            assert(res);

            for(Handler* handler: _handlers)
            {
                handler->_receive(*this,event);
            }
            return res;
        }
    }
}
