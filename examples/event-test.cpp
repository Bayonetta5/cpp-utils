#include <string>
#include <iostream>

#include <utils/events.hpp>

using namespace utils;

class TestEvent : public event::Event<TestEvent>
{
    public:
        TestEvent(int i, std::string str) : _i(i), _str(str){};

        friend std::ostream& operator<<(std::ostream& stream,const TestEvent& self)
        {
            stream<<"family= "<<self.family()<<", _i= "<<self._i<<", _str= "<<self._str;
            return stream;
        }

    private:
        int _i;
        std::string _str;
};

class TestEvent2 : public event::Event<TestEvent2>
{
    public:
        TestEvent2(std::string str) : _str(str){};

        friend std::ostream& operator<<(std::ostream& stream,const TestEvent2& self)
        {
            stream<<"family= "<<self.family()<<", _str= "<<self._str;
            return stream;
        }

    private:
        std::string _str;
};

class HandlerClass : public event::EventHandler<TestEvent>
{
    public:
        static void onEvent(const TestEvent& event)
        {
            std::cout<<"HandlerClass::onEvent("<<event<<")"<<std::endl;
        }

         HandlerClass() : event::EventHandler<TestEvent>(&HandlerClass::onEvent)
        {
        };
};


void guiTest();


int main(int argc,char* argv[])
{
    //object to object link
    std::cout<<"++++++++++++ Use direct link +++++++++++"<<std::endl;
    {
        TestEvent event(42,"TestEvent");
        std::cout<<event<<std::endl;

        event::EventHandler<TestEvent> handler([](const TestEvent& event){
            std::cout<<"handler default function: "<<event<<std::endl;
        });
        event::Emitter<TestEvent> emitter1;

        {
            std::cout<<std::endl<<"------ handler should receive nothing ------"<<std::endl;

            std::cout<<"-- emit by &ref "<<std::endl;
            emitter1.emit(event);
            std::cout<<"-- emit by &&ref "<<std::endl;
            emitter1.emit(TestEvent(48,"pwet 2"));
        }

        {
            std::cout<<std::endl<<"------ handler should receive events ------"<<std::endl;
            handler.connect(emitter1);
            emitter1.emit(event);
        }

        {
            std::cout<<std::endl<<"------ handler should receive nothing ------"<<std::endl;
            handler.disconnect(emitter1);
            emitter1.emit(event);
        }

        {
            std::cout<<std::endl<<"------ handlers 1,2 should receive events from 1, and handlers2 from emitter2 ------"<<std::endl;
            event::EventHandler<TestEvent> handler2;

            event::Emitter<TestEvent> emitter2;

            handler.connect(emitter1);

            handler2.connect(emitter1,[](const TestEvent& event){
                std::cout<<"handler2 from emitter1: "<<event<<std::endl;
            });
            handler2.connect(emitter2,[](const TestEvent& event){
                std::cout<<"handler2 from emitter2: "<<event<<std::endl;
            });
            emitter1.emit(event);
            emitter2.emit(event);

            handler.disconnect(emitter1);
        }

        {
            std::cout<<std::endl<<"------ handlers class should receive events ------"<<std::endl;

            HandlerClass handlerClass;
            handlerClass.connect(emitter1);

            emitter1.emit(event);
        }


        std::cout<<"------------- Nothing should handle this event -------"<<std::endl;
        emitter1.emit(event);
    }

    //event throught bus
    std::cout<<"\n++++++++++++ Use bus as link +++++++++++"<<std::endl;
    {
        event::EventBus bus;

        TestEvent event(67,"Event 2");
        event::EventHandler<TestEvent> handler([](const TestEvent& event){
            std::cout<<"handler default function: "<<event<<std::endl;
        });

        bus.connect<TestEvent>(handler);

        std::cout<<"------ handler  (default) class should receive event ------"<<std::endl;

        bus.emit(event);
    }

    guiTest();

    return 0;
}


class Button;

class ButtonClickedEvent : public event::Event<ButtonClickedEvent>
{
    public :
        ButtonClickedEvent(Button& owner) : _owner(owner)
        {
        }
        
