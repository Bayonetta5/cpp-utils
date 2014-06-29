#include <cstdio>
#include <cstdlib>

#include <string>
#include <sstream>

#include <stdexcept>


namespace utils
{
namespace tr
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

            template<typename CONTAINER_X,typename CONTAINER_Y>
            void plot(const CONTAINER_X& x,const CONTAINER_Y& y,const Style& style = Style::points)
            {
                plot("",x,y,style);
            }

            template<typename CONTAINER_X,typename CONTAINER_Y>
            void plot(const std::string& title,const CONTAINER_X& x,const CONTAINER_Y& y,const Style& style = Style::points)
            {
                auto begin_x = x.begin();
                const auto end_x = x.end();

                auto begin_y = y.begin();
                const auto end_y = y.end();

                *this<<"plot '-'";

                if(not title.empty())
                    *this<<" title \""<<title<<"\"";

                *this<<" with "<<convert(style)<<"\n";


                while(begin_x != end_x and begin_y != end_y)
                {
                    *this<<*begin_x<<" "<<*begin_y<<"\n";
                    ++begin_x;
                    ++begin_y;
                }

                *this<<"e\n";

                has_plot = true;

                //*this
            }

            inline void plot(const std::string& cmd)
            {
                if(has_plot)
                    *this<<"replot "<<cmd<<"\n";
                else
                {
                    *this<<"plot "<<cmd<<"\n";
                    has_plot = true;
                }
            }

            inline void cmd(const std::string& cmd)
            {
                *this<<cmd<<"\n";
            }

            void clear()
            {
                *this<<"clear\n";
                has_plot = false;
            }

            inline bool isOpen()const
            {
                return pipe != nullptr;
            }

            inline bool open()
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

            inline bool close()
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

            //vector<T>, list<T>, array<T>, initializer_list<T>
            template<typename T>
            friend Gnuplot& operator<<(Gnuplot& self,const T& value)
            {
                if(self.isOpen())
                {
                    std::stringstream ss;
                    ss<<value;
                    ::fprintf(self.pipe,"%s",ss.str().c_str());
                    ::fflush(self.pipe);
                }
                return self;
            }

            Gnuplot() : pipe(nullptr), has_plot(false)
            {
                open();
            }

            ~Gnuplot()
            {
                close();
            }

        private:
            FILE* pipe;
            bool has_plot;

            static inline std::string convert(const Style& style)
            {
                switch(style)
                {
                    case Style::points : return {"points"};
                    case Style::lines : return {"lines"};
                    case Style::linespoints : return {"linespoints"};
                    case Style::impulses : return {"impulses"};
                    case Style::dots : return {"dots"};
                    case Style::steps : return {"steps"};
                    case Style::errorbars : return {"errorbars"};
                    case Style::boxes : return {"boxes"};
                    case Style::boxerrorbars : return {"boxerrorbars"};
                }
                return {"points"};
            }
    };
}
}
