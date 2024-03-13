/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifndef OC_REGEXP_HH
#define OC_REGEXP_HH


// =============================================================================
//
//  Crystal Growth Laboratory
//
//  University Erlangen-Nuremberg      Fraunhofer Gesellschaft
//  Department of Material Science     Institute of Integrated Systems
//  Electrical Engineering Materials       Device Technology Devision (IIS-B)
//  Martensstrasse 7               Schottkystrasse 10
//  91058 Erlangen             91058 Erlangen
//  Germany                Germany
//
//  In cooperation with
//
//  University Erlangen-Nuremberg      University Erlangen-Nuremberg
//  Department of Computer Science 9       Department of Computer Science 10
//  Computer Graphics              System Simulation Group
//  Am Weichselgarten 9            Cauerstra?e 6
//  91058 Erlangen             91058 Erlangen
//  Germany                Germany
//
// =============================================================================
//
//  Copyright 2004 (c) by
//  (1) Department of Material Science 6  University Erlangen-Nuremberg, M.Kellner
//  (2) Department of Computer Science 9  University Erlangen-Nuremberg, H.Hadler
//  (3) Department of Computer Science 10 University Erlangen-Nuremberg, J.Treibig
//  (4) Fraunhofer IISb Erlangen Department of Crystal Growth, Dr.Th.Jung
//
//  For Licensing regulations see the accompanying LICENSE file.
//  If this file does not exist and/or does not apply to you, please contact
//  the copyright holders.
//
//
//Copyright (c) 1986, 1993, 1995 by University of Toronto.
//Written by Henry Spencer.  Not derived from licensed software.
//
//Permission is granted to anyone to use this software for any
//purpose on any computer system, and to redistribute it in any way,
//subject to the following restrictions:
//
//1. The author is not responsible for the consequences of use of
//    this software, no matter how awful, even if they arise
//    from defects in it.
//
//2. The origin of this software must not be misrepresented, either
//    by explicit claim or by omission.
//
//3. Altered versions must be plainly marked as such, and must not
//    be misrepresented (by explicit claim or omission) as being
//    the original software.
// *** THIS IS AN ALTERED VERSION.  It was altered by John Gilmore,
// *** hoptoad!gnu, on 27 Dec 1986, to add \< and \> for word-matching
// *** as in BSD grep and ex.
// *** THIS IS AN ALTERED VERSION.  It was altered by John Gilmore,
// *** hoptoad!gnu, on 28 Dec 1986, to optimize characters quoted with \.
// *** THIS IS AN ALTERED VERSION.  It was altered by James A. Woods,
// *** ames!jaw, on 19 June 1987, to quash a regcomp() redundancy.
// *** THIS IS AN ALTERED VERSION.  It was altered by Guy Gascoigne - Piggford
// *** guy@wyrdrune.com, on 15 March 1998, porting it to C++ and converting
// *** it to be the engine for the Regexp class
// *** THIS IS AN ALTERED VERSION.  It was altered by e.solutions,
// *** to adapt it to the e.solutions framework
//
//4. This notice must not be removed or altered.
//
// =============================================================================


// INCLUDE
// =======

// ORCAN include

//#include <oc/config.h>

// C++ include

// to prevent annoying warnings on WIN32
#include <iplcompiler.h>

#include <osal/osal_dso.h>
#include <common/stdint.h>
#include <common/types/string.hxx>
#include <common/types/memory.hxx>

namespace oc
{

    class regexp;

