/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
*/

/*****************************************************************************/
#ifndef OSAL_USERINFO_HXX
#define OSAL_USERINFO_HXX
/*****************************************************************************/

#include <common/stdint.h>
#include <common/types/string.hxx>
#include <osal/osal_dso.h>

/*****************************************************************************/

namespace osal {

/*****************************************************************************/

    /*!
        \brief Representation of a user, specified by numeric id or string name
    */
    class OSAL_EXPORT User {

    public:
        typedef int64_t Id;
        typedef ipl::string Name;

        explicit User(Id id):
            m_id(id), m_name(BAD_NAME), m_id_known(true), m_name_known(false) {}
        explicit User(const Name &name):
            m_id(BAD_ID), m_name(name), m_id_known(false), m_name_known(true) {}

        //! \brief Retrieve numeric id
        //!
        //! If the object was created from a name, a system call is made once to
        //! resolve to the id. If there is no valid id for the name,
        //! BAD_ID is returned.
        //!
        //! On Windows mapping between name and id fails always.
        Id id() const {
            if(!m_id_known) {
                m_id=name2id(m_name);
                m_id_known=true;
            }
            return m_id;
        }
        operator Id () const { return id(); }

        //! \brief Retrieve string name
        //!
        //! If the object was created from an id, a system call is made once to
        //! resolve to the name. If there is no valid name for the id,
        //! BAD_NAME is returned.
        //!
        //! On Windows mapping between name and id fails always.
        Name name() const {
            if(!m_name_known) {
                m_name=id2name(m_id);
                m_name_known=true;
            }
            return m_name;
        }
        operator Name () const { return name(); }

        //! \brief Invalid id
        static const Id BAD_ID;
        //! \brief Invalid name
        static const Name BAD_NAME;

    protected:
        static Name id2name(Id id);
        static Id name2id(const Name &name);

        // mutable: these values need to be changed lazily,
        // in methods that should be const
        mutable Id m_id;
        mutable Name m_name;
        mutable bool m_id_known;
        mutable bool m_name_known;
    };

/*****************************************************************************/

    /*!
        \brief Representation of a user group, specified by numeric id or string name
    */
    class OSAL_EXPORT Group {

    public:
        typedef int64_t Id;
        typedef ipl::string Name;

        explicit Group(Id id):
            m_id(id), m_name(BAD_NAME), m_id_known(true), m_name_known(false) {}
        explicit Group(const Name &name):
            m_id(BAD_ID), m_name(name), m_id_known(false), m_name_known(true) {}

        //! \brief Retrieve numeric id
        //!
        //! If the object was created from a name, a system call is made once to
        //! resolve to the id. If there is no valid id for the name,
        //! BAD_ID is returned.
        //!
        //! On Windows mapping between name and id fails always.
        Id id() const {
            if(!m_id_known) {
                m_id=name2id(m_name);
                m_id_known=true;
            }
            return m_id;
        }
        operator Id () const { return id(); }

        //! \brief Retrieve string name
        //!
        //! If the object was created from an id, a system call is made once to
        //! resolve to the name. If there is no valid name for the id,
        //! BAD_NAME is returned.
        //!
        //! On Windows mapping between name and id fails always.
        Name name() const {
            if(!m_name_known) {
                m_name=id2name(m_id);
                m_name_known=true;
            }
            return m_name;
        }
        operator Name () const { return name(); }

        //! \brief Invalid id
        static const Id BAD_ID;
        //! \brief Invalid name
        static const Name BAD_NAME;

    protected:
        static Name id2name(Id id);
        static Id name2id(const Name &name);

        // mutable: these values need to be changed lazily,
        // in methods that should be const
        mutable Id m_id;
        mutable Name m_name;
        mutable bool m_id_known;
        mutable bool m_name_known;
    };

/*****************************************************************************/

}  // end of namespace osal

/*****************************************************************************/
#endif
