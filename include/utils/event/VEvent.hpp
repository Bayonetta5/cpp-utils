#ifndef EVENT_PRIV_VEVENT_HPP
#define EVENT_PRIV_VEVENT_HPP
namespace utils
{
namespace event
{
    namespace priv
    {
        class VEvent
        {
            public:
                VEvent(const VEvent&) = default;
                VEvent& operator=(const VEvent&) = default;

                virtual ~VEvent() = default;


            protected:
                static unsigned int _familyCounter;
                VEvent() = default;
        };

    }
}
}
#endif
