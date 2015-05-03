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
    template<typename> class EventHandler;

    template<typename> class Event;

    /**
     * \brief This class is used to send an event of type T
     */
    template<typename T>
    class Emitter
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
            void emit(T& event);

            /**
             * \brief Send an event
             * \param event the event to send
             */
            void emit(T&& event);

            /**
             * \brief Construct and send an event
             * \param args the envent constructor parameters
             */
            template<typename ... Args>
            void emit(Args&& ... args);

            /**
             * \brief connect an handler to the class. Eache time a call to
             * emit() is done, the handler will be executed
             */
            void connect(EventHandler<T>& handler);

            /**
             * \brief remove an handler
             */
            void disconnect(EventHandler<T>& handler);

            /**
             * \brief Add a function as an handler.
             * \param callback The function to execute when the event is trigger
             */
            void connect(const std::function<void(T&)>& callback);

            /**
             * \brief Remove all the lambdas functions
             */
            void clearLambdas();

        private:
            friend class EventHandler<T>;

            void _register(EventHandler<T>* handler);
            void _unregister(EventHandler<T>* handler);

            std::list<EventHandler<T>*> _handlers;
            std::list<std::function<void(T&)>> _lambdas;
    };
}
}

#include <utils/event/Emitter.tpl>

#endif
