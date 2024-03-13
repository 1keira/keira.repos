/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/
#ifndef FW_UTIL_ESOJSONPARSER_H
#define FW_UTIL_ESOJSONPARSER_H

#include <util/util_dso.h>

#ifdef __cplusplus
extern "C" {
#endif 

/*
 * current result of the parser given at the callback(esojson_parser_result_callback_t)
*/
enum esojson_parser_result_type_t{
    ESOJSON_RES_ERROR,          // error during parsing occured
    ESOJSON_RES_PARSE_BEGIN,    // parser starts with its work
    ESOJSON_RES_PARSE_END,      // parser has finished successful its work
    ESOJSON_RES_DICT_BEGIN,     // a dictionary definition starts
    ESOJSON_RES_DICT_END,       // a dictionary definition finisged
    ESOJSON_RES_ARRAY_BEGIN,    // an array definition starts
    ESOJSON_RES_ARRAY_END,      // an array definition finished
    ESOJSON_RES_ITEM_KEY,       // key found
    ESOJSON_RES_STRING_VALUE,   // string value found
    ESOJSON_RES_TRUE_VALUE,     // true value found
    ESOJSON_RES_FALSE_VALUE,    // false value found
    ESOJSON_RES_NULL_VALUE,     // null value found
    ESOJSON_RES_INT_VALUE,      // int value found
    ESOJSON_RES_FLOAT_VALUE     // float value found
};
/*
 * information given for each callback of the parser (esojson_parser_result_callback_t)
*/
struct esojson_parser_result_t{
    //! current result of the parser, see ESOJSON_RES_xxx
    esojson_parser_result_type_t result_type;
    int  current_line_number;
    int  current_line_pos;
    //! content related to the result_type
    union {
        /*
         * result of 
         * ESOJSON_RES_ITEM_KEY -> the key
         * ESOJSON_RES_STRING_VALUE -> the string value
         * ESOJSON_RES_ERROR -> the error reason
        */
        const char* value_string;
        //! result of ESOJSON_RES_INT_VALUE
        unsigned long long value_integer;
        //! result of ESOJSON_RES_FLOAT_VALUE
        double value_float;
    };
};

//! result value of the parser callback
#define ESOJSON_PARSER_CONTINUE 0    // continue parsing
#define ESOJSON_PARSER_ABORT 1       // abort parsing
//! callback from the parser into the application
typedef int esojson_parser_result_callback_t(const esojson_parser_result_t* result, void* user_data);

/*!
 * callback used by the parser to read character from the json input
 *
 * return next character from the stream or ESOJSON_EOS in case of EOS
*/ 
#define ESOJSON_STREAM_EOS (int)0
#define ESOJSON_STREAM_ERROR (int)-1
/*!
 * callback used by the parser to read characters from the json input
 * return:
 *  >0: number of read chars
 *  ESOJSON_STREAM_EOS on end of stream found
 *  ESOJSON_STREAM_ERROR on error reading from stream
*/
typedef int esojson_parser_streaminput_t(char* buf, int max_size, void* user_data);

typedef void *esojson_parser_handle_t;

/*!
 * create a parser instance
 * cb [in] 
 *  callback for the parser to report results during parsing
 * stream [in] 
 *  callback for the parser to get character from the stream
 * stream_buffer_size [in]
 *  size of the internal streaming buffer
 * initial_cache_buffer_size
 *  initial size of an internal used cached (e.g. for collecting strings)
 *  If the cached is too short it's increased internally
*/ 
UTIL_EXPORT esojson_parser_handle_t esojson_parser_create(
        esojson_parser_result_callback_t* cb, 
        esojson_parser_streaminput_t* stream, 
        int stream_buffer_size, 
        int initial_cache_buffer_size,
        void* user_data);

#define ESOJSON_PARSER_RESULT_OK 0
#define ESOJSON_PARSER_RESULT_FAILED 1
#define ESOJSON_PARSER_RESULT_ILLEGAL_HANDLE 2
/*!
 * calling the parser
 * return see ESOJSON_PARSER_RESULT_<XXX>
*/ 
UTIL_EXPORT int esojson_parser_parse(esojson_parser_handle_t handle);

/*!
 * destroy the parser instance
*/
UTIL_EXPORT void esojson_parser_destroy(esojson_parser_handle_t handle);

#ifdef __cplusplus
}
#endif 

#endif