    /** Regular Expression Evaluation.
     ** This documenation is based on the documenation found at
     ** http://codeguru.earthweb.com/string/regexp.shtml written
     ** by Guy Gascoigne - Piggford
     **
     ** For example:

     \code
     Regexp re( "^[\t ]*(.*)[\t ]*\\((.*)\\)" );
     ipl::string str( "wyrdrune.com!kelly (Kelly)\n" );
     ipl::string name, addr;

     if ( re.Match( str ) &amp;&amp; re.SubStrings() == 2 ) {
     name = re[2];
     addr = re[1];
     }
     \endcode

     ** Will give:

     \code
     name == "Kelly" and addr == "wyrdrune.com!kelly"
     \endcode



     <p><b>Regular Expression Syntax</b> </p>

     <p>A regular expression is zero or more branches, separated by '<strong>|</strong>'.
     It matches anything that matches one of the branches.</p>

     <p>A branch is zero or more pieces, concatenated. It matches a match for the first,
     followed by a match for the second, etc.</p>

     <p>A piece is an atom possibly followed by '<strong>*</strong>',
     '<strong>+</strong>', or '<strong>?</strong>'.
     An atom followed by '<strong>*</strong>' matches a sequence
     of 0 or more matches of the atom. An atom followed by '<strong>+</strong>'
     matches a sequence of 1 or more matches of the atom. An atom followed by
     '<strong>?</strong>' matches a match of the atom, or the null string.</p>

     <p>An atom is a regular expression in parentheses (matching a match for the regular
     expression), a range (see below), '<strong>.</strong>'
     (matching any single character), '<strong>^</strong>'
     (matching the null string at the beginning of the input string), '<strong>$</strong>'
     (matching the null string at the end of the input
     string), a '<strong>\\</strong>' followed by a single
     character (matching that character), or a single character with no other significance
     (matching that character).</p>

     <p>A range is a sequence of characters enclosed in '<strong>[]</strong>'.
     It normally matches any single character from the sequence. If the sequence begins with
     '<strong>^</strong>', it matches any single character not from the rest of
     the sequence. If two characters in the sequence are separated by '<strong>-</strong>',
     this is shorthand for the full list of ASCII
     characters between them (e.g. '<strong>[0-9]</strong>'
     matches any decimal digit). To include a literal '<strong>]</strong>'
     in the sequence, make it the first character (following a possible '<strong>^</strong>').
     To include a literal '<strong>-</strong>',
     make it the first or last character.</p>


     <p>Ambiguity</p>

     <p>If a regular expression could match two different parts of the input string, it will
     match the one which begins earliest. If both begin in the same place but match different
     lengths, or match the same length in different ways, life gets messier, as follows. </p>

     <p>In general, the possibilities in a list of branches are considered in left-to-right
     order, the possibilities for '<strong>*</strong>', '<strong>+</strong>', and '<strong>?</strong>'
     are considered longest-first, nested constructs are considered from the outermost in, and
     concatenated constructs are considered leftmost-first. The match that will be chosen is
     the one that uses the earliest possibility in the first choice that has to be made. If
     there is more than one choice, the next will be made in the same manner (earliest
     possibility) subject to the decision on the first choice. And so forth.</p>

     <p>For example, '<strong>(ab|a)b*c</strong>' could match '<strong>abc</strong>'
     in one of two ways. The first choice is between '<strong>ab</strong>' and '<strong>a</strong>';
     since '<strong>ab</strong>' is earlier, and does lead to a
     successful overall match, it is chosen. Since the '<strong>b</strong>'
     is already spoken for, the '<strong>b*</strong>' must match
     its last possibility--the empty string--since it must respect the earlier choice.</p>

     <p>In the particular case where the regular expression does not use `<strong>|</strong>' and
     does not apply `<strong>*</strong>',
     `<strong>+</strong>', or `<strong>?</strong>'
     to parenthesized subexpressions, the net effect is that the longest possible match will be
     chosen. So `<strong>ab*</strong>', presented with `<strong>xabbbby</strong>', will match
     `<strong>abbbb</strong>'.
     Note that if `<strong>ab*</strong>' is tried against `<strong>xabyabbbz</strong>', it will
     match `<strong>ab</strong>'
     just after `<strong>x</strong>', due to the begins-earliest
     rule. (In effect, the decision on where to start the match is the first choice to be made,
     hence subsequent choices must respect it even if this leads them to less-preferred
     alternatives.)</p>

     ** \see http://codeguru.earthweb.com/string/regexp.shtml
     **/
    template <
        typename CHAR_TYPE,
        typename CHAR_TRAITS = ipl::char_traits<CHAR_TYPE>,
        typename ALLOCATOR = ipl::allocator<CHAR_TYPE> >
    class OSAL_EXPORT RegexpBase
    {
    public:
        typedef typename CHAR_TRAITS::char_type* string_ptr;
        typedef typename CHAR_TRAITS::char_type const * const_string_ptr;
        typedef typename ipl::basic_string<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR> string_obj;
        typedef const typename ipl::basic_string<CHAR_TYPE, CHAR_TRAITS, ALLOCATOR> const_string_obj;

