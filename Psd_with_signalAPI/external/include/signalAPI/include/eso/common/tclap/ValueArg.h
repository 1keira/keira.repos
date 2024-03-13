/****************************************************************************** 
 * 
 *  file:  ValueArg.h
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

#ifndef TCLAP_VALUE_ARGUMENT_H
#define TCLAP_VALUE_ARGUMENT_H

#include <ipl_config.h>

#include <string>
#include <vector>

#include <common/tclap/Arg.h>
#include <common/tclap/Constraint.h>

namespace TCLAP {

/**
 * The basic labeled argument that parses a value.
 * This is a template class, which means the type T defines the type
 * that a given object will attempt to parse when the flag/name is matched
 * on the command line.  While there is nothing stopping you from creating
 * an unflagged ValueArg, it is unwise and would cause significant problems.
 * Instead use an UnlabeledValueArg.
 */
template<class T>
class ValueArg : public Arg 
{
    protected:

        /**
         * The value parsed from the command line.
         * Can be of any type, as long as the >> operator for the type
         * is defined.
         */
        T _value;

        /**
         * Used to support the reset() method so that ValueArg can be
         * reset to their constructed value.
         */
        T _default;

        /**
         * A human readable description of the type to be parsed.
         * This is a hack, plain and simple.  Ideally we would use RTTI to
         * return the name of type T, but until there is some sort of
         * consistent support for human readable names, we are left to our
         * own devices.
         */
        std::string _typeDesc;

        /**
         * A Constraint this Arg must conform to. 
         */
        Constraint<T>* _constraint;

        /**
         * Extracts the value from the string.
         * Attempts to parse string as type T, if this fails an exception
         * is thrown.
         * \param val - value to be parsed. 
         */
        bool _extractValue( const std::string& val ) IPL_NOEXCEPT;

    public:

        /**
         * Labeled ValueArg constructor.
         * You could conceivably call this constructor with a blank flag, 
         * but that would make you a bad person.  It would also cause
         * an exception to be thrown.   If you want an unlabeled argument, 
         * use the other constructor.
         * \param flag - The one character flag that identifies this
         * argument on the command line.
         * \param name - A one word name for the argument.  Can be
         * used as a long flag on the command line.
         * \param desc - A description of what the argument is for or
         * does.
         * \param req - Whether the argument is required on the command
         * line.
         * \param value - The default value assigned to this argument if it
         * is not present on the command line.
         * \param typeDesc - A short, human readable description of the
         * type that this object expects.  This is used in the generation
         * of the USAGE statement.  The goal is to be helpful to the end user
         * of the program.
         * \param v - An optional visitor.  You probably should not
         * use this unless you have a very good reason.
         */
        ValueArg( const std::string& flag, 
                  const std::string& name, 
                  const std::string& desc, 
                  bool req, 
                  T value,
                  const std::string& typeDesc,
                  Visitor* v = NULL) IPL_NOEXCEPT;
                 
                 
        /**
         * Labeled ValueArg constructor.
         * You could conceivably call this constructor with a blank flag, 
         * but that would make you a bad person.  It would also cause
         * an exception to be thrown.   If you want an unlabeled argument, 
         * use the other constructor.
         * \param flag - The one character flag that identifies this
         * argument on the command line.
         * \param name - A one word name for the argument.  Can be
         * used as a long flag on the command line.
         * \param desc - A description of what the argument is for or
         * does.
         * \param req - Whether the argument is required on the command
         * line.
         * \param value - The default value assigned to this argument if it
         * is not present on the command line.
         * \param typeDesc - A short, human readable description of the
         * type that this object expects.  This is used in the generation
         * of the USAGE statement.  The goal is to be helpful to the end user
         * of the program.
         * \param parser - A CmdLine parser object to add this Arg to
         * \param v - An optional visitor.  You probably should not
         * use this unless you have a very good reason.
         */
        ValueArg( const std::string& flag, 
                  const std::string& name, 
                  const std::string& desc, 
                  bool req, 
                  T value,
                  const std::string& typeDesc,
                  CmdLineInterface& parser,
                  Visitor* v = NULL ) IPL_NOEXCEPT;
 
