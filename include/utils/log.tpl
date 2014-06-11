#include <iostream>

namespace utils
{
namespace log
{
    /////////// HELPERS ////////////////////
    void __out_helper(std::ostream& out);

    template <typename T,typename ... Args>
    void __out_helper(std::ostream& out,const T& p,const Args& ... args)
    {
        out<<" "<<p;
        __out_helper(out,args ...);
    }

    ////////////// TODO //////////////////////
    template <typename T>
    void todo(const T& msg)
    {
        std::clog<<colors::yellow<<time
            <<msg
            <<colors::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void todo(const T& type,const Args& ... args)
    {
        std::clog<<colors::yellow<<time<<"["<<type<<"]";
        __out_helper(std::clog,args ...);
        std::clog<<colors::reset<<std::endl;
    }
    //////////////////// info //////////////////////
    template <typename T>
    void info(const T& msg)
    {
        std::clog<<colors::light_cyan<<time
            <<msg
            <<colors::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void info(const T& type,const Args& ... args)
    {
        std::clog<<colors::light_cyan<<time<<"["<<type<<"]";
        __out_helper(std::clog,args ...);
        std::clog<<colors::reset<<std::endl;
    }

    //////////////////// ok //////////////////////
    template <typename T>
    void ok(const T& msg)
    {
        std::clog<<colors::green<<time
            <<msg
            <<colors::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void ok(const T& type,const Args& ... args)
    {
        std::clog<<colors::green<<time<<"["<<type<<"]";
        __out_helper(std::clog,args ...);
        std::clog<<colors::reset<<std::endl;
    }

    /////////// WARNING //////////////
    template <typename T>
    void warning(const T& msg)
    {
        std::clog<<colors::magenta<<time
            <<msg
            <<colors::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void warning(const T& type,const Args& ... args)
    {
        std::clog<<colors::magenta<<time<<"["<<type<<"]";
        __out_helper(std::clog,args ...);
        std::clog<<colors::reset<<std::endl;
    }
    ////////////// ERROR ///////////////
    template <typename T>
    void error(const T& msg)
    {
        std::clog<<colors::light_red<<time
            <<msg
            <<colors::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void error(const T& type,const Args& ... args)
    {
        std::clog<<colors::light_red<<time<<"["<<type<<"]";
        __out_helper(std::clog,args ...);
        std::clog<<colors::reset<<std::endl;
    }
    ///////////////// CRITICAL ///////////////
    template <typename T>
    void critical(const T& msg)
    {
        std::clog<<format::bold<<bg::red<<time
            <<msg
            <<format::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void critical(const T& type,const Args& ... args)
    {
        std::clog<<format::bold<<bg::red<<time<<"["<<type<<"]"<<type;
        __out_helper(std::clog,args ...);
        std::clog<<format::reset<<std::endl;
    }

    template <typename T,typename ... Args>
    void critical(int code,const T& type,const Args& ... args)
    {
        if(code != 0)
        {
            critical(type,args...,". Exit with code:",code);
            exit(code);
        }
        else
            critical(type,args...);
    }


    template <typename ... Args>
    void log(LOG_LVL lvl,Args&& ... args)
    {
        switch(lvl)
        {
            case TODO:
                todo(args ...);break;
            case INFO:
                info(args...);break;
            case WARNING:
                warning(args ...);break;
            case ERROR:
                error(args ...); break;
            case CRITICAL:
                critical(args ...);break;
            default:
                error("utils::log::log()","Unknow value of lvl. Message show as info:");
                info(args ...);
                break;

        }
    }
}
}
