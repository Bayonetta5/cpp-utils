#include <utils/plot.hpp>

#include <stdexcept>
namespace utils
{
    namespace plot
    {
        void Gnuplot::plot(const std::string& cmd)
        {
            if(has_plot)
                *this<<"replot "<<cmd<<"\n";
            else
            {
                *this<<"plot "<<cmd<<"\n";
                has_plot = true;
            }
        }

        void Gnuplot::cmd(const std::string& cmd)
        {
            *this<<cmd<<"\n";
        }
        
        void Gnuplot::clear()
        {
            *this<<"clear\n";
            has_plot = false;
        }

        bool Gnuplot::isOpen()const
        {
            return pipe != nullptr;
        }

        bool Gnuplot::open()
        {
            if(pipe != nullptr)
                return false;

            #ifdef WIN32
            pipe = _popen("gnuplot.exe", "w");
            #else
            pipe = popen("gnuplot", "w");
            #endif
            
            if(pipe == nullptr)
            {
                throw std::runtime_error("gnuplot not found. Is gnuplot"
                #ifdef WIN32
                ".exe"
                #endif
                " in your path?");
            }
            return true;
        }

        bool Gnuplot::close()
        {
            if(pipe == nullptr or
            #ifdef WIN32
            ::_pclose(pipe)
            #else
            ::pclose(pipe)
            #endif
            == -1)
                return false;
            pipe= nullptr;
            return true;
        }

        Gnuplot::Gnuplot() : pipe(nullptr), has_plot(false)
        {
            open();
        }

        Gnuplot::~Gnuplot()
        {
            close();
        }
    }
}
