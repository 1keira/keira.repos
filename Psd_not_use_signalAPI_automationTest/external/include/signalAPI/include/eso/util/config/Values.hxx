/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef UTIL_CONFIG_VALUES_HXX
#define UTIL_CONFIG_VALUES_HXX

#include <ipl_config.h>
#include <common/stdint.h>
#include <common/types/map.hxx>
#include <common/types/vector.hxx>
#include <common/types/string.hxx>
#include <util/util_dso.h>
#include <util/UnicodeString.hxx>
#include <util/config/ValueIterator.hxx>

namespace util {
namespace config {

// Forware declarations for the generic Value interface
class Dictionary;
class Array;
class ValueBool;
class ValueNull;

/*!
\brief    instance for one value out of the config-value dictionary tree. A config-value can be
        - an array of entries
        - a dictionary of entries
        - a single value of type int, double, string, bool
        Depending on it's type different access to the content is possible
*/
class UTIL_EXPORT Value {
public: // types

    /// Typedef that represents a nonconst iterator.
    typedef value_iterator<
        ipl::map<ipl::string, Value*>::iterator > iterator;

    //! Iterator type to the map of dictionary Values
    typedef value_iterator<
        ipl::map<ipl::string, Value*>::const_iterator > const_iterator;

public:

    static void printCompact(bool c) IPL_NOEXCEPT  {
        g_print_compact = c;
    }
    static bool printCompact() IPL_NOEXCEPT  {
        return g_print_compact;
    }

    //! flag for the print methods either print human readable or as compact as possible
    virtual ~Value() IPL_NOEXCEPT  {};

    virtual Value * clone() const
    {
        return NULL;
    }

    /*!
    \brief    retrieve from an array of dictionaries the element, which has the
            given key-string_value pair
    \return    the requested Value or an default empty value, in case of
                - Array is no Array
                - Array is no Array of dictionaries
                - dictionary doesn't contain the requested key-string_value pair
    */
    static const Value& getDictFromArray (const Value& array, const char* key, const char* value) IPL_NOEXCEPT;

    /*!
    \brief    retrive an undefined Value
    */
    static const Value& getUndefined() IPL_NOEXCEPT ;

    /*!
    \brief    retrieve a bool-value with the given state
    */
    static ValueBool& getBool (bool value) IPL_NOEXCEPT;

    /*!
    \brief    retrieve a null-value
    */
    static ValueNull& getNull() IPL_NOEXCEPT ;


    /*!
    \brief    In case of the Value is a dictionary it's the begin iterator to the concrete map, otherwise
            it's the begin iterator of an empty map
    \return    end-iterator
    \errorindicator
            none
    \errors    none
    */
    virtual const_iterator begin()const IPL_NOEXCEPT;
//            virtual const_iterator begin() const { return const_iterator (g_null_map.begin());  };


    /*!
    \brief    In case of the Value is a dictionary it's the end iterator to the concrete map, otherwise
            it's the end iterator of an empty map
    \return    end-iterator
    \errorindicator
            none
    \errors    none
    */
    virtual const_iterator end() const IPL_NOEXCEPT;
    /*!
    \brief    In case of the Value is a dictionary access to an entry of
            the dictionary by the related key
    \return    instance to the concrete value access by the key, or an empty value which is !isDefined()
    \errorindicator
            none
    \errors    none
    */
    virtual const Value& operator[] (const char* key) const IPL_NOEXCEPT;
    virtual const Value& operator[] (const ipl::string& key) const IPL_NOEXCEPT;

    /*!
    \brief    In case of the Value is a dictionary check whether an an entry with
            the related key is available or not
    \return    true in case of existing entry, otherwise FALSE
    \errorindicator
            none
    \errors    none
    */
    virtual bool hasKey (const char* key) const IPL_NOEXCEPT { return false; };
    virtual bool hasKey (const ipl::string& key) const IPL_NOEXCEPT { return false; };

