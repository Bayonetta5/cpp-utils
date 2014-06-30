#include <utils/plot.hpp>
#include <utils/sys.hpp>

#include <cstring>
#include <stdexcept>

#ifndef _WIN32
#include <unistd.h>
#endif

namespace utils
{
    namespace plot
    {
        /********* Serie **************/
        Serie::Serie(const std::string& title) : _title(title), _style(Style::lines)
        {
            if(utils::sys::dir::create("./plot") == 0)
                throw std::runtime_error("Unable to create tempory dir plot");

            char *tmpname = ::strdup("./plot/serie_XXXXXX");
            #ifdef _WIN32
            if(::_mkstemp(tmpname)==nullptr)
            #else
            int fd = ::mkstemp(tmpname);
            if(fd == -1)
            #endif
            {
                ::free(tmpname);
                throw std::runtime_error("Unable to create tempory file");
            }

            _out.open(tmpname);
            ::free(tmpname);
            #ifndef _WIN32
            ::close(fd);
            #endif
        }

        const std::string& Serie::title()const
        {
            return _title;
        }

        void Serie::title(const std::string& title)
        {
            _title = title;
        }

        Serie::Style Serie::style()const
        {
            return _style;
        }

        void Serie::style(Serie::Style style)
        {
            _style = style;
        }
        
        //Gnuplot
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
