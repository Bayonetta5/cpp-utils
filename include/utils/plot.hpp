#ifndef UTILS_PLOT_HPP
#define UTILS_PLOT_HPP

#include <cstdio>
#include <cstdlib>

#include <string>
#include <fstream>

namespace utils
{
    namespace plot
    {

        class Serie
        {
            public:

                explicit Serie(const std::string& ="");

                enum class Style
                {
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

                const std::string& title()const;
                void title(const std::string&);

                Style style()const;
                void style(Style);

                template<typename X,typename Y>
                void add(X&& x,Y&& y);

                template<typename T>
                friend Serie& operator<<(Serie& self,const T& value);

            private:
                std::string _title;
                std::ofstream _out;
                Style _style;
        };

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