    /*!
    \brief    In case of the Value is an array access to an entry of
            the array by the related index
    \return    instance to the concrete value access by the index, or an empty value which is !isDefined()
    \errorindicator
            none
    \errors    none
    */
    virtual const Value& operator[] (const size_t index) const IPL_NOEXCEPT;

    /*!
    \brief    In case of the Value is an array return the number
            of items in the array
    \return    number of items or 0
    \errorindicator
            none
    \errors    none
    */
    virtual size_t arraySize() const IPL_NOEXCEPT  { return 0; };

    /*!
    \brief    access the content of an integer value
    \return    false in case the instance is an integer value otherwise true
    \errorindicator
            return value
    \errors    none
    */
    virtual bool get (int32_t& value) const IPL_NOEXCEPT  { return true; };
    virtual bool get (uint32_t& value) const IPL_NOEXCEPT  { return true; };
    virtual bool get (int64_t& value) const IPL_NOEXCEPT  { return true; };
    virtual bool get (uint64_t& value) const IPL_NOEXCEPT  { return true; };

    /*!
    \brief    access the content of a double value
    \return    false in case the instance is an double value otherwise true
    \errorindicator
            return value
    \errors    none
    */
    virtual bool get (double& value) const IPL_NOEXCEPT { return true; };

    /*!
    \brief    access the content of a string value
    \return    false in case the instance is an string value otherwise true
    \errorindicator
            return value
    \errors    none
    */
    virtual bool get (ipl::string& value) const IPL_NOEXCEPT { return true; };
    virtual bool get (util::UnicodeString& value) const IPL_NOEXCEPT { return true; };

    /*!
    \brief    access the content of a bool value
    \return    false in case the instance is an string value otherwise true
    \errorindicator
            return value
    \errors    none
    */
    virtual bool get (bool& value) const IPL_NOEXCEPT  { return true; };

    /*!
    \brief    check if the concrete value instance is a dictionary
    \return    true if yes, otherwise false
    \errors    none
    */
    virtual bool isDictionary() const IPL_NOEXCEPT  { return false; }

    /*!
    \brief    check if the concrete value instance is an array
    \return    true if yes, otherwise false
    \errors    none
    */
    virtual bool isArray() const IPL_NOEXCEPT  { return false; }

    /*!
    \brief    check if the concrete value instance is one of int, double, bool, string or unicode-string
    \return    true if yes, otherwise false
    \errors    none
    */
    virtual bool isValue() const IPL_NOEXCEPT  { return false; }

    //! check if the concrete value instance if of type string
    virtual bool isString() const IPL_NOEXCEPT  { return false; }
    //! check if the concrete value instance if of type unicodestring
    virtual bool isUnicodeString() const IPL_NOEXCEPT  { return false; }
    //! check if the concrete value instance if of type integer
    virtual bool isInt() const IPL_NOEXCEPT  { return false; }
    //! check if the concrete value instance if of type float
    virtual bool isFloat() const IPL_NOEXCEPT  { return false; }

    /*!
    \brief    check if the concrete value instance is a NULL value. A NULL value is
            a defined value node but without content
    \return    true if yes, otherwise false
    \errors    none
    */
    virtual bool isNull() const IPL_NOEXCEPT  { return false; }

    /*!
    \brief    check if the concrete value instance is a bool value.
    \return    true if yes, otherwise false
    \errors    none
    */
    virtual bool isBool() const IPL_NOEXCEPT  { return false; }

    /*!
    \brief    check if the value instance exists in the config-tree
    \return    true if yes, otherwise false
    \errors    none
    */
    virtual bool isDefined() const IPL_NOEXCEPT  { return false; }

