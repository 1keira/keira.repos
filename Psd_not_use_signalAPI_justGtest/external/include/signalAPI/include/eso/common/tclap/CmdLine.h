// -*- Mode: c++; c-basic-offset: 4; tab-width: 4; -*-

/******************************************************************************
 *
 *  file:  CmdLine.h
 *
 *  Copyright (c) 2003, Michael E. Smoot .
 *  Copyright (c) 2004, Michael E. Smoot, Daniel Aarno.
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

#ifndef TCLAP_CMDLINE_H
#define TCLAP_CMDLINE_H

#include <ipl_config.h>

#include <common/tclap/SwitchArg.h>
#include <common/tclap/MultiSwitchArg.h>
#include <common/tclap/UnlabeledValueArg.h>
#include <common/tclap/UnlabeledMultiArg.h>

#include <common/tclap/XorHandler.h>
#include <common/tclap/HelpVisitor.h>
#include <common/tclap/VersionVisitor.h>
#include <common/tclap/IgnoreRestVisitor.h>

#include <common/tclap/CmdLineOutput.h>
#include <common/tclap/StdOutput.h>

#include <common/tclap/Constraint.h>
#include <common/tclap/ValuesConstraint.h>

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <iplbase/exit.hxx>

namespace TCLAP {

template<typename T> void DelPtr(T ptr) IPL_NOEXCEPT
{
    delete ptr;
}

template<typename C> void ClearContainer(C &c) IPL_NOEXCEPT
{
    typedef typename C::value_type value_type;
    std::for_each(c.begin(), c.end(), DelPtr<value_type>);
    c.clear();
}


/**
 * The base class that manages the command line definition and passes
 * along the parsing to the appropriate Arg classes.
 */
class CmdLine : public CmdLineInterface
{
    protected:

        /**
         * The list of arguments that will be tested against the
         * command line.
         */
        std::list<Arg*> _argList;

        /**
         * The name of the program.  Set to argv[0].
         */
        std::string _progName;

        /**
         * A message used to describe the program.  Used in the usage output.
         */
        std::string _message;

        /**
         * The version to be displayed with the --version switch.
         */
        std::string _version;

        /**
         * The number of arguments that are required to be present on
         * the command line. This is set dynamically, based on the
         * Args added to the CmdLine object.
         */
        int _numRequired;

        /**
         * The character that is used to separate the argument flag/name
         * from the value.  Defaults to ' ' (space).
         */
        char _delimiter;

        /**
         * The handler that manages xoring lists of args.
         */
        XorHandler _xorHandler;

        /**
         * A list of Args to be explicitly deleted when the destructor
         * is called.  At the moment, this only includes the three default
         * Args.
         */
        std::list<Arg*> _argDeleteOnExitList;

        /**
         * A list of Visitors to be explicitly deleted when the destructor
         * is called.  At the moment, these are the Visitors created for the
         * default Args.
         */
        std::list<Visitor*> _visitorDeleteOnExitList;

        /**
         * Object that handles all output for the CmdLine.
         */
        CmdLineOutput* _output;

        /**
         * Should CmdLine handle parsing exceptions internally?
         */
        bool _handleExceptions;

        /**
         * Throws an exception listing the missing args.
         */
        void missingArgsException() IPL_NOEXCEPT;

        /**
         * Checks whether a name/flag string matches entirely matches
         * the Arg::blankChar.  Used when multiple switches are combined
         * into a single argument.
         * \param s - The message to be used in the usage.
         */
        bool _emptyCombined(const std::string& s) IPL_NOEXCEPT;

        /**
         * Perform a delete ptr; operation on ptr when this object is deleted.
         */
        void deleteOnExit(Arg* ptr) IPL_NOEXCEPT;

        /**
         * Perform a delete ptr; operation on ptr when this object is deleted.
         */
        void deleteOnExit(Visitor* ptr) IPL_NOEXCEPT;

private:

        /**
         * Prevent accidental copying.
         */
        CmdLine(const CmdLine& rhs) IPL_NOEXCEPT;
        CmdLine& operator=(const CmdLine& rhs) IPL_NOEXCEPT;