        Button& _owner;
};

class ButtonReleaseEvent : public event::Event<ButtonReleaseEvent>
{
    public :
        ButtonReleaseEvent(Button& owner) : _owner(owner)
        {
        }
        
        Button& _owner;
};


class Button : public event::Emitter<ButtonClickedEvent,ButtonReleaseEvent>
{
    public:

        void click()
        {
            std::cout<<"emit ButtonClickedEvent"<<std::endl;
            event::VEmitter<ButtonClickedEvent>::emit(ButtonClickedEvent(*this));
            std::cout<<"end ButtonClickedEvent propagation"<<std::endl;
        }

        void release()
        {
            std::cout<<"emit ButtonReleaseEvent"<<std::endl;
            event::VEmitter<ButtonReleaseEvent>::emit(ButtonReleaseEvent(*this));
            std::cout<<"end ButtonReleaseEvent propagation"<<std::endl;
        }
};


class ButtonHandler : public event::EventHandler<ButtonClickedEvent,ButtonReleaseEvent>
{
    public:
        ButtonHandler() /*: event::EventHandler<ButtonClickedEvent>(&ButtonHandler::onEventClicked&ButtonHandler::onEventReleased)*/

        {
        }
    
        void onEventClicked(const ButtonClickedEvent& event)
        {
            std::cout<<" * EVENT : Button clicked received"<<std::endl;
        }

        void onEventReleased(const ButtonReleaseEvent& event)
        {
            std::cout<<"* EVENT : Button released received"<<std::endl;
        }
};


void guiTest()
{
    std::cout<<"+++++++++++++ GUI test +++++++++++++++"<<std::endl;

    {
        std::cout<<"\n--- No receiver ---"<<std::endl;

        Button btn;
        btn.click();
        btn.release();
    }

    {
        std::cout<<"\n---  Receiver  Clicked only---"<<std::endl;

        Button btn;
        event::EventHandler<ButtonClickedEvent> handlerClicked([](const ButtonClickedEvent& event){
                std::cout<<" * EVENT : Button clicked received"<<std::endl;
        });
        handlerClicked.connect(btn);

        btn.click();
        btn.release();
    }

    {
        std::cout<<"\n---  Receiver  Released only---"<<std::endl;

        Button btn;
        event::EventHandler<ButtonReleaseEvent> handlerReleased([](const ButtonReleaseEvent event){
                std::cout<<"* EVENT : Button released received"<<std::endl;
        });
        handlerReleased.connect(btn);

        btn.click();
        btn.release();
    }

    {
        std::cout<<"\n---  Receiver Clicked and Released ---"<<std::endl;

        Button btn;
        event::EventHandler<ButtonClickedEvent> handlerClicked([](const ButtonClickedEvent& event){
                std::cout<<"* EVENT : Button clicked received"<<std::endl;
        });
        handlerClicked.connect(btn);

        event::EventHandler<ButtonReleaseEvent> handlerReleased([](const ButtonReleaseEvent& event){
                std::cout<<"* EVENT : Button released received"<<std::endl;
        });
        handlerReleased.connect(btn);

        btn.click();
        btn.release();
    }

    {
        std::cout<<"\n---  Receiver Clicked and Released without member functions---"<<std::endl;

        Button btn;
        event::EventHandler<ButtonClickedEvent> handlerClicked([](const ButtonClickedEvent& event){
                std::cout<<"* EVENT : Button clicked received"<<std::endl;
        });
        handlerClicked.connect(btn);

        event::EventHandler<ButtonReleaseEvent> handlerReleased([](const ButtonReleaseEvent& event){
                std::cout<<"* EVENT : Button released received"<<std::endl;
        });
        handlerReleased.connect(btn);

        btn.emit(ButtonClickedEvent(btn));
        btn.emit(ButtonReleaseEvent(btn));
    }

    {
        std::cout<<"\n---  Receiver Clicked and Released with handler class---"<<std::endl;

        Button btn;
        ButtonHandler handler;
        handler.connect(btn);

        btn.click();
        btn.release();
    }

}
