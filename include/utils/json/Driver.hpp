#ifndef UTILS_JSON_DRIVER_HPP
#define UTILS_JSON_DRIVER_HPP

#include <iostream>

#include <utils/json/Scanner.hpp>

namespace utils
{
    namespace json {
        /**
         * A class that have to be use to parse json input
         */
        class Driver
        {
            public:
                /**
                 * \brief Construct a Driver from a stream
                 * \param in input stream
                 */
                Driver(std::istream& in);

                Driver(const Driver&) = delete;
                Driver& operator=(const Driver&) = delete;

                /**
                 * \brief Destructor
                 */
                ~Driver();

                /**
                 * \brief Parse all the input (until \0)
                 * \return A analyse tha contain all the datas
                 */
                //Anal parse(const int max_charge=0);

                /**
                 * \brief PArse only the next spectrum
                 * \return a pointer to the Spectrum. if nullptr is recive, all the input have been pase. You have to manualy delete the Spectrum
                 */
                //Spectrum* next(const int max_charge=0,const int prepare_flags = Spectrum::PrepareFlags::All);

                /**
                 * \brief Parse a input
                 * \param in The input stream to parse
                 * \return The analyse tha contain all the datas
                 */
                //static Analyse parse(std::istream& in,const int max_charge=0,const int prepare_flags = Spectrum::PrepareFlags::All);

                /**
                 * \brief Parse a input, and add the data parse to the analyse
                 * \param in Input to parse
                 * \param a Analyse where data will be saves
                 * \return number of spectrum parsed
                 */
                //static int parse(std::istream& in,Analyse& a,const int max_charge=0,const int prepare_flags = Spectrum::PrepareFlags::All);
                
                /**
                 * \brief Parse a file and return a Analyse
                 * \param filename the file name
                 * \return A Analyse tha contain all the datas parsed
                 */
                //static Analyse parse_file(const std::string& filename,const int max_charge=0,const int prepare_flags = Spectrum::PrepareFlags::All);

                /**
                 * \brief Parse a file, and store data in the analyse
                 * \param filename file to parse
                 * \param a Analyse where data will be saved
                 * \return number of spectrum parsed
                 */
                //static int parse_file(const std::string& filename,Analyse& a,const int max_charge=0,const int prepare_flags = Spectrum::PrepareFlags::All);


                /**
                 * \return true if the stream is a valid format, else, false.
                 */
                inline bool isValid()const{return validity;}

                 
            private:
                friend class Parser;
                    
                Scanner scanner; ///< The lexer
                Parser parser; ///< The parser

                bool validity;
        };
    }
}
#endif
