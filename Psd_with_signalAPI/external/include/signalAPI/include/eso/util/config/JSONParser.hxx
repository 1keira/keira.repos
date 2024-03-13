/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_CONFIG_JSONPARSER_HXX
#define UTIL_CONFIG_JSONPARSER_HXX

#include <ipl_config.h>
#include <common/types/stack.hxx>
#include <common/streams/istream.hxx>
#include <common/error/Error.hxx>
#include <osal/Time.hxx>
#include <util/config/Values.hxx>
#include <common/tracing/tracing.hxx>


namespace util {
namespace config {

/* this trace channel is for json parser errors and json input format errors */
IPL_TRACE_DECLARE_CHANNEL_EXTERN(FW_UTIL_JSON_ConfigParser);

    enum JSONParserErrors
    {
        IPL_JSONPARSER_FILE_NOT_FOUND_ERROR,
        IPL_JSONPARSER_PARSER_ERROR,
        IPL_JSONPARSER_PARSER_ERROR_IN_STREAM,
        IPL_JSONPARSER_DUPLICATE_ENTRY,
        IPL_JSONPARSER_DUPLICATE_ENTRY_IN_STREAM,
        IPL_JSONPARSER_EMPTY_KEY,
        IPL_JSONPARSER_EMPTY_KEY_IN_STREAM,
        IPL_JSONPARSER_PREFIX_TOO_LONG,
        IPL_JSONPARSER_UNSUPPORTED_FILEFORMAT,
        IPL_JSONPARSER_INVALID_USAGE
    };

    UTIL_EXPORT extern ipl::ErrorType JSONParserError;

/*!
\brief    Implementation of a parser for JSON Files
*/
class UTIL_EXPORT JSONParser : public ipl::NonCopyable {

    public:

        /*!
         * create a JSON Parser
         *
         * \param [in] hold_owner_ship
         *  defines whether the parser shall own all create memory or not
         *
         *  Each parse call creates a tree or array of config values. This instances is
         *  returned to the caller. Dependend on the hold_owner_ship value, the instance
         *  is destroyed when the parser is deleted (hold_owner_ship = true),
         *  so the caller must not delete it by himself.
         *  In case of hold_owner_ship = false, the parser does no delete, so the caller
         *  has to do this.
         *
         *  Note: This parser does not allow to parse JSON files that consist of a value other than array or object.
         *  This is in line with the former RFC 4627. Since the update to RFC 7159, the root of a JSON document
         *  can be any JSON value. This is not yet reflected by this interface.
         */

        //! memory ownership of the created instances is taken by the parser
        static const bool HOLD_OWNER_SHIP = true;

        //! memory ownership of the created instances is returned by the parser to the caller
        static const bool MOVE_OWNER_SHIP = false;

        JSONParser(bool hold_owner_ship = true) IPL_NOEXCEPT;
        ~JSONParser() IPL_NOEXCEPT;

        /*!
        \brief    parse json-content from a file given with filename. The root of RFC 4627 conform json is always
                an array or a dictionary. In case of an array, the *array parameter is initialized and filled,
                in case of an dictionary, *dict is initialized and filled. The other one is set to NULL.

                All read values from the json are appended to the dict or array. Duplicate keys
                and empty keys in dictionaries are handled as error.

                In case of an error like
                    - file not found
                    - parser error
                true is returned. In case of success false is returned.

                In case of a parser error, the *dict and *array parameters are not changed.

        \param[in] filename
                is the name of the file to be read
        \param[in,out]
                dict is the dictionary, which is filled in case of the root-node of the json is a dictionary
        \param[in,out]
                array is the array, which is filled in case of the root-node of the json is an array
        \param[in] max_line_length
                the maximum length of a line within the json-file. If the parameter is ommited or 0 is
                given the default value of 255 is used.
        \return    false on success, true on error
        \errorindicator
                return value
        \errors    see JSONParserError
        */
        bool parseFile (const char *filename, Dictionary** dict, Array** array, uint32_t max_line_length = 0) IPL_NOEXCEPT;

        bool parseStream (ipl::istream& stream, Dictionary** dict, Array** array) IPL_NOEXCEPT;


        /*!
        \brief    like parseFile, but it assumes that an array is the root element of the json file
                It reports an error if the root element is not an array
        \return    false on success, true on error
        */
        bool parseFileToArray (const char *filename, Array** array, uint32_t max_line_length = 0) IPL_NOEXCEPT;

        /*!
        \brief    like parseFile, but it assumes that a dictionary is the root element of the json file
                It reports an error if the root element is not a dictionary
        \return    false on success, true on error
        */
        bool parseFileToDict (const char *filename, Dictionary** dict, uint32_t max_line_length = 0) IPL_NOEXCEPT;

        /*!
        \brief    The same parseFile, but the content is taken from a string
        \return    false on success, true on error
        \errorindicator
                return value
        \errors    see JSONParserError
        */
        bool parseString (const char *string, Dictionary** dict, Array** array) IPL_NOEXCEPT;

        /*!
        \brief    The same parseFileToArray, but the content is taken from a string
        \return    false on success, true on error
        \errorindicator
                return value
        \errors    see JSONParserError
        */
        bool parseStringToArray (const char *string, Array** array) IPL_NOEXCEPT;

        /*!
        \brief    The same parseFileToDict, but the content is taken from a string
        \return    false on success, true on error
        \errorindicator
                return value
        \errors    see JSONParserError
        */
        bool parseStringToDict (const char *string, Dictionary** dict) IPL_NOEXCEPT;

        //! retrieve the elapsed time in ms needed to parse the file and create the dictionary
        osal::TimeT getElapsedTime() const IPL_NOEXCEPT;
    private:
        void *m_impl;

};

} // namespace config
} // namespace util

#endif // UTIL_CONFIG_JSONPARSER_HXX

