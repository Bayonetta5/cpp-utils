#include <sstream>

namespace utils
{
    namespace plot
    {

        template<typename X,typename Y>
        void Serie::add(X&& x, Y&& y)
        {
            (*this)<<x<<" "<<y<<std::endl;
        }

        template<typename T>
        Serie& operator<<(Serie& self,const T& value)
        {
            self._out<<value;
            return self;
        }
            template<typename CONTAINER_X,typename CONTAINER_Y>
            void Gnuplot::plot(const CONTAINER_X& x,const CONTAINER_Y& y,const Style& style)
            {
                plot("",x,y,style);
            }

            template<typename CONTAINER_X,typename CONTAINER_Y>
            void Gnuplot::plot(const std::string& title,const CONTAINER_X& x,const CONTAINER_Y& y,const Style& style)
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

                ++nb_plot;

                //*this
            }

            template<typename T>
            Gnuplot& operator<<(Gnuplot& self,const T& value)
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

            inline std::string Gnuplot::convert(const Style& style)
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
    }
}
