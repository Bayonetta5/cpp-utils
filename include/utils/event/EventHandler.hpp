#ifndef EVENT_EVENTHANDLER_HPP
#define EVENT_EVENTHANDLER_HPP

#include <unordered_map>
#include <functional>

#include <utils/event/VEventHandler.hpp>

namespace utils
{
namespace event
{
    template<typename T> class Emitter;
    class EventBus;

    /**
     * \brief A class that can handel an event of type T.
     */
    template<typename T>
    class EventHandler : public ::utils::event::priv::VEventHandler
    {
        public:

            using FuncType = std::function<void(T&)>;

            /**
             * \brief construct a EventHandler with no default behaviour
             */
            EventHandler();

            /**
             * \brief construct a EventHandler with callback as default behaviour
             * \param callback the default behaviour of the handler
             */
            EventHandler(const FuncType& callback);

            /**
             * \brief construct an EventHandler with method as default behaviour
             * \param method is a method of the henerited class called to this.
             */
            template<typename U>
            EventHandler(void (U::*method)(T&) );

            virtual ~EventHandler();

            /**
             * \brief connect emitter with the default callback from the constructor
             * \param emitter the emitter to connect with
             */
            void connect(Emitter<T>& emitter);

            /**
             * \brief connect emitter with the callback as parameter
             * \param emitter the emitter to connect with
             * \param callback the specific callback to use
             */
            void connect(Emitter<T>& emitter,const FuncType& callback);

            /**
             * \brief remove the emitter from the manager list
             * \param emitter Emitter to remove
             */
            void disconnect(Emitter<T>& emitter);

        private:
            friend class Emitter<T>;
            friend class EventBus;

            void _register(Emitter<T>* emitter);
            void _register(Emitter<T>* emitter,const FuncType& callback);
            void _unregister(Emitter<T>* emitter);

            void exec(Emitter<T>*emitter,T& event);
            void exec(T& event);

            std::unordered_map<Emitter<T>*,const FuncType> _emitters;
            const FuncType _callback;
    };
}
}

#include <utils/event/EventHandler.tpl>

#endif
