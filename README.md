cpp-utils
========

add some usefull missing functions in the stl.

adds: 

* string manipulation (0.1.0)
* maths (0.0.1)
* system info (0.1.0)
* logs functions (0.1.0)
* json parser (0.1.2)
* Thread pool (0.1.3)
* Kernel function for learning machin (0.1.4)
* Function manipulation (0.1.5)
* Run time compilation as shared library (0.1.6)
* shared library loading and function management (0.1.6)
* Gnuplot (0.1.7)
* Event system (0.2.1)


See exemples/ for exemples

utils::string
=============

String manipulation

* split
* join(del,...)
* replace


utils::maths
============

Maths functions

* sign(T)
* min(...)
* max(...)
* abs(T)


utils::maths::ker
=================

* inline double uniform(double)
* inline double triangular(double)
* inline double epanechnikov(double)
* inline double quartic(double)
* inline double triweight(double)
* inline double tricube(double)
* inline double gaussian(double,double=1,double=0)
* inline double cosine(double)
* inline double mul(double,double)
* inline double div(double,double)
* inline double add(double,double)
* inline double sub(double,double)


utils::log
==========

Print
-----

Print message on console with color on unix.

* todo(...)
* info(...)
* warning(...)
* error(...)
* critical(...), critical(int c,...) //call exit if c != 0
* log(type, ...) 

utils::log::format
------------------

You can used them on a ostream object with orerator <<.

* bold
* dim
* underline
* blink
* reverse
* hidden
* strikeout
* reset[type]

utils::log::colors
------------------

Change the texte color.
As format, you can use them with operator << on ostream objects;

* black
* red
* green
* yellow
* blue
* magenta
* cyan
* light_gray
* dark_gray
* light_red
* light_green
* light_yellow
* light_blue
* light_magenta
* light_cyan
* white
* reset


utils::log::bg
--------------

As Color, but change the background color.
The same colors name are defines.


utils::json
===========

A json parser.
Need flex and bison.
Can be disable in cmake, and is build as a different lib.

To parse a file (see examples/json-test.cpp)

```c++
#include <utils/json/Driver.hpp>

int main(int argc,char* argv[])
{
    utils::json::Value* v = utils::json::Driver::parse_file(argv[1]);
    std::cout<<*v<<std::endl;
    return 0;
}
```

utils::json::Value
------------------

Represent a single value.

* Type getType()const;
* long double& as_float();
* long long int& as_int();
* bool& as_bool();
* std::string& as_string();
* Object& as_object();
* Array& as_array();
* cast operators
* operator<<(std::ostream& stream, const Value& self);


utils::json::Object
-------------------

Representation of a object.

* Value& operator\[\](const std::string&)
* const Value& operator\[\](const std::string&)const 
* std::unordered_map\<std::string, Value\>::const_iterator begin() const;
* std::unordered_map\<std::string, Value\>::const_iterator end() const;
* std::unordered_map\<std::string, Value\>::iterator begin();
* std::unordered_map\<std::string, Value\>::iterator end();
* size_t size() const;
* operator<<(std::ostream& stream, const Object& self);


utils::json::Array
------------------

Represent a json array. Internalty, it's a list.

* std::list\<Values\> values
* operator<<(std::ostream& stream, const Array& self);


utils::thread::Pool
-------------------

Represent a thread pool.

* Pool(size_t number)
* template\<typename F\>void push(F f)
* size_t size();
* void wait(std::chrono::milliseconds d =std::chrono::milliseconds(500));

utils::func
-----------

* apply the c++14 feature
* VFunc a virtual class for function
* Func\<Ret,Args ...\> specified class for function. Extands VFunc
* make_func(f) return a Func of the good type for f



utils::event
============

``` c++
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

class HandlerClass : public event::EventHandler<TestEvent>
{
    public:
        void onEvent(TestEvent& event)
        {
            std::cout<<"HandlerClass::onEvent("<<event<<")"<<std::endl;
        }

         HandlerClass() : EventHandler(&HandlerClass::onEvent)
        {
        };
};

int main(int argc,char* argv[])
{
    //object to object link
    std::cout<<"++++++++++++ Use direct link +++++++++++"<<std::endl;
    {
        TestEvent event(42,"TestEvent");
        std::cout<<event<<std::endl;

        event::EventHandler<TestEvent> handler([](TestEvent& event){
            std::cout<<"handler default function: "<<event<<std::endl;
        });
        event::Emitter<TestEvent> emitter1;

        {
            std::cout<<std::endl<<"------ handler should receive events ------"<<std::endl;
            handler.connect(emitter1);
            emitter1.emit(event);
        }

        {
            std::cout<<std::endl<<"------ handlers 1,2 should receive events from 1, and handlers2 from emitter2 ------"<<std::endl;
            event::EventHandler<TestEvent> handler2;

            event::Emitter<TestEvent> emitter2;

            handler.connect(emitter1);

            handler2.connect(emitter1,[](TestEvent& event){
                std::cout<<"handler2 from emitter1: "<<event<<std::endl;
            });
            handler2.connect(emitter2,[](TestEvent& event){
                std::cout<<"handler2 from emitter2: "<<event<<std::endl;
            });
            emitter1.emit(event);
            emitter2.emit(event);

            handler.disconnect(emitter1);
        }

        {
            std::cout<<"------------- Test with lambda instdead of handler-------"<<std::endl;
            emitter1.connect([](TestEvent& event){
                std::cout<<"handler is a lambda"<<std::endl;
            });
            emitter1.emit(event);
            emitter1.clearLambdas();

        }
    }


    //event throught bus
    std::cout<<"++++++++++++ Use bus as link +++++++++++"<<std::endl;
    {
        event::EventBus bus;

        TestEvent event(67,"Event 2");
        event::EventHandler<TestEvent> handler([](TestEvent& event){
            std::cout<<"handler default function: "<<event<<std::endl;
        });

        bus.connect<TestEvent>(handler);
        //bus.connect<TestEvent>(handler,[](TestEvent& event){
        //    std::cout<<"bus connect function: "<<event<<std::endl;
        //});

        std::cout<<std::endl<<"------ handler  (default) class should receive event ------"<<std::endl;

        bus.emit(event);
    }

    
    return 0;
}

```











