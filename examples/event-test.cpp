#include <string>
#include <iostream>

#include <utils/event.hpp>

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

class HandlerClass : public event::Handler
{
    public:
        static void onEvent(const TestEvent& event)
        {
            std::cout<<"HandlerClass::onEvent("<<event<<")"<<std::endl;
        }

        HandlerClass()
        {
            bind<TestEvent>(&HandlerClass::onEvent);
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

        event::Emitter<TestEvent> emitter1;

        event::Handler handler1([](const event::VEvent& event){
            std::cout<<"handler1 default function: "<<std::endl;
        });

        {
            std::cout<<std::endl<<"------ handler1 should receive nothing ------"<<std::endl;

            std::cout<<"-- emit by &ref "<<std::endl;
            emitter1.emit(event);
            std::cout<<"-- emit by &&ref "<<std::endl;
            emitter1.emit(TestEvent(48,"pwet 2"));
        }

        {
            std::cout<<std::endl<<"------ handler1 should receive 1 default event ------"<<std::endl;
            handler1.connect(emitter1);
            emitter1.emit(event);
        }

        {
            std::cout<<std::endl<<"------ handler1 should receive nothing ------"<<std::endl;
            handler1.disconnect(emitter1);
            emitter1.emit(event);
        }

        {
            std::cout<<std::endl<<"------ handlers 1,2 should receive events from 1, and handlers2 from emitter2 ------"<<std::endl;

            handler1.connect(emitter1);

            event::Handler handler2;
            event::Emitter<TestEvent> emitter2;

            handler2.connect<TestEvent>(emitter1,[](const TestEvent& event){
                std::cout<<"handler2 from emitter1: "<<event<<std::endl;
            });

            handler2.connect<TestEvent>(emitter2,[](const TestEvent& event){
                std::cout<<"handler2 from emitter2: "<<event<<std::endl;
            });

            std::cout<<" + emiter 1"<<std::endl;
            emitter1.emit(TestEvent(1,"emitter 1"));

            std::cout<<" + emiter 2"<<std::endl;
            emitter2.emit(TestEvent(2,"emitter 2"));

            handler1.disconnect(emitter1);

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
        event::Bus bus;

        TestEvent event(67,"Event 2");
        event::Handler handler([](const event::VEvent& event){
            std::cout<<"handler default function"<<std::endl;
        });

        handler.bind<TestEvent>([](const TestEvent& event){
            std::cout<<"handler TestEvent function: "<<event<<std::endl;
        });

        handler.connect(bus);

        std::cout<<"------ handler  (default) class should receive event ------"<<std::endl;

        bus.emit(event);
        bus.emit(TestEvent2("test event2"));
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
            emit(ButtonClickedEvent(*this));
            std::cout<<"end ButtonClickedEvent propagation"<<std::endl;
        }

        void release()
        {
            std::cout<<"emit ButtonReleaseEvent"<<std::endl;
            emit(ButtonReleaseEvent(*this));
            std::cout<<"end ButtonReleaseEvent propagation"<<std::endl;
        }
};


class ButtonHandler : public event::Handler
{
    public:
        ButtonHandler()
        {
            bind<ButtonClickedEvent>(&ButtonHandler::onEventClicked);
            bind<ButtonReleaseEvent>(&ButtonHandler::onEventReleased);
        }
    
        static void onEventClicked(const ButtonClickedEvent& event)
        {
            std::cout<<" * EVENT : Button clicked received"<<std::endl;
        }

        static void onEventReleased(const ButtonReleaseEvent& event)
        {
            std::cout<<" * EVENT : Button released received"<<std::endl;
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
        std::cout<<"\n--- One reciver but no callback ---"<<std::endl;

        Button btn;
        event::Handler handler;

        handler.connect(btn);

        btn.click();
        btn.release();
    }

    {
        std::cout<<"\n--- One reciver with default callback only ---"<<std::endl;

        Button btn;
        event::Handler handler([](const event::VEvent& event){
            std::cout<<" * EVENT : default received"<<std::endl;
        });

        handler.connect(btn);

        btn.click();
        btn.release();
    }

    {
        std::cout<<"\n---  Receiver  Clicked only ---"<<std::endl;

        Button btn;
        event::Handler handler;

        handler.bind<ButtonClickedEvent>([](const ButtonClickedEvent& event){
            std::cout<<" * EVENT : Button clicked received"<<std::endl;
        });

        handler.connect(btn);

        btn.click();
        btn.release();
    }

    {
        std::cout<<"\n---  Receiver  Clicked + default ---"<<std::endl;

        Button btn;
        event::Handler handler([](const event::VEvent& event){
            std::cout<<" * EVENT : default received"<<std::endl;
        });

        handler.bind<ButtonClickedEvent>([](const ButtonClickedEvent& event){
            std::cout<<" * EVENT : Button clicked received"<<std::endl;
        });

        handler.connect(btn);

        btn.click();
        btn.release();
    }

    {
        std::cout<<"\n---  Receiver  Released only---"<<std::endl;

        Button btn;

        event::Handler handler;
        handler.bind<ButtonReleaseEvent>([](const ButtonReleaseEvent event){
                std::cout<<" * EVENT : Button released received"<<std::endl;
        });

        handler.connect(btn);

        btn.click();
        btn.release();
    }

    {
        std::cout<<"\n---  Receiver Clicked and Released ---"<<std::endl;

        Button btn;

        event::Handler handler;
        handler.bind<ButtonClickedEvent>([](const ButtonClickedEvent& event){
            std::cout<<" * EVENT : Button clicked received"<<std::endl;
        });

        handler.bind<ButtonReleaseEvent>([](const ButtonReleaseEvent event){
                std::cout<<" * EVENT : Button released received"<<std::endl;
        });

        handler.connect(btn);


        btn.click();
        btn.release();
    }

    {
        std::cout<<"\n---  Receiver Clicked and Released without member functions---"<<std::endl;

        Button btn;

        event::Handler handler;
        handler.bind<ButtonClickedEvent>([](const ButtonClickedEvent& event){
            std::cout<<" * EVENT : Button clicked received"<<std::endl;
        });

        handler.bind<ButtonReleaseEvent>([](const ButtonReleaseEvent event){
                std::cout<<" * EVENT : Button released received"<<std::endl;
        });

        handler.connect(btn);

        btn.emit(ButtonClickedEvent(btn));
        btn.emit(ButtonReleaseEvent(btn));
        //btn.emit(TestEvent(42,"This event will rase an assert"));
    }

    {
        std::cout<<"\n--- Use handler class (Clicked and Released) ---"<<std::endl;

        Button btn;

        ButtonHandler handler;
        handler.connect(btn);

        btn.click();
        btn.release();
    }
}
