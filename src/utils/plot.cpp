#include <utils/plot.hpp>

#include <stdexcept>
namespace utils
{
    namespace plot
    {
        void Gnuplot::plot(const std::string& cmd)
        {
            if(nb_plot>0)
                *this<<"replot "<<cmd<<"\n";
            else
                *this<<"plot "<<cmd<<"\n";
            ++nb_plot;
        }

        void Gnuplot::cmd(const std::string& cmd)
        {
            *this<<cmd<<"\n";
        }
        
        void Gnuplot::clear()
        {
            *this<<"clear\n";
            nb_plot = 0;
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

        Gnuplot::Gnuplot() : pipe(nullptr), nb_plot(0), _mod(Mod::MULTI)
        {
            open();
        }

        Gnuplot::~Gnuplot()
        {
            close();
        }
    }
}
