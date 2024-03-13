/*
    Copyright 2022 esolutions GmbH
    All rights reserved
*/

#ifndef UTIL_SERIALIZER_SERIALIZER_SCOPE_HXX_
#define UTIL_SERIALIZER_SERIALIZER_SCOPE_HXX_

#include <vector>

namespace util {
namespace serializer {

    /**
     * @brief Helper class for StructuredSerializer/PullDeserializer
     *
     * Serializers may have the need to remember some data when a new serializer
     * scope starts and restore the data when the scope ends.
     *
     * Scopes are surrounded by
     * - beginSerialize/endSerialize
     * - beginOption/endOption
     * - beginStruct/endStruct
     * - beginField/endField
     * - beginArray/endArray
     * - beginField/endField
     *
     * For details see IStructuredSerializer/IStructuredPullDeserializer
     *
     * Scopes can be nested. A structure can have fields of type structure or array.
     * The nesting level depends on the definition of the data to be serialized.
     *
     *
     * @tparam T   class/struct defining the data needed for a scope
     * @tparam N   initial number of preallocated scopes
     */
    template <class T, std::size_t N>
        class SerializerScope {
              typename std::vector<T>::iterator Iterator;
        public:
            /**
             * @brief Construct a new Serializer Scope object
             *
             */
            SerializerScope() {
                m_it = m_scopes.begin();
            }
            void reset() {
                m_it = m_scopes.begin();
            };

            /**
             * @brief openScope, request to open a new scope.
             *
             * @return T* a pointer to the data of the new scope
             *
             */
            T* openScope() {
                T* res;
                if (m_it == m_scopes.end()) {
                    // we are running out of m_scopes
                    m_scopes.emplace_back(T());
                    m_it = --m_scopes.end();
                }
                res = &*m_it;
                ++m_it;
                return res;
            }

            /**
             * @brief closeScope, close the most recent scope
             *
             * @return T* pointer to the data of the closed scope
             *         nullptr if no scope is open
             */
            T* closeScope() {
                if (m_it == m_scopes.begin()) {
                    return nullptr;
                }
                --m_it;
                return &*m_it;
            }

            /**
             * @brief check that no scope is open
             *
             * @return true if all scopes are closed, false otherwise
             */
            bool allClosed() {
                return m_it == m_scopes.begin();
            }
        private:
            typename std::vector<T>::iterator  m_it;
            std::vector<T>                     m_scopes{N};
        };
}
}

#endif //UTIL_SERIALIZER_SERIALIZER_SCOPE_HXX_

