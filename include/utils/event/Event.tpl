namespace utils
{
namespace event
{
    template<typename T>
    Event<T>::Event()
    {
    }

    template<typename T>
    Event<T>::~Event()
    {
    }

    template<typename T>
    unsigned int Event<T>::family()
    {
        static unsigned int family = VEvent::_familyCounter++;
        return family;
    };

}
}
