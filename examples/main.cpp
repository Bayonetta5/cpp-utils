#include <iostream>

#include <utils/log.hpp>
void test_logs()
{

    {
        using namespace utils::log::format;
        std::cout<<bold<<"bold"<<reset_bold<<"reset_bold"<<std::endl;
        std::cout<<dim<<"dim"<<reset_dim<<"reset_dim"<<std::endl;
        std::cout<<underline<<"underline"<<reset_underline<<"reset_underline"<<std::endl;
        std::cout<<blink<<"blink"<<reset_blink<<"reset_blink"<<std::endl;
        std::cout<<reverse<<"reverse"<<reset_reverse<<"reset_reverse"<<std::endl;
        std::cout<<hidden<<"hidden"<<reset_hidden<<"reset_hidden"<<std::endl;
        std::cout<<strikeout<<"strikeout"<<reset_strikeout<<"reset_strikeout"<<std::endl;
    }

    
    {
        using namespace utils::log::colors;
        std::cout<<black<<"black"<<std::endl;
        std::cout<<red<<"red"<<std::endl;
        std::cout<<green<<"green"<<std::endl;
        std::cout<<yellow<<"yellow"<<std::endl;
        std::cout<<blue<<"blue"<<std::endl;
        std::cout<<magenta<<"magenta"<<std::endl;
        std::cout<<cyan<<"cyan"<<std::endl;
        std::cout<<light_gray<<"light_gray"<<std::endl;
        std::cout<<dark_gray<<"dark_gray"<<std::endl;
        std::cout<<light_red<<"light_red"<<std::endl;
        std::cout<<light_green<<"light_green"<<std::endl;
        std::cout<<light_yellow<<"light_yellow"<<std::endl;
        std::cout<<light_blue<<"light_blue"<<std::endl;
        std::cout<<light_magenta<<"light_magenta"<<std::endl;
        std::cout<<light_cyan<<"light_cyan"<<std::endl;
        std::cout<<white<<"white"<<std::endl;
        std::cout<<reset<<"reset"<<std::endl;
    }

    {
        using namespace utils::log::bg;
        std::cout<<black<<"black"<<std::endl;
        std::cout<<red<<"red"<<std::endl;
        std::cout<<green<<"green"<<std::endl;
        std::cout<<yellow<<"yellow"<<std::endl;
        std::cout<<blue<<"blue"<<std::endl;
        std::cout<<magenta<<"magenta"<<std::endl;
        std::cout<<cyan<<"cyan"<<std::endl;
        std::cout<<light_gray<<"light_gray"<<std::endl;
        std::cout<<dark_gray<<"dark_gray"<<std::endl;
        std::cout<<light_red<<"light_red"<<std::endl;
        std::cout<<light_green<<"light_green"<<std::endl;
        std::cout<<light_yellow<<"light_yellow"<<std::endl;
        std::cout<<light_blue<<"light_blue"<<std::endl;
        std::cout<<light_magenta<<"light_magenta"<<std::endl;
        std::cout<<light_cyan<<light_cyan<<std::endl;
        std::cout<<white<<"white"<<std::endl;
        std::cout<<reset<<"reset"<<std::endl;
    }

    {
        using namespace utils::log;
        todo("information test");
        todo("test_logs","information","test");

        info("information test");
        info("test_logs","information","test");

        warnning("information test");
        warnning("test_logs","information test");

        error("information test");
        error("test_logs","information test");

        critical("information test");
        critical("test_logs","information test");

        log(LOG_LVL::TODO,"information test");
        log(LOG_LVL::TODO,"test_logs","information test");

        log(LOG_LVL::INFO,"information test");
        log(LOG_LVL::INFO,"test_logs","information test");

        log(LOG_LVL::WARNNING,"information test");
        log(LOG_LVL::WARNNING,"test_logs","information test");

        log(LOG_LVL::ERROR,"information test");
        log(LOG_LVL::ERROR,"test_logs","information test");

        log(LOG_LVL::CRITICAL,"information test");
        log(LOG_LVL::CRITICAL,"test_logs","information test");
    }

}

#include <utils/maths.hpp>
void test_maths()
{
    using namespace utils::maths;
    std::cout<<"sign(-42)"<<sign(-42)<<std::endl;
    std::cout<<"sign(42)"<<sign(42)<<std::endl;
    std::cout<<"sign(0)"<<sign(0)<<std::endl;
    std::cout<<"sign(-42.8)"<<sign(-42.8)<<std::endl;
    std::cout<<"sign(42.8)"<<sign(42.8)<<std::endl;
    std::cout<<"sign(0.f)"<<sign(0.f)<<std::endl;

    std::cout<<"min(1,2)"<<min(1,2)<<std::endl;
    std::cout<<"min(-1,-2)"<<min(-1,-2)<<std::endl;
    std::cout<<"min(0,1)"<<min(0,1)<<std::endl;
    std::cout<<"min(-1,0)"<<min(-1,0)<<std::endl;
    std::cout<<"min(0,0)"<<min(0,0)<<std::endl;
    std::cout<<"min(1,2,2,3,4,5)"<<min(1,2,3,4,5)<<std::endl;
    std::cout<<"min(1,2,-12,4,5)"<<min(1,2,-12,4,5)<<std::endl;
    std::cout<<"min(1,2,3,4,-5)"<<min(1,2,-12,4,5)<<std::endl;

    std::cout<<"max(1,2)"<<max(1,2)<<std::endl;
    std::cout<<"max(-1,-2)"<<max(-1,-2)<<std::endl;
    std::cout<<"max(0,1)"<<max(0,1)<<std::endl;
    std::cout<<"max(-1,0)"<<max(-1,0)<<std::endl;
    std::cout<<"max(0,0)"<<max(0,0)<<std::endl;
    std::cout<<"max(1,2,2,3,4,5)"<<max(1,2,3,4,5)<<std::endl;
    std::cout<<"max(1,2,12,4,5)"<<max(1,2,-12,4,5)<<std::endl;
    std::cout<<"max(1,2,3,4,12)"<<max(1,2,-12,4,5)<<std::endl;
}

#include <utils/string.hpp>
void test_string()
{
    using namespace utils::string;
    std::string base = "test testtest testestestestest";
    std::cout<<"Base:"<<base<<std::endl;

    std::cout<<"split(base,\" \")"<<std::endl;
    for(auto& s : split(base," "))
        std::cout<<s<<std::endl;

    std::cout<<"replace(base,\"test\",\"blah\")"<<std::endl;
    replace(base,"test","blah");
    std::cout<<"Base:"<<base<<std::endl;

    std::cout<<"join(\"/\",split(base,\"bl\"))"<<std::endl;
    std::cout<<join("|",split(base,"bl"))<<std::endl;


    std::cout<<join("|",1,2,3,"blaghjio",42.f)<<std::endl;
}

#include <utils/sys.hpp>
void test_sys()
{
    {
        using namespace utils::sys::dir;
        //rm("/tmp/tmp",true);
        //rm_if_empty("/tmp/tmp",true);
    }

    {
        using namespace utils::sys::file;
    }
}


int main(int argc,char* argv[])
{
    test_logs();
    test_maths();
    test_string();
    test_sys();

    return 0;
}