        /**
         * Encapsulates the code common to the constructors
         * (which is all of it).
         */
        void _constructor() IPL_NOEXCEPT;


        /**
         * Is set to true when a user sets the output object. We use this so
         * that we don't delete objects that are created outside of this lib.
         */
        bool _userSetOutput;

        /**
         * Whether or not to automatically create help and version switches.
         */
        bool _helpAndVersion;
        
        bool has_error;

    public:

        /**
         * Command line constructor. Defines how the arguments will be
         * parsed.
         * \param message - The message to be used in the usage
         * output.
         * \param delimiter - The character that is used to separate
         * the argument flag/name from the value.  Defaults to ' ' (space).
         * \param version - The version number to be used in the
         * --version switch.
         * \param helpAndVersion - Whether or not to create the Help and
         * Version switches. Defaults to true.
         */
        CmdLine(const std::string& message,
                const char delimiter = ' ',
                const std::string& version = "none",
                bool helpAndVersion = true) IPL_NOEXCEPT;

        /**
         * Deletes any resources allocated by a CmdLine object.
         */
        virtual ~CmdLine() IPL_NOEXCEPT;

        /**
         * Adds an argument to the list of arguments to be parsed.
         * \param a - Argument to be added.
         */
        void add( Arg& a ) IPL_NOEXCEPT;

        /**
         * An alternative add.  Functionally identical.
         * \param a - Argument to be added.
         */
        void add( Arg* a ) IPL_NOEXCEPT;

        /**
         * Add two Args that will be xor'd.  If this method is used, add does
         * not need to be called.
         * \param a - Argument to be added and xor'd.
         * \param b - Argument to be added and xor'd.
         */
        void xorAdd( Arg& a, Arg& b ) IPL_NOEXCEPT;

        /**
         * Add a list of Args that will be xor'd.  If this method is used,
         * add does not need to be called.
         * \param xors - List of Args to be added and xor'd.
         */
        void xorAdd( std::vector<Arg*>& xors ) IPL_NOEXCEPT;

        /**
         * Parses the command line.
         * \param argc - Number of arguments.
         * \param argv - Array of arguments.
         */
        void parse(int argc, const char * const * argv) IPL_NOEXCEPT;

        /**
         * Parses the command line.
         * \param args - A vector of strings representing the args.
         * args[0] is still the program name.
         */
        void parse(std::vector<std::string>& args) IPL_NOEXCEPT;

        /**
         *
         */
        CmdLineOutput* getOutput() IPL_NOEXCEPT;

        /**
         *
         */
        void setOutput(CmdLineOutput* co) IPL_NOEXCEPT;

        /**
         *
         */
        std::string& getVersion() IPL_NOEXCEPT;

        /**
         *
         */
        std::string& getProgramName() IPL_NOEXCEPT;

        /**
         *
         */
        std::list<Arg*>& getArgList() IPL_NOEXCEPT;

        /**
         *
         */
        XorHandler& getXorHandler() IPL_NOEXCEPT;

        /**
         *
         */
        char getDelimiter() IPL_NOEXCEPT;

        /**
         *
         */
        std::string& getMessage() IPL_NOEXCEPT;

        /**
         *
         */
        bool hasHelpAndVersion() IPL_NOEXCEPT;

        /**
         * Disables or enables CmdLine's internal parsing exception handling.
         *
         * @param state Should CmdLine handle parsing exceptions internally?
         */
        void setExceptionHandling(const bool state) IPL_NOEXCEPT;

        /**
         * Returns the current state of the internal exception handling.
         *
         * @retval true Parsing exceptions are handled internally.
         * @retval false Parsing exceptions are propagated to the caller.
         */
        bool getExceptionHandling() const IPL_NOEXCEPT;

        /**
         * Allows the CmdLine object to be reused.
         */
        void reset() IPL_NOEXCEPT;
        
        bool hasError() const IPL_NOEXCEPT { return has_error; }

};