    /*!
    \brief    like const Value& operator[](const char* key), but not a const
            reference but a changable reference is returned
    \return    instance to the concrete value access by the key, or NULL if the
            requested value isn't a dictionary or the key is not part of the dictionary
    \errorindicator
            none
    \errors    none
    */
    virtual util::config::Dictionary* getEditableDictionary(const char* key) const IPL_NOEXCEPT { return NULL; };
    virtual util::config::Dictionary* getEditableDictionary(const ipl::string& key) const IPL_NOEXCEPT { return NULL; };

    /*!
    \brief    get the related config value as editable dictionary
    \return    instance to the dictionary, or NULL if the
            requested value isn't a dictionary
    */
    virtual util::config::Dictionary* getEditableDictionary() IPL_NOEXCEPT  { return NULL; };

    /*!
    \brief    like const Value& operator[](const size_t index), but not a const
            reference but a changable reference is returned
    \return    instance to the concrete value access by the key, or NULL
    \errorindicator
            none
    \errors    none
    */
    virtual util::config::Array* getEditableArray (const char* key) const IPL_NOEXCEPT { return NULL; };
    virtual util::config::Array* getEditableArray (const ipl::string& key) const IPL_NOEXCEPT { return NULL; };

    /*!
    \brief    get the related config value as editable array
    \return    instance to the array, or NULL if the
            requested value isn't an array
    */
    virtual util::config::Array* getEditableArray() const IPL_NOEXCEPT  { return NULL; };

    virtual ipl::ostream& print (ipl::ostream &stream) const IPL_NOEXCEPT  {
        stream << "undefined";
        return stream;
    }

    //! equals operator
    virtual bool operator==(const util::config::Value& other) const IPL_NOEXCEPT  { return false; }
    virtual bool operator!=(const util::config::Value& other) IPL_NOEXCEPT  {return !(other == *this);}

    //! \brief A value allocated with \c new may only be deleted
    //! if this returns \c true!
    // Base class is false because it is used for g_undef_value
    virtual bool deletable() const { return false; }

public: // data

