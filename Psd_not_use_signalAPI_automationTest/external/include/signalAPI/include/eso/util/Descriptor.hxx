/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
/****************************************************************************/
#ifndef UTIL_DESCRIPTOR_HXX
#define UTIL_DESCRIPTOR_HXX
/*****************************************************************************/

/*!
    \page util_descriptor_page Transport Descriptors

    The traditional system for creating transports from configuration is pretty
    clumsy.
    There is a central factory that takes Config obtained from a JSON file
    and that parses a whole bunch of idiosyncratic parameters,
    more or less individual to the transport type.
    Then it sets up spawning factories without a chance of outside control.

    What we rather need is a more fine-grained mechanism.
    Hand it a string (from JSON, from the command line, from some COMM call,
    whatever) and get back a Transport.
    That mechanism are the \ref util_astra_factory_page "factory functions",
    and the string describing what you want is the descriptor.
    Parsing is done per Transport type, which doesn't make the parameters less
    idiosyncratic, but at least it keeps the parser close to the code
    it configures.

    A Transport Descriptor has the form of a
    <a href="http://en.wikipedia.org/wiki/Uniform_resource_identifier">URI</a>.
    The scheme or "protocol" part is left of the first colon (think
    \"<tt>http:</tt>\") and denotes the kind of Transport (TCP/IP,
    Ressource Manager, ...).
    The keyword arguments are in the query string,
    right of the first question mark, delimited by ampersand or semicolon and
    possibly with an equals-sign separating the keyword from a value
    (think \"<tt>?search=foo&format=bar&thud</tt>\").
    Between the two are the positional, non-keyword arguments,
    separated by colons (think \"<tt>//localhost:8080</tt>\").

    So we have a generic format, and it gets parsed by the
    \ref util::Descriptor "Descriptor" class.
    Instantiate it with a string and you get access to all parts of the
    descriptor, cooked as well as raw.
    
    \see \ref util_astra_page
*/

/****************************************************************************/

#include <common/error/ErrorType.hxx>

#include <string>
#include <sstream>
#include <vector>
#include <map>

#include <type_traits>
#include <algorithm>
#include <cstddef>
#include <cstdint>

#include <util/util_dso.h>

/****************************************************************************/

namespace util {

/*****************************************************************************/

    /*!
        \brief A parsed transport descriptor
        
        If the constructor raises an error, everything except raw is
        invalid.
        
        \see \ref util_astra_descriptor_page, \ref util_astra_page
    */
    struct UTIL_EXPORT Descriptor {

        // Cannot use enum class here as it would be too typesafe
        // for convenient use with ipl_raise
        struct Error { enum {
            syntax,   // %s uri
            hex,      // %s urlencoded
            keyword,  // %s keyword
            kwarg,    // %s keyword, %s value
        }; };
        static ipl::ErrorType error;
        
        //! \brief The raw descriptor
        std::string raw;
        
        //! \brief The scheme, i.e. the stuff left of ":"
        std::string scheme;
        
        //! \brief Not the scheme, i.e. the stuff right of the first ":", undecoded
        std::string non_scheme;
        
        //! \brief The urldecoded non-query part
        std::string arg;
        
        typedef std::vector<std::string> Args;
        //! \brief The list of non-keyword arguments, i.e. without a "="
        Args args;
        
        typedef std::map<std::string, std::string> Kwargs;
        //! \brief The keyword arguments, i.e. with "="
        Kwargs kwargs;

        // Yes, this is intended to be non-explicit!
        Descriptor(const std::string &descriptor);
        Descriptor(const char *descriptor):
            Descriptor(std::string(descriptor)) {}
        Descriptor()=default;

        //! \brief Retrieve a keyword argument
        template <typename T> void get(const std::string &key, T &value) const;
        