///////////////////////////////////////////////////////////////////////////////
//Begin CmdLine.cpp
///////////////////////////////////////////////////////////////////////////////

inline CmdLine::CmdLine(const std::string& m,
                        char delim,
                        const std::string& v,
                        bool help ) IPL_NOEXCEPT
    :
  _argList(std::list<Arg*>()),
  _progName("not_set_yet"),
  _message(m),
  _version(v),
  _numRequired(0),
  _delimiter(delim),
  _xorHandler(XorHandler()),
  _argDeleteOnExitList(std::list<Arg*>()),
  _visitorDeleteOnExitList(std::list<Visitor*>()),
  _output(0),
  _handleExceptions(true),
  _userSetOutput(false),
  _helpAndVersion(help),
  has_error(false)
{
    _constructor();
}

inline CmdLine::~CmdLine() IPL_NOEXCEPT
{
    ClearContainer(_argDeleteOnExitList);
    ClearContainer(_visitorDeleteOnExitList);

    if ( !_userSetOutput ) {
        delete _output;
        _output = 0;
    }
}

inline void CmdLine::_constructor() IPL_NOEXCEPT
{
    _output = new StdOutput;

    Arg::setDelimiter( _delimiter );

    Visitor* v;

    if ( _helpAndVersion )
    {
        v = new HelpVisitor( this, &_output );
        SwitchArg* help = new SwitchArg("h","help",
                              "Displays usage information and exits.",
                              false, v);
        add( help );
        deleteOnExit(help);
        deleteOnExit(v);

        v = new VersionVisitor( this, &_output );
        SwitchArg* vers = new SwitchArg("","version",
                              "Displays version information and exits.",
                              false, v);
        add( vers );
        deleteOnExit(vers);
        deleteOnExit(v);
    }

    v = new IgnoreRestVisitor();
    SwitchArg* ignore  = new SwitchArg(Arg::flagStartString(),
              Arg::ignoreNameString(),
              "Ignores the rest of the labeled arguments following this flag.",
              false, v);
    add( ignore );
    deleteOnExit(ignore);
    deleteOnExit(v);
}

inline void CmdLine::xorAdd( std::vector<Arg*>& ors ) IPL_NOEXCEPT
{
    _xorHandler.add( ors );

    for (ArgVectorIterator it = ors.begin(); it != ors.end(); it++)
    {
        (*it)->forceRequired();
        (*it)->setRequireLabel( "OR required" );
        add( *it );
    }
}

inline void CmdLine::xorAdd( Arg& a, Arg& b ) IPL_NOEXCEPT
{
    std::vector<Arg*> ors;
    ors.push_back( &a );
    ors.push_back( &b );
    xorAdd( ors );
}

inline void CmdLine::add( Arg& a ) IPL_NOEXCEPT
{
    add( &a );
}

inline void CmdLine::add( Arg* a ) IPL_NOEXCEPT
{
    for( ArgListIterator it = _argList.begin(); it != _argList.end(); it++ )
        if ( *a == *(*it) )
            specification_exception("Argument with same flag/name already exists!",
                                    a->longID());

    a->addToList( _argList );

    if ( a->isRequired() )
        _numRequired++;
}


inline void CmdLine::parse(int argc, const char * const * argv) IPL_NOEXCEPT
{
        // this step is necessary so that we have easy access to
        // mutable strings.
        std::vector<std::string> args;
        for (int i = 0; i < argc; i++)
            args.push_back(argv[i]);

        parse(args);
}

