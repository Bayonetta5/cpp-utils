#include <iostream>
#include <utils/log.hpp>

void test_logs()
{
    using namespace std;

    {
        using namespace utils::logs::format;
        cout<<bold<<"bold"<<reset_bold<<"reset_bold"<<endl;
        cout<<dim<<"dim"<<reset_dim<<"reset_dim"<<endl;
        cout<<underline<<"underline"<<reset_underline<<"reset_underline"<<endl;
        cout<<blink<<"blink"<<reset_blink<<"reset_blink"<<endl;
        cout<<reverse<<"reverse"<<reset_reverse<<"reset_reverse"<<endl;
        cout<<hidden<<"hidden"<<reset_hidden<<"reset_hidden"<<endl;
        cout<<strikeout<<"strikeout"<<reset_strikeout<<"reset_strikeout"<<endl;
    }

    
    {
        using namespace utils::logs::colors;
        cout<<black<<"black"<<endl;
        cout<<red<<"red"<<endl;
        cout<<green<<"green"<<endl;
        cout<<yellow<<"yellow"<<std::endl;
        cout<<blue<<"blue"<<endl;
        cout<<magenta<<"magenta"<<endl;
        cout<<cyan<<"cyan"<<endl;
        cout<<light_gray<<"light_gray"<<endl;
        cout<<dark_gray<<"dark_gray"<<endl;
        cout<<light_red<<"light_red"<<endl;
        cout<<light_green<<"light_green"<<endl;
        cout<<light_yellow<<"light_yellow"<<endl;
        cout<<light_blue<<"light_blue"<<endl;
        cout<<light_magenta<<"light_magenta"<<endl;
        cout<<light_cyan<<"light_cyan"<<endl;
        cout<<white<<"white"<<endl;
        cout<<reset<<"reset"<<endl;
    }

    {
        using namespace utils::logs::bg;
        cout<<black<<"black"<<endl;
        cout<<red<<"red"<<endl;
        cout<<green<<"green"<<endl;
        cout<<yellow<<"yellow"<<std::endl;
        cout<<blue<<"blue"<<endl;
        cout<<magenta<<"magenta"<<endl;
        cout<<cyan<<"cyan"<<endl;
        cout<<light_gray<<"light_gray"<<endl;
        cout<<dark_gray<<"dark_gray"<<endl;
        cout<<light_red<<"light_red"<<endl;
        cout<<light_green<<"light_green"<<endl;
        cout<<light_yellow<<"light_yellow"<<endl;
        cout<<light_blue<<"light_blue"<<endl;
        cout<<light_magenta<<"light_magenta"<<endl;
        cout<<light_cyan<<light_cyan<<endl;
        cout<<white<<"white"<<endl;
        cout<<reset<<"reset"<<endl;
    }
    
}

#include <utils/maths.hpp>
void test_maths()
{

}

void test_string()
{
}

void test_sys()
{
}


int main(int argc,char* argv[])
{
    test_logs();
    test_maths();
    test_string();
    test_sys();

    return 0;
}