        /**
         * Labeled ValueArg constructor.
         * You could conceivably call this constructor with a blank flag, 
         * but that would make you a bad person.  It would also cause
         * an exception to be thrown.   If you want an unlabeled argument, 
         * use the other constructor.
         * \param flag - The one character flag that identifies this
         * argument on the command line.
         * \param name - A one word name for the argument.  Can be
         * used as a long flag on the command line.
         * \param desc - A description of what the argument is for or
         * does.
         * \param req - Whether the argument is required on the command
         * line.
         * \param value - The default value assigned to this argument if it
         * is not present on the command line.
         * \param constraint - A pointer to a Constraint object used
         * to constrain this Arg.
         * \param parser - A CmdLine parser object to add this Arg to.
         * \param v - An optional visitor.  You probably should not
         * use this unless you have a very good reason.
         */
        ValueArg( const std::string& flag, 
                  const std::string& name, 
                  const std::string& desc, 
                  bool req, 
                  T value,
                  Constraint<T>* constraint,
                  CmdLineInterface& parser,
                  Visitor* v = NULL ) IPL_NOEXCEPT;
      
        /**
         * Labeled ValueArg constructor.
         * You could conceivably call this constructor with a blank flag, 
         * but that would make you a bad person.  It would also cause
         * an exception to be thrown.   If you want an unlabeled argument, 
         * use the other constructor.
         * \param flag - The one character flag that identifies this
         * argument on the command line.
         * \param name - A one word name for the argument.  Can be
         * used as a long flag on the command line.
         * \param desc - A description of what the argument is for or
         * does.
         * \param req - Whether the argument is required on the command
         * line.
         * \param value - The default value assigned to this argument if it
         * is not present on the command line.
         * \param constraint - A pointer to a Constraint object used
         * to constrain this Arg.
         * \param v - An optional visitor.  You probably should not
         * use this unless you have a very good reason.
         */
        ValueArg( const std::string& flag, 
                  const std::string& name, 
                  const std::string& desc, 
                  bool req, 
                  T value,
                  Constraint<T>* constraint,
                  Visitor* v = NULL ) IPL_NOEXCEPT;

        /**
         * Handles the processing of the argument.
         * This re-implements the Arg version of this method to set the
         * _value of the argument appropriately.  It knows the difference
         * between labeled and unlabeled.
         * \param i - Pointer the the current argument in the list.
         * \param args - Mutable list of strings. Passed 
         * in from main().
         */
        virtual bool processArg(int* i, std::vector<std::string>& args) IPL_NOEXCEPT; 

        /**
         * Returns the value of the argument.
         */
        T& getValue() IPL_NOEXCEPT ;

        /**
         * Specialization of shortID.
         * \param val - value to be used.
         */
        virtual std::string shortID(const std::string& val = "val") const IPL_NOEXCEPT;

        /**
         * Specialization of longID.
         * \param val - value to be used.
         */
        virtual std::string longID(const std::string& val = "val") const IPL_NOEXCEPT;
        
        virtual void reset() IPL_NOEXCEPT;

private:
       /**
        * Prevent accidental copying
        */
       ValueArg<T>(const ValueArg<T>& rhs) IPL_NOEXCEPT;
       ValueArg<T>& operator=(const ValueArg<T>& rhs) IPL_NOEXCEPT;
};


/**
 * Constructor implementation.
 */
template<class T>
ValueArg<T>::ValueArg(const std::string& flag, 
                      const std::string& name, 
                      const std::string& desc, 
                      bool req, 
                      T val,
                      const std::string& typeDesc,
                      Visitor* v) IPL_NOEXCEPT
: Arg(flag, name, desc, req, true, v),
  _value( val ),
  _default( val ),
  _typeDesc( typeDesc ),
  _constraint( NULL )
{ }

template<class T>
ValueArg<T>::ValueArg(const std::string& flag, 
                      const std::string& name, 
                      const std::string& desc, 
                      bool req, 
                      T val,
                      const std::string& typeDesc,
                      CmdLineInterface& parser,
                      Visitor* v) IPL_NOEXCEPT
