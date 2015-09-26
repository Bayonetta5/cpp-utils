#ifndef UTILS_EVENT_VHANDLER_HPP
#define UTILS_EVENT_VHANDLER_HPP

#include <unordered_map>
#include <memory>

namespace utils
{
    namespace event
    {
        class VEmitter;
        class VEvent;

        class Handler
        {
            public:
                Handler(const Handler&) = delete;
                Handler& operator=(const Handler&) = delete;

                Handler();
                virtual ~Handler();

                template <typename T>
                bool connect(VEmitter& emitter);

                template <typename T>
                bool disconnect(VEmitter& emitter);

            protected:
                class VFunction
                {
                    public:
                        VFunction();
                        virtual ~VFunction();
                        virtual void exec(const VEmitter& emitter,const VEvent& event)const = 0;  
                };

                template <typename T>
                class Function : public VFunction
                {
                    public :
                        Function(const std::function<void(const T&)>& callback);
                        virtual ~Function();

                        virtual void exec(const VEmitter& emitter,const VEvent& event)const override;
                    private:
                        std::function<void(const T&)> _callback;
                };


            private:
                friend class VEmitter;

                template <typename T>
                void _receive(const VEmitter& emitter,const T& event) const;

                std::unordered_map<VEmitter*,std::unordered_map<unsigned int,std::unique_ptr<VFunction>>> _callbacks;
        };
    }
}
#include <utils/event/Handler.tpl>
#endif
