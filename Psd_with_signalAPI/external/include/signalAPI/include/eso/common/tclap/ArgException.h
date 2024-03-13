// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

/****************************************************************************** 
 * 
 *  file:  ArgException.h
 * 
 *  Copyright (c) 2003, Michael E. Smoot .
 *  All rights reserved.
 * 
 *  See the file COPYING in the top directory of this distribution for
 *  more information.
 *  
 *  THE SOFTWARE IS PROVIDED _AS IS_, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
 *  THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
 *  DEALINGS IN THE SOFTWARE.  
 *  
 *****************************************************************************/ 

// Adapted for the e.solutions framework

#ifndef TCLAP_ARG_EXCEPTION_H
#define TCLAP_ARG_EXCEPTION_H

#include <ipl_config.h>

#include <iplbase/abort.hxx>

#include <common/iplcommon_dso.h>
#include <common/error/Error.hxx>
#include <common/CommonError.hxx>

#include <string>
// #include <exception>
#include <iostream>

namespace TCLAP {

// our very own error API

inline void arg_exception(const std::string &text="undefined exception",
                          const std::string &id="undefined",
                          const std::string &td="Generic ArgException")
{
    std::cerr << td << ": " << id << "\n" << text << std::endl;
    iplbase::abort();
}

// inline void arg_parse_exception(const std::string &text="undefined exception",
//                                 const std::string &id="undefined")
// {
//     arg_exception(text, id,
//                     "Exception found while parsing the value the Arg has been passed.");
// }
// 
// inline void cmd_line_parse_exception(const std::string &text="undefined exception",
//                                         const std::string &id="undefined")
// {
//     arg_exception(text, id,
//                     "Exception found when the values on the command line do not meet "
//                     "the requirements of the defined Args." );
// }
        
inline void specification_exception(const std::string &text="undefined exception",
                                    const std::string &id="undefined")
{
    arg_exception(text, id,
                  "Exception found when an Arg object is improperly defined by the developer" );
}
    
enum Errors
{
    ARG_PARSE_ERROR,
    CMDLINE_PARSE_ERROR,
//     SPEC_ERROR,
};

extern const ipl::ErrorID ERROR_TABLE[];
extern IPLCOMMON_EXPORT ipl::ErrorType Error;

} // namespace TCLAP

#endif