: Arg(flag, name, desc, req, true, v),
  _value( val ),
  _default( val ),
  _typeDesc( typeDesc ),
  _constraint( NULL )
{ 
    parser.add( this );
}

template<class T>
ValueArg<T>::ValueArg(const std::string& flag, 
                      const std::string& name, 
                      const std::string& desc, 
                      bool req, 
                      T val,
                      Constraint<T>* constraint,
                      Visitor* v) IPL_NOEXCEPT
: Arg(flag, name, desc, req, true, v),
  _value( val ),
  _default( val ),
  _typeDesc( constraint->shortID() ),
  _constraint( constraint )
{ }

template<class T>
ValueArg<T>::ValueArg(const std::string& flag, 
                      const std::string& name, 
                      const std::string& desc, 
                      bool req, 
                      T val,
                      Constraint<T>* constraint,
                      CmdLineInterface& parser,
                      Visitor* v) IPL_NOEXCEPT
: Arg(flag, name, desc, req, true, v),
  _value( val ),
  _default( val ),
  _typeDesc( constraint->shortID() ),
  _constraint( constraint )
{ 
    parser.add( this );
}


/**
 * Implementation of getValue().
 */
template<class T>
T& ValueArg<T>::getValue() IPL_NOEXCEPT { return _value; }

/**
 * Implementation of processArg().
 */
template<class T>
bool ValueArg<T>::processArg(int *i, std::vector<std::string>& args) IPL_NOEXCEPT
{
    if ( _ignoreable && Arg::ignoreRest() )
        return false;

    if ( _hasBlanks( args[*i] ) )
        return false;

    std::string flag = args[*i];

    std::string value = "";
    trimFlag( flag, value );

    if ( argMatches( flag ) )
    {
        if ( _alreadySet )
        {
            if ( _xorSet )
                ipl_raise(Error, CMDLINE_PARSE_ERROR,
                          ("Mutually exclusive argument already set: "+toString()).c_str());
            else
                ipl_raise(Error, CMDLINE_PARSE_ERROR,
                          ("Argument already set: "+toString()).c_str());
            return false;
        }

        if ( Arg::delimiter() != ' ' && value == "" ) {
            ipl_raise(Error, ARG_PARSE_ERROR,
                      ("Couldn't find delimiter for this argument: "+toString()).c_str());
            return false;
        }

        if ( value == "" )
        {
            (*i)++;
            if ( static_cast<unsigned int>(*i) < args.size() ) {
                if(_extractValue( args[*i] ))
                    return false;
            } else {
                ipl_raise(Error, ARG_PARSE_ERROR,
                          ("Missing a value for this argument: "+toString()).c_str());
                return false;
            }
        }
        else
            if(_extractValue( value ))
                return false;
                
        _alreadySet = true;
        _checkWithVisitor();
        return true;
    }    
    else
        return false;
}

/**
 * Implementation of shortID.
 */
template<class T>
std::string ValueArg<T>::shortID(const std::string& val) const IPL_NOEXCEPT
{
    static_cast<void>(val); // Ignore input, don't warn
    return Arg::shortID( _typeDesc ); 
}

/**
 * Implementation of longID.
 */
template<class T>
std::string ValueArg<T>::longID(const std::string& val) const IPL_NOEXCEPT
{
    static_cast<void>(val); // Ignore input, don't warn
    return Arg::longID( _typeDesc ); 
}

template<class T>
bool ValueArg<T>::_extractValue( const std::string& val ) IPL_NOEXCEPT 
{
    if(ExtractValue(_value, val, typename ArgTraits<T>::ValueCategory()))
        return true;
    
    if ( _constraint != NULL && ! _constraint->check( _value ) ) {
        ipl_raise(Error, CMDLINE_PARSE_ERROR,
                  ("Value '"+val+"' does not meet constraint: "+
                   _constraint->description()+": "+toString()).c_str());
        return true;
    }
    
    return false;
}

template<class T>
void ValueArg<T>::reset() IPL_NOEXCEPT
{
    Arg::reset();
    _value = _default;
}

} // namespace TCLAP

#endif