inline void CmdLine::parse(std::vector<std::string>& args) IPL_NOEXCEPT
{
    _progName = args.front();
    args.erase(args.begin());

    int requiredCount = 0;

    for (int i = 0; static_cast<unsigned int>(i) < args.size(); i++) 
    {
        bool matched = false;
        for (ArgListIterator it = _argList.begin();
                it != _argList.end(); it++) {
            bool found=(*it)->processArg( &i, args );
            if(ipl_error && ipl_error.isA(Error)) {  // poor man's exception
                has_error=true;
                return;
            }
            if(found)
            {
                int cnt=_xorHandler.check( *it );
                if(cnt<0) {
                    has_error=true;
                    return;
                }
                requiredCount += cnt;
                matched = true;
                break;
            }
        }

        // checks to see if the argument is an empty combined
        // switch and if so, then we've actually matched it
        if ( !matched && _emptyCombined( args[i] ) )
            matched = true;

        if ( !matched && !Arg::ignoreRest() ) {
            ipl_raise(Error, CMDLINE_PARSE_ERROR,
                        ("Couldn't find match for argument: "+args[i]).c_str());
            has_error=true;
            return;
        }
    }

    if ( requiredCount < _numRequired ) {
        missingArgsException();
        return;
    }

    if ( requiredCount > _numRequired ) {
        ipl_raise(Error, CMDLINE_PARSE_ERROR, "Too many arguments!");
        has_error=true;
        return;
    }
    
    has_error=false;
}

inline bool CmdLine::_emptyCombined(const std::string& s) IPL_NOEXCEPT
{
    if ( s.length() > 0 && s[0] != Arg::flagStartChar() )
        return false;

    for ( int i = 1; static_cast<unsigned int>(i) < s.length(); i++ )
        if ( s[i] != Arg::blankChar() )
            return false;

    return true;
}

inline void CmdLine::missingArgsException() IPL_NOEXCEPT
{
        int count = 0;

        std::string missingArgList;
        for (ArgListIterator it = _argList.begin(); it != _argList.end(); it++)
        {
            if ( (*it)->isRequired() && !(*it)->isSet() )
            {
                missingArgList += (*it)->getName();
                missingArgList += ", ";
                count++;
            }
        }
        missingArgList = missingArgList.substr(0,missingArgList.length()-2);

        std::string msg;
        if ( count > 1 )
            msg = "Required arguments missing: ";
        else
            msg = "Required argument missing: ";

        msg += missingArgList;

        ipl_raise(Error, CMDLINE_PARSE_ERROR, msg.c_str());
        has_error=true;
}

inline void CmdLine::deleteOnExit(Arg* ptr) IPL_NOEXCEPT
{
    _argDeleteOnExitList.push_back(ptr);
}

inline void CmdLine::deleteOnExit(Visitor* ptr) IPL_NOEXCEPT
{
    _visitorDeleteOnExitList.push_back(ptr);
}

inline CmdLineOutput* CmdLine::getOutput() IPL_NOEXCEPT
{
    return _output;
}

inline void CmdLine::setOutput(CmdLineOutput* co) IPL_NOEXCEPT
{
    if ( !_userSetOutput )
        delete _output;
    _userSetOutput = true;
    _output = co;
}

inline std::string& CmdLine::getVersion() IPL_NOEXCEPT
{
    return _version;
}

inline std::string& CmdLine::getProgramName() IPL_NOEXCEPT
{
    return _progName;
}

inline std::list<Arg*>& CmdLine::getArgList() IPL_NOEXCEPT
{
    return _argList;
}

inline XorHandler& CmdLine::getXorHandler() IPL_NOEXCEPT
{
    return _xorHandler;
}

inline char CmdLine::getDelimiter() IPL_NOEXCEPT
{
    return _delimiter;
}

inline std::string& CmdLine::getMessage() IPL_NOEXCEPT
{
    return _message;
}

inline bool CmdLine::hasHelpAndVersion() IPL_NOEXCEPT
{
    return _helpAndVersion;
}

inline void CmdLine::setExceptionHandling(const bool state) IPL_NOEXCEPT
{
    _handleExceptions = state;
}

inline bool CmdLine::getExceptionHandling() const IPL_NOEXCEPT
{
    return _handleExceptions;
}

inline void CmdLine::reset() IPL_NOEXCEPT
{
    for( ArgListIterator it = _argList.begin(); it != _argList.end(); it++ )
        (*it)->reset();
    
    _progName.clear();
}

///////////////////////////////////////////////////////////////////////////////
//End CmdLine.cpp
///////////////////////////////////////////////////////////////////////////////



} //namespace TCLAP
#endif
