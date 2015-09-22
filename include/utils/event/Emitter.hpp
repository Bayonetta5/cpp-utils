#ifndef EVENT_EMITTER_HPP
#define EVENT_EMITTER_HPP

#include <list>
#include <functional>
#include <memory>

namespace utils
{

    /**
     * \brief The namespace that contain all the event functionalities
     */
namespace event
{
    template<typename> class VEventHandler;

    template<typename> class Event;

    /**
     * \brief This class is used to send an event of type T
     */
    template<typename T>
    class VEmitter
    {
        public:
            VEmitter();

            /**
             * \brief automaticly unregister all the handlers
             */
            virtual ~VEmitter();

            /**
             * \brief Send an event
             * \param event the event to send
             */
            void emit(const T& event);

        private:
            friend class VEventHandler<T>;

            void _register(VEventHandler<T>* handler);
            void _unregister(VEventHandler<T>* handler);

            std::list<VEventHandler<T>*> _handlers;
    };

    template<typename ... Args>
    class Emitter : public VEmitter<Args>...
    {
        public:
            Emitter();

            /**
             * \brief automaticly unregister all the handlers
             */
            virtual ~Emitter();

            /**
             * \brief Send an event
             * \param event the event to send
             */
            template <typename T>
            void emit(const T& event);
    };
}
}

#include <utils/event/Emitter.tpl>

#endif
