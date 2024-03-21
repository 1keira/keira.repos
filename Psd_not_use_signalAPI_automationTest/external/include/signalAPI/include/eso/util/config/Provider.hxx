/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_CONFIG_PROVIDER_HXX
#define UTIL_CONFIG_PROVIDER_HXX

#include <ipl_config.h>
#include <common/error/Error.hxx>
#include <util/util_dso.h>
#include <util/config/Values.hxx>
#include <util/config/JSONParser.hxx>

namespace util {
namespace config {

    class BCFProvider;


    /*!
    \brief
        The ConfigProvider class provides the access to the framework configuration files
        It supports the access to the root-config dictionary, which is created out of the information
        read from root configuration file.
        The content can only be read. Existing values can't be overwritten and also no new values
        can be added.

        There is one singleton instance, which is instatiated when the first instance of the
        ConfigProvider is created. At this time the default root config-file is read into the
        config dictionary.

        Each entry in the dictionary can be access via it's key.
    */
    class UTIL_EXPORT Provider     {
        public:
            //! defines the file type which was loaded
            enum FileType {
                UNDEF,
                JSON,
            };

            enum LoadStrategy {
                ONLY_JSON,
            };

            /*!
            \brief
                Creates a configuration dictionary based on a given prefix.

                The file to load is searched by the following rules:
                - if env IPL_CONFIG_FILE_\<PREFIX>.json is set,
                  this filename is used
                - else if env IPL_CONFIG_DIR_\<PREFIX> is set,
                  the filename \<env>/\<prefix>.json is used
                - else if env IPL_CONFIG_DIR is set,
                  the filename \<env>/\<prefix>.json is used
                - else the filename ./\<path>/\<prefix>.json
                Only one of these defined alternatives is used for searching the file. It's controlled by
                the existence of the environment variables

                Depending on the \a strategy, json is used as suffix of the filenames.

            \param[in] prefix
                is the prefix for the filename and also used as part of the environment variable names
            \param[in] max_line_length
                defines the maximum supported length of text lines in the json-file
            \param[in] strategy
                defines which suffix and also which format shall be used for loading files
                IT'S NOT SUPPORTED ANYMORE BECAUSE OF SECURITY ISSUES

            \errorindicator
                hasError()
            \errors    see util::config::JSONParserError from util/config/JSONParser.hxx
            */
            Provider(const char* prefix, const char* path, uint32_t max_line_length = 0, LoadStrategy strategy = ONLY_JSON) IPL_NOEXCEPT;
            Provider(const char* prefix, const char* path, LoadStrategy strategy) IPL_NOEXCEPT;

            /*!
            \brief
                loads the given file. Depending on the suffix, a json files is loaded
            */
            Provider(const char* file, uint32_t max_line_length = 0) IPL_NOEXCEPT;

            /*!
            \brief
                creates the dictionary out of the given string
            */
            Provider(const ipl::string & str) IPL_NOEXCEPT;

            Provider(const Provider &)=delete;
            Provider &operator = (const Provider &)=delete;
            
            Provider(Provider &&other) { operator = (std::move(other)); }
            Provider &operator = (Provider &&other) {
                m_is_valid=other.m_is_valid;
                other.m_is_valid=false;
                m_dict=other.m_dict;
                other.m_dict=nullptr;
                m_array=other.m_array;
                other.m_array=nullptr;
                // gets deleted in the d'tor if not NULL
                m_parser=other.m_parser;
                other.m_parser=nullptr;
                m_file_type=other.m_file_type;
                return *this;
            }

            virtual ~Provider() IPL_NOEXCEPT;
            
            operator const Value &() const IPL_NOEXCEPT {

                if(isValid()) {
                    if(m_dict->isDefined())
                    {
                        return *m_dict;
                    }
                    else if(m_array->isDefined())
                    {
                        return *m_array;
                    }
                }

                return util::config::Value::getUndefined();
            }

            util::config::Dictionary* getEditableDictionary() const IPL_NOEXCEPT {
                if(isValid() && m_dict)
                    return (util::config::Dictionary*)m_dict;
                return NULL;
            }

            /*!
            \brief    check whether a valid configuration is loaded.
            */
            bool isValid() const IPL_NOEXCEPT { return m_is_valid; };

            /*!
            \brief    check whether an error occured and raised during access loading
            */
            bool hasError() const IPL_NOEXCEPT { return !m_is_valid; } ;

            /*!
            \brief
            */
            const Value& operator[](const char* key) const IPL_NOEXCEPT {  return (*m_dict)[key]; };
            const Value& operator[](const ipl::string& key) const IPL_NOEXCEPT {  return (*m_dict)[key]; };

            bool isDictionary() const IPL_NOEXCEPT  { return m_dict->isDictionary(); };

            /*!
            \brief    overwritten method from base class ConfigValue.
                    It checks on the root-node from the root-config-dictionary
            */
            virtual bool hasKey(const char* key) const IPL_NOEXCEPT {  return m_dict->hasKey(key); };

            const Value& operator[] (const size_t index) const IPL_NOEXCEPT { return (*m_array)[index]; };
            size_t arraySize() const IPL_NOEXCEPT  {  return m_array->arraySize(); };
            bool isArray() const IPL_NOEXCEPT  {  return m_array->isArray(); };

            //! retrieve the elapsed time in ms needed to parse the file and create the dictionary
            osal::TimeT getElapsedTime() const  IPL_NOEXCEPT  { return m_parser->getElapsedTime(); }

            ipl::ostream& print (ipl::ostream &stream) const IPL_NOEXCEPT  {
                if (m_dict->isDefined())
                    m_dict->print (stream);
                if (m_array->isDefined())
                    m_array->print (stream);
                return stream;
            }

            //! retrieve the file type
            FileType getType() IPL_NOEXCEPT  { return m_file_type; }

        private:

            void init (const char* prefix, const char* path, uint32_t max_line_length, LoadStrategy strategy);

            void loadJSON (const char* filename, uint32_t max_line_length);
            void loadString(const char* str);
            bool fileExists(const char* filename);

            //! ctor()
            Provider() {};

            bool m_is_valid;

            const Value* m_dict;
            const Value* m_array;

            JSONParser* m_parser;

            FileType    m_file_type;


    };

} // namespace config
} // namespace util

#endif // UTIL_CONFIG_PROVIDER_HXX
