/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

namespace osal
{

#ifdef OSAL_USE_SPENCER

inline size_t Regex::SubstringMatch::startOffset() const
{
    return start_index;
}

inline size_t Regex::SubstringMatch::endOffset() const
{
    return start_index + length;
}

inline void Regex::clean()
{
    if( this->isValid() )
    {
        m_handle.regexp = oc::Regexp();
    }
}
    
inline int_fast8_t Regex::match(const char *s) const
{
    const int_fast8_t match_res = m_handle.regexp.Match(s);

    if( match_res < 0 )
    {
        ipl_raise( Regex::Error, MATCH_ERROR,
            m_handle.regexp.GetErrorString().c_str() );
    }

    return match_res;
}

inline int_fast8_t Regex::match(
    const char *s,
    ipl::vector< SubstringMatch >& matches) const
{
    matches.clear();

    const int_fast8_t match_res = m_handle.regexp.Match(s);

    if( match_res < 0 )
    {
        ipl_raise( Regex::Error, MATCH_ERROR,
            m_handle.regexp.GetErrorString().c_str() );
    }

    for( int substring = 0;
        substring < m_handle.regexp.GetSubStrings();
        substring++ )
    {
        matches.push_back( SubstringMatch() );
        matches.back().start_index = m_handle.regexp.GetSubStart(substring);
        matches.back().length = m_handle.regexp.GetSubLength(substring);
    }

    return match_res;
}

#endif // OSAL_USE_SPENCER

} // end ns osal
