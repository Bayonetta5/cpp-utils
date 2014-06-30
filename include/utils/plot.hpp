#ifndef UTILS_PLOT_HPP
#define UTILS_PLOT_HPP

#include <cstdio>
#include <cstdlib>

#include <string>


namespace utils
{
    namespace plot
    {
        class Gnuplot
        {
            public:
                
                enum class Style{
                    points,
                    lines,
                    linespoints,
                    impulses,
                    dots,
                    steps,
                    errorbars,
                    boxes,
                    boxerrorbars,
                };

                Gnuplot();
                ~Gnuplot();

                template<typename CONTAINER_X,typename CONTAINER_Y>
                void plot(const CONTAINER_X& x,const CONTAINER_Y& y,const Style& style = Style::points);

                template<typename CONTAINER_X,typename CONTAINER_Y>
                void plot(const std::string& title,const CONTAINER_X& x,const CONTAINER_Y& y,const Style& style = Style::points);

                void plot(const std::string& cmd);

                void cmd(const std::string& cmd);

                void clear();

                bool isOpen()const;

                bool open();

                bool close();

                template<typename T>
                friend Gnuplot& operator<<(Gnuplot& self,const T& value);

                void draw();
                void draw(int plot_number);

                enum class Mod{
                    MULTI,
                    WINDOW
                };

                void mod()const;
                void mod(Mod mod);


            private:
                FILE* pipe;
                int nb_plot;

                Mod _mod;

                static inline std::string convert(const Style& style);
        };
    }
}
#include <utils/plot.tpl>
#endif