    static ValueBool g_bool_value_false;
    static ValueBool g_bool_value_true;
    static ValueNull g_null_value;
    static Dictionary g_null_map;
    static Value g_undef_value;
protected:
    static bool g_print_compact;

};

inline ipl::ostream &operator << (ipl::ostream &stream, const util::config::Value &value)    {
    return value.print(stream);
}


/*!
    \brief    base class for all concrete util::config:Value implementations
*/
template<typename T>
class UTIL_EXPORT ValueBaseT : public Value {
public:
    ValueBaseT() IPL_NOEXCEPT  : m_value() {};
    virtual ~ValueBaseT() {};
    virtual bool isDefined() const IPL_NOEXCEPT  { return true; }
    bool deletable() const override { return true; }
protected:
    T m_value;
};

/*!
\brief    concrete util::config:Value which holds a int64_t value and can be retrieved
          as int, uint32_t, int64_t or uint64_t
*/
class UTIL_EXPORT ValueInt : public ValueBaseT<int64_t> {
public:
    ValueInt(int64_t value) IPL_NOEXCEPT  {m_value = value;};
    virtual ValueInt * clone() const IPL_NOEXCEPT  { return new(ipl::nothrow) ValueInt(m_value); }
    using ValueBaseT<int64_t>::get;
    virtual bool get (int& value) const IPL_NOEXCEPT  { value = (int)m_value; return false;};
    virtual bool get (uint32_t& value) const IPL_NOEXCEPT  { value = (uint32_t)m_value; return false;};
    virtual bool get (int64_t& value) const IPL_NOEXCEPT  { value = (int64_t)m_value; return false;};
    virtual bool get (uint64_t& value) const IPL_NOEXCEPT  { value = (uint64_t)m_value; return false;};
    virtual bool isValue() const IPL_NOEXCEPT  { return true; }
    virtual bool isInt() const IPL_NOEXCEPT  { return true; }
    virtual ipl::ostream& print (ipl::ostream &stream) const IPL_NOEXCEPT {
        stream << m_value;
        return stream;
    }
    virtual bool operator==(const util::config::Value& other) const IPL_NOEXCEPT  {
        return (other.isInt() && (((const util::config::ValueInt&)other).m_value == m_value));
};
};

/*!
\brief    concrete util::config:Value which represents a float value
*/
class UTIL_EXPORT ValueFloat : public ValueBaseT<double> {
public:
    ValueFloat(const double value) IPL_NOEXCEPT   {m_value = value;};
    virtual ValueFloat * clone() const IPL_NOEXCEPT  { return new(ipl::nothrow) ValueFloat(m_value); }
    using ValueBaseT<double>::get;
    virtual bool get (double& value) const IPL_NOEXCEPT  { value = m_value; return false;};
    virtual bool isValue() const IPL_NOEXCEPT  { return true; }
    virtual bool isFloat() const IPL_NOEXCEPT  { return true; }
    virtual ipl::ostream& print(ipl::ostream &stream) const IPL_NOEXCEPT {
        stream << m_value;
        return stream;
    }
    //! using this deprecated - there is no generic float/double comparison
    // see here for a discussion: https://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
    virtual bool operator==(const util::config::Value& other) const IPL_NOEXCEPT;
};

/*!
\brief    concrete util::config:Value which represents a bool value
*/
class UTIL_EXPORT ValueBool : public ValueBaseT<bool> {
public:
    using ValueBaseT<bool>::get;
    //! bools are never copied, there is only one static instance within the system
    virtual bool get (bool& value) const IPL_NOEXCEPT  { value = m_value; return false;};
    virtual bool isValue() const IPL_NOEXCEPT  { return true; }
    virtual bool isBool() const IPL_NOEXCEPT  { return true; }
    // since clone() is const the this pointer inside clone is a const - pointer.
    // the contract wants us to return a non-const pointer, hence the cast
    virtual ValueBool * clone() const IPL_NOEXCEPT  { return const_cast<ValueBool*>(this); }
    virtual ipl::ostream& print (ipl::ostream &stream) const IPL_NOEXCEPT  {
        stream << (m_value?"true":"false");
        return stream;
    }
    virtual bool operator==(const util::config::Value& other) const  IPL_NOEXCEPT {
        return (other.isBool() && (((const util::config::ValueBool&)other).m_value == m_value));
    };
    bool deletable() const override { return false; }
private:
    ValueBool(const bool value) {m_value = value;};
    ValueBool() {};
    friend class Value;
};

/*!
\brief    concrete util::config:Value which represents a NULL value
*/
class UTIL_EXPORT ValueNull : public Value {
public:
    //! nulls are never copied, there is only one static instance within the system
    virtual bool isNull() const IPL_NOEXCEPT  { return true; }
    virtual bool isDefined() const IPL_NOEXCEPT  { return true; }
    // since clone() is const the this pointer inside clone is a const - pointer.
    // the contract wants us to return a non-const pointer, hence the cast
    virtual ValueNull * clone() const IPL_NOEXCEPT  { return const_cast<ValueNull*>(this); }
    virtual ipl::ostream& print (ipl::ostream &stream) const IPL_NOEXCEPT  {
        stream << "null";
        return stream;
    }
    virtual bool operator==(const util::config::Value& other) const  IPL_NOEXCEPT {
        return (other.isNull());
    };
private:
    friend class Value;
    ValueNull() {};
};

/*!
\brief    concrete util::config:Value which represents a string value
*/
class UTIL_EXPORT ValueString : public ValueBaseT<ipl::string> {
public:
    ValueString(const char* str) IPL_NOEXCEPT  {m_value = str;}
    ValueString(const ipl::string& str) IPL_NOEXCEPT  {m_value = str;}
    virtual ValueString * clone() const  IPL_NOEXCEPT { return new(ipl::nothrow) ValueString(m_value); }
    using ValueBaseT<ipl::string>::get;
    virtual bool get (ipl::string& value) const IPL_NOEXCEPT  { value = m_value; return false;};
    virtual bool get (util::UnicodeString& value) const IPL_NOEXCEPT ;
    virtual bool isValue() const  IPL_NOEXCEPT { return true; }
    virtual bool isString() const  IPL_NOEXCEPT { return true; }
    virtual ipl::ostream& print (ipl::ostream &stream) const IPL_NOEXCEPT ;
    virtual bool operator==(const util::config::Value& other) const IPL_NOEXCEPT  {
        return (other.isString() && (((const util::config::ValueString&)other).m_value == m_value));
    };
};

/*!
\brief    concrete util::config:Value which represents a util::UnicodeString value
*/
class UTIL_EXPORT ValueUnicodeString : public ValueBaseT<util::UnicodeString> {
public:
    ValueUnicodeString(const util::UnicodeString* str) IPL_NOEXCEPT  { m_value = *str;}
    ValueUnicodeString(const util::UnicodeString& str) IPL_NOEXCEPT  { m_value = str; }
    virtual ValueUnicodeString * clone() const IPL_NOEXCEPT  { return new(ipl::nothrow) ValueUnicodeString(m_value); }
    using ValueBaseT<util::UnicodeString>::get;
    virtual bool get (util::UnicodeString& value) const  IPL_NOEXCEPT { value = m_value; return false;};
    virtual bool isValue() const  IPL_NOEXCEPT { return true; }
    virtual bool isUnicodeString() const  IPL_NOEXCEPT { return true; }
    virtual ipl::ostream& print (ipl::ostream &stream) const IPL_NOEXCEPT;
    virtual bool operator==(const util::config::Value& other)  const IPL_NOEXCEPT {
        return (other.isUnicodeString() && (((const util::config::ValueUnicodeString&)other).m_value == m_value));
    };
};

/*!
\brief    concrete util::config:Value which represents a dictionary
*/
class UTIL_EXPORT Dictionary : public ValueBaseT<ipl::map<ipl::string, Value*> > {
public:
    Dictionary() IPL_NOEXCEPT  {};
    /*!
    \brief    destructor

        all contained instances of util::config::Values are recursively deleted
    */
    virtual ~Dictionary() IPL_NOEXCEPT ;

