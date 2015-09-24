#ifndef EVENT_EVENTHANDLER_HPP
#define EVENT_EVENTHANDLER_HPP

#include <unordered_map>
#include <functional>

#include <utils/event/VEventHandler.hpp>

namespace utils
{
namespace event
{
    template<typename ... Args> class Emitter;
    class EventBus;

    /**
     * \brief A class that can handel an event of type T.
     */
    template<typename T>
    class VEventHandler : public ::utils::event::priv::VEventHandler
    {
        public:

            VEventHandler(const VEventHandler<T>&) = delete;
            VEventHandler& operator=(const VEventHandler<T>&) = delete;

            using FuncType = std::function<void(const T&)>;//< callback type

            /**
             * \brief construct a VEventHandler with no default behaviour
             */
            explicit VEventHandler();

            /**
             * \brief construct a VEventHandler with callback as default behaviour
             * \param callback the default behaviour of the handler
             */
            explicit VEventHandler(const FuncType& callback);

            virtual ~VEventHandler();

            /**
             * \brief connect emitter with the default callback from the constructor
             * \param emitter the emitter to connect with
             */
            void connect(VEmitter<T>& emitter);

            /**
             * \brief connect emitter with the callback as parameter
             * \param emitter the emitter to connect with
             * \param callback the specific callback to use
             */
            void connect(VEmitter<T>& emitter,const FuncType& callback);

            /**
             * \brief remove the emitter from the manager list
             * \param emitter Emitter to remove
             */
            void disconnect(VEmitter<T>& emitter);

        private:
            friend class VEmitter<T>;
            friend class EventBus;

            void _register(VEmitter<T>* emitter);
            void _register(VEmitter<T>* emitter,const FuncType& callback);
            void _unregister(VEmitter<T>* emitter);

            void exec(VEmitter<T>*emitter,const T& event);
            void exec(T& event);

            std::unordered_map<VEmitter<T>*,const FuncType> _emitters;
            const FuncType _callback;
    };


    template <typename ... Args>
    class EventHandler : public VEventHandler<Args>...
    {
        public:
            EventHandler();

            EventHandler(const typename VEventHandler<Args>::FuncType& ... callbacks);

            /**
             * \brief connect emitter with the default callback from the constructor
             * \param emitter the emitter to connect with
             */
            template<typename ... Args2>
            void connect(Emitter<Args2...>& emitter);

            /**
             * \brief connect emitter with the callback as parameter
             * \param emitter the emitter to connect with
             * \param callback the specific callback to use
             */
            template<typename T>
            void connect(VEmitter<T>& emitter,const typename VEventHandler<T>::FuncType& callback);

            /**
             * \brief remove the emitter from the manager list
             * \param emitter Emitter to remove
             */
            template<typename T>
            void disconnect(VEmitter<T>& emitter);

    };
}
}

#include <utils/event/EventHandler.tpl>

#endif
