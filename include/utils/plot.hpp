#ifndef UTILS_PLOT_HPP
#define UTILS_PLOT_HPP

#include <cstdio>
#include <cstdlib>

#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

namespace utils
{
    /**
     * \brief a namspace for ploting class
     */
    namespace plot
    {
        class Gnuplot;
        class Graph;
        /**
         * \brief internal serie representation.
         * Each serie is stor in a separate tmp file
         */
        class Serie
        {
            public:

                /**
                 * \brief could throw a std::runtime_error
                 */
                explicit Serie(const std::string& title="");

                ~Serie();

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
                std::string style_str()const;

                template<typename X,typename Y>
                void addPoint(X&& x,Y&& y);

                template<typename X,typename Y>
                void addPoints(X&& x,Y&& y);

                template<typename T>
                friend Serie& operator<<(Serie& self,const T& value);

                template<typename T>
                friend Serie& operator<<(Serie& self,T&& value);

                friend Gnuplot& operator<<(Gnuplot& plot,const Serie& self);

            private:
                friend class Graph;
                std::string _title;
                std::ofstream _out;
                Style _style;
                std::string _filename;
        };

        class Graph
        {
            public:
                Graph(const std::string& title="");
                ~Graph();

                const std::string& title()const;
                void title(const std::string&);

                Serie::Style style()const;
                void style(Serie::Style);

                unsigned int size()const;

                Serie& operator[](unsigned int);
                const Serie& operator[](unsigned int)const;

                Serie& operator[](const std::string& title);
                const Serie& operator[](const std::string& title)const;

                bool remove(unsigned int);
                bool remove(const std::string& title);

                template<typename ... Args>
                bool add(Args&& ... args);

                template<typename ... Args>
                bool addPoint(Args&& ... args);

                template<typename ... Args>
                bool addPoints(Args&& ... args);

                friend Gnuplot& operator<<(Gnuplot& plot,const Graph& self);

            private:
                friend class Gnuplot;
                std::string _title;
                std::vector<Serie*> _series;
                Serie::Style _style;

        };

        class Gnuplot
        {
            public:
                
                Gnuplot();
                ~Gnuplot();

                template<typename ... Args>
                void cmd(Args&& ... args);
                
                void flush();

                void clear();

                bool isOpen()const;

                bool open();

                bool close();

                template<typename T>
                friend Gnuplot& operator<<(Gnuplot& self,const T& value);

                void draw();
                void draw(unsigned int graph);
                void draw(const std::string& graph);

                enum class Mod{
                    MULTI,
                    WINDOW
                };

                Mod mod()const;
                void mod(Mod mod);


                template<typename ... Args>
                bool add(Args&& ... args);

                bool remove(unsigned int);
                bool remove(const std::string& title);

                Graph& operator[](unsigned int);
                const Graph& operator[](unsigned int)const;

                Graph& operator[](const std::string& title);
                const Graph& operator[](const std::string& title)const;

                unsigned int size()const;

            private:
                FILE* pipe;
                std::vector<Graph*> _graphs;

                Mod _mod;

        };
    }
}
#include <utils/plot.tpl>
#endif