        //! \brief Check for presence of a keyword argument
        bool has(const std::string &key) const;
        
//         //! \brief Convenience check for extra/mistyped keywords
//         template <typename Container>
//         std::string keywords_not_in(const Container &keywords) const;
//
//         //! \brief Convenience check for extra/mistyped keywords
//         //!
//         //! \p begin and \p end point into some container or array
//         //! of expected keywords.
//         template <typename Iterator>
//         std::string keywords_not_in(const Iterator &begin,
//                                     const Iterator &end) const;
        
        //! \brief Convenience functionality mainly for reporting
        //! extra/mistyped keywords
        //!
        //! If you erase_kw() all valid keywords from the descriptor,
        //! this gives a convenient string for you to print,
        //! containing unknown keywords the user has given.
        std::string kw_to_string(const char *delim=", ") const;
        
        //! \brief Make sure \p key is not contained in kwargs
        void erase_kw(const std::string &key);

        //! \brief Convenience functionality, retrieve and erase
        //! a keyword argument
        template <typename T>
        void get_and_erase(const std::string &key, T &value);
        
        //! \brief Convenience functionality,
        //! check for presence of a keyword argument and erase it
        bool has_and_erase(const std::string &key);

        //! \brief Retrieve a non-keyword argument
        template <typename T> void get(unsigned index, T &value) const;
        
        //! \brief Check for presence of a non-keyword argument
        bool has(unsigned index) const;
        
        //! \brief Get substring from \p begin up to \p end (exclusive)
        //! and urldecode it, turning "+" into " " if \p decode_plus
        //!
        //! It is OK for \p end to be past the string's end.
        static std::string urldecode(const std::string &s, size_t begin=0,
                                        size_t end=std::string::npos,
                                        bool decode_plus=false);
        
        //! \brief Get numeric value of hex character \p c
        //! or non_hex on error
        static unsigned hexdecode(char c);
        static const unsigned non_hex;
    };

/*****************************************************************************/

    template <typename T>
    /*inline*/ void Descriptor::get(const std::string &key, T &value) const
    {
        Kwargs::const_iterator i=kwargs.find(key);
        if(i==kwargs.end()) return;
        std::istringstream s(i->second);
        s >> value;
    }

    template <>
    inline void Descriptor::get<std::string>(const std::string &key, std::string &value) const
    {
        Kwargs::const_iterator i=kwargs.find(key);
        if(i==kwargs.end()) return;
        value=i->second;
    }

    inline bool Descriptor::has(const std::string &key) const
    {
        return kwargs.find(key)!=kwargs.end();
    }

//         template <typename Container>
//         inline std::string Descriptor::keywords_not_in(const Container &keywords) const
//         {
//             return keywords_not_in(keywords.begin(), keywords.end());
//         }
//         
//         template <typename Iterator>
//         std::string Descriptor::keywords_not_in(const Iterator &begin, const Iterator &end) const
//         {
//             std::string result;
//             for(auto kw: kwargs)
//                 if(std::find(begin, end, kw.first)==end) {
//                     if(!result.empty())
//                         result+=", ";
//                     result+=kw.first;
//                 }
//             return result;
//         }

    inline void Descriptor::erase_kw(const std::string &key)
    {
        kwargs.erase(key);
    }

    template <typename T>
    inline void Descriptor::get_and_erase(const std::string &key, T &value)
    {
        get(key, value);
        erase_kw(key);
    }
    
    inline bool Descriptor::has_and_erase(const std::string &key)
    {
        auto res=has(key);
        erase_kw(key);
        return res;
    }

    template <typename T>
    /*inline*/ void Descriptor::get(unsigned index, T &value) const
    {
        if(index<args.size()) {
            std::istringstream s(args[index]);
            s >> value;
        }
    }

    template <>
    inline void Descriptor::get<std::string>(unsigned index, std::string &value) const
    {
        if(index<args.size()) { value=args[index]; }
    }


    inline bool Descriptor::has(unsigned index) const
    {
        return index<args.size();
    }

/****************************************************************************/

}  // end of namespace util

/****************************************************************************/
#endif
