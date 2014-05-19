#include <utils/json/Driver.hpp>

#include <fstream>

namespace utils
{
    namespace json
    {
        Driver::Driver(std::istream& in) : scanner(in), parser(scanner,*this), validity(true)
        {
        }

        Driver::~Driver()
        {
        }

        
        /*Analyse Driver::parse(const int max_charge,const int prepare_flags)
        {
            mgf::Analyse analyse;
            int status = 0;
            while ((status = parser.parse()) == MGF_END_IONS)
            {
                analyse.push(new Spectrum(std::move(currentSpectrum)));
                currentSpectrum.reset();
                analyse.back().prepare(max_charge,prepare_flags);
            }
            if (status == 1)
                validity = false;

            return analyse;
        }

        Spectrum* Driver::next(const int max_charge,const int prepare_flags)
        {
            mgf::Spectrum* r = nullptr;
            int status = 0;
            if ((status = parser.parse()) == MGF_END_IONS)
            {
                r = new Spectrum(std::move(currentSpectrum));
                r->prepare(max_charge,prepare_flags);
                currentSpectrum.clear();
            }
            else if ( status == 1)
                validity = false;
            return r;
        }

        Analyse Driver::parse(std::istream& in,const int max_charge,const int prepare_flags)
        {
            Analyse res;
            Driver::parse(in,res,max_charge,prepare_flags);
            return res;
        }

        int Driver::parse(std::istream& in,Analyse& a,const int max_charge,const int prepare_flags)
        {
            int res = 0;
            Driver driver(in);
            Spectrum* spectrum = nullptr;
            while((spectrum = driver.next(max_charge,prepare_flags))!= nullptr)
            {
                a.push(spectrum);
                ++res;
            }
            return res;
        }

        Analyse Driver::parse_file(const std::string& filename,const int max_charge,const int prepare_flags)
        {
            Analyse res;
            Driver::parse_file(filename,res,max_charge,prepare_flags);
            return res;
        }

        int Driver::parse_file(const std::string& filename,Analyse& a,const int max_charge,const int prepare_flags)
        {
            int res = -1;
            std::ifstream file(filename, std::ifstream::in);
            if (file.good())
            {
                res = Driver::parse(file,a,max_charge,prepare_flags);
                file.close();
            }
            return res;
        }*/
    }
}