    private:
        const_string_ptr string; /* used to return substring offsets only */
        mutable string_obj m_szError;
        regexp * rc;

        void ClearErrorString() const;
        int safeIndex( unsigned int i ) const;
    public:

        /** A constant defining how many subexpressions Regexp supports (usually 10),
            attempting to use a regular expression with more than this number will generate an error.
        **/
        enum { NSUBEXP = 10 };
    public:

        /** A boring constructor, this must be initialized by assignment before anything useful can be done with it.
         **/
        RegexpBase();

        /** Create and Compile regular expression. The success or
         **  failure of the compilation can be discovered by using
         **  either GetErrorString() or CompiledOK()
         ** \param exp The regular expression itself.
         ** \param icase   If true the regular expression is compiled so that differences in case are ignored when matching.
         **/
        RegexpBase( const_string_ptr exp, bool icase = false );

        /** Construct a new regular expression taking the compiled form from another Regexp.
         **/
        RegexpBase( const RegexpBase &r );

        /** Dtor.
         **/
        ~RegexpBase();

        /** Assign Regexp r to the current object.
         **/
        const RegexpBase& operator=( const RegexpBase &r );

        /** Examine the char array s with this regular expression, returning true if
         ** there is a match. This match updates the state of this Regexp object so that the
         ** substrings of the match can be obtained. The 0th substring is the substring of string that
         ** matched the whole regular expression. The others are those substrings that matched
         ** parenthesized expressions within the regular expression, with parenthesized expressions
         ** numbered in left-to-right order of their opening parentheses. If a parenthesized
         ** expression does not participate in the match at all, its length is 0. It is an error if
         ** thisRegexp has not been successfully initialized.
         **/
        int_fast8_t Match( const_string_ptr s );

        /** Return the number of substrings found after a successful
         **/
        int GetSubStrings() const;


        /**
         **/
        string_obj operator[]( unsigned int i ) const;

        /** Return the starting offset of the i.th matched substring from the beginning of
         ** the char array used in Match().
         **/
        int GetSubStart( unsigned int i ) const;

        /** Return the length of the i.th matched substring.
         **/
        int GetSubLength( unsigned int i ) const;


        /** After a successful Match you can retrieve a replacement string as an alternative to
         ** building up the various substrings by hand.
         <p>Each character in the source string will be copied to the return value except for the
         following special characters:</p>
         <table border="0" width="690">
         <tr>
         <td width="88">&amp;&nbsp;&nbsp; </td>
         <td width="594">The complete matched string (sub-string 0).</td>
         </tr>
         <tr>
         <td width="88">\\1&nbsp; </td>
         <td width="594">Sub-string 1</td>
         </tr>
         <tr>
         <td width="88">...</td>
         <td width="594">and so on until...</td>
         </tr>
         <tr>
         <td width="88">\\9</td>
         <td width="594">Sub-string 9</td>
         </tr>
         </table>
        **/
        string_obj GetReplaceString( const_string_ptr source ) const;


        /** Return a description of the most recent error caused on this Regexp. Errors
         ** include, but are not limited to, various forms of compilation errors, usually syntax
         ** errors, and calling Match when the Regexp hasn&#146;t been initialized
         ** correctly (or at all). There are a fair number of these that should never occur if all of
         ** the Regexp use comes from your code, but where the user can type in regular
         ** expressions that you then have to compile, checking this can be very important.
         **/
        string_obj GetErrorString() const;

        /** Return the status of the last regular expression compilation.
         **/
        bool HasCompiledOK() const;


    }; // class Regexp

    typedef RegexpBase<char> Regexp;
    typedef RegexpBase<wchar_t> WideRegexp;

    #ifndef OSAL_EXPORT_CONTEXT
    extern template OSAL_EXPORT class RegexpBase<char>;
    //extern template OSAL_EXPORT class RegexBase<wchar_t>;
    #endif
} // namespace oc

#endif