    virtual Dictionary * clone() const IPL_NOEXCEPT;
    /*!
    \brief    If no entry with the given key exists in the dictionary, it's added,
            otherwise nothing is done

     the instance in added to the dictionary. In case of the dictionatry is
            deleted also this instance is recursively deleted
    \param    key is the key
    \param    val is the value
    \return    false on success, true on error
    */
    bool add (const char* key, Value* val) IPL_NOEXCEPT ;

    /*!
    \brief    If no entry with the given key exists in the dictionary, it's added,
            otherwise the existing one is replaced by the new one

       the replaced config value instance is deleted
    \param    key is the key
    \param    val is the value
    \return    false on success, true on error
    */
    bool set (const char* key, Value* val) IPL_NOEXCEPT ;

    using ValueBaseT<ipl::map<ipl::string, Value*> >::operator[];
    virtual const Value& operator[](const char *key) const IPL_NOEXCEPT ;
    virtual const Value& operator[](const ipl::string& key) const IPL_NOEXCEPT ;

    //! check whether a value with the given key is in the dictionary
    virtual bool hasKey(const char* key) const IPL_NOEXCEPT  { return (m_value.find(key) != m_value.end());    }
    virtual bool hasKey(const ipl::string& key) const IPL_NOEXCEPT  { return (m_value.find(key) != m_value.end());    }

    virtual iterator begin() IPL_NOEXCEPT  {
        return iterator (m_value.begin());
    };
    virtual const_iterator begin() const IPL_NOEXCEPT  {
        return const_iterator (m_value.begin());
    };

    virtual iterator end() IPL_NOEXCEPT {
        return iterator(m_value.end());
    };
    virtual const_iterator end() const  IPL_NOEXCEPT {
        return const_iterator(m_value.end());
    };

