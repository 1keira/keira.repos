/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

#ifdef OSAL_USE_POSIXREGEX

namespace osal {

    inline size_t Regex::SubstringMatch::startOffset() const
    {
        return this->rm_so;
    }

    inline size_t Regex::SubstringMatch::endOffset() const
    {
        return this->rm_eo;
    }

    inline void Regex::clean()
    {
        if( this->isValid() )
        {
            ::regfree(&m_handle.regex);
            m_handle.valid = false;
        }
    }

    inline int_fast8_t Regex::match(const char *s) const
    {
        if( ! this->isValid() )
        {
            return m_handle.handleMatchError(0);
        }

        const int res = ::regexec(&m_handle.regex, s, 0, NULL, 0);

        if( ! res )
            return 0;

        if( res == REG_NOMATCH ) // BRANCH_COVERAGE_UNTESTABLE
            return 1;

        return m_handle.handleMatchError(res);
    }

    inline int_fast8_t Regex::match(const char *s,
        ipl::vector< SubstringMatch > &matches) const
    {
        if( ! this->isValid() || ! m_handle.submatches )
        {
            return m_handle.handleMatchError(0, true);
        }

        if( ! matches.empty() )
            matches[0].rm_so = -1;

        // this gives us the number of sub-expressions
        //
        // the expression itself counts as a sub-expression so we need
        // to add one
        matches.resize( m_handle.regex.re_nsub + 1 );

        const int res = ::regexec(
            &m_handle.regex,
            s,
            matches.size(),
            &matches[0], 0);

        if( ! res )
        {
            for( size_t i = 0; i < matches.size(); i++ )
            {
                if( matches[i].rm_so == -1 )
                {
                    // pass a not matching sub expression related result
                    // as a string having zero length
                    matches[i].rm_so = matches[i].rm_eo = 0u;
                }
            }

            return 0;
        }

        if( res == REG_NOMATCH ) // BRANCH_COVERAGE_UNTESTABLE
            return 1;

        return m_handle.handleMatchError(res);
    }

} // end ns osal

#else
#    include <osal/common/Regex.inl>
#endif // OSAL_USE_POSIXREGEX