    /*!
    \brief    remove the value identified by key from the dictionary
    \param[in] key
            is the key into the dictionary
    \param[in] delete_it
            defines, whether the value instance identified by the key shall
            be deleted on removal or not
    \return    true on error, false on success
    \return    false on success, true on error
    */
    virtual void remove (const char* key, bool delete_it = false) IPL_NOEXCEPT ;

    virtual bool isDictionary() const IPL_NOEXCEPT  { return true; }

    //! see util::config::Value
    virtual util::config::Dictionary* getEditableDictionary(const char* key) const IPL_NOEXCEPT ;
    //! see util::config::Value
    virtual util::config::Dictionary* getEditableDictionary(const ipl::string& key) const IPL_NOEXCEPT ;
    //! see util::config::Value
    virtual util::config::Dictionary* getEditableDictionary() IPL_NOEXCEPT ;
    using ValueBaseT<ipl::map<ipl::string, Value*> >::getEditableArray ;
    //! see util::config::Value
    virtual util::config::Array* getEditableArray(const char* key) const IPL_NOEXCEPT ;
    //! see util::config::Value
    virtual util::config::Array* getEditableArray(const ipl::string& key) const IPL_NOEXCEPT ;

    virtual ipl::ostream& print (ipl::ostream &stream) const IPL_NOEXCEPT  {
        const char *delim="";
        stream << "{";
        for(util::config::Value::const_iterator i=m_value.begin();
            i!=m_value.end(); i++) {
            stream << delim << "\"" << i->first << "\":"
                   << *i->second;
            if (!g_print_compact) {
                stream << "\n";
            }
            delim=",";
        }
        stream << "}";
        return stream;
    }
    virtual bool operator==(const util::config::Value& other) const IPL_NOEXCEPT ;

};

/*!
\brief    concrete util::config:Value which represents an array
*/
class UTIL_EXPORT Array : public ValueBaseT<ipl::vector<Value*> > {
public:
    Array() IPL_NOEXCEPT  {};
    /*!
    \brief    destructor

        is deletes all the contained instances of the config values
    */
    virtual ~Array() IPL_NOEXCEPT ;

    virtual Array * clone() const IPL_NOEXCEPT ;
    /*!
    \brief    add a new value to the array
    */
    virtual bool add (Value* val)  IPL_NOEXCEPT {
        m_value.push_back(val);
        return false;
    }

    /*!
    \brief    overwrite a value within the array

        The overwritten instance is deleted
    \return    true in case of the index is out-of-range, false in case of success
    */
    virtual bool set (const size_t index, Value* val) IPL_NOEXCEPT ;

    using ValueBaseT<ipl::vector<Value*> >::operator[];
    virtual const Value& operator[](const size_t index) const IPL_NOEXCEPT ;

    /*!
    \brief    returns the reference to the value instance reference by
            the given index

    \return    the requested instance or a "undefined" value in case of
            the index is out of range
    */
    Value& operator[](const size_t index) IPL_NOEXCEPT  ;

    virtual size_t arraySize() const IPL_NOEXCEPT  { return m_value.size(); };

    using ValueBaseT<ipl::vector<Value*> >::getEditableArray;
    //! see util::config::Value
    virtual util::config::Array* getEditableArray() const IPL_NOEXCEPT ;

    virtual bool isArray() const  IPL_NOEXCEPT { return true; }
    virtual ipl::ostream& print (ipl::ostream &stream) const  IPL_NOEXCEPT {
        const char *delim="";
        stream << "[";
        for(size_t i=0; i<m_value.size(); i++) {
            stream << delim << *m_value[i];
            if (!g_print_compact) {
                stream << "\n";
            }
            delim=",";
        }
        stream << "]";
        return stream;
    }
    virtual bool operator==(const util::config::Value& other) const IPL_NOEXCEPT ;
};

} // namespace config
} // namespace util

#endif //UTIL_CONFIG_VALUES_HXX
