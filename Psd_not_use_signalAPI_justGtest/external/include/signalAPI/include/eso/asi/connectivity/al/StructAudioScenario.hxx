/*
    Copyright 2020 e.solutions GmbH
    All rights reserved
    GENERATED FROM esofw_core_sdk code generator using template Struct_hxx.tmpl
*/
#ifndef ASI_CONNECTIVITY_AL_AUDIOSCENARIO_HXX
#define ASI_CONNECTIVITY_AL_AUDIOSCENARIO_HXX

#include <comm/commidltypes.hxx>
#include <comm/attributes/commattributes.hxx>

#undef unix

namespace asi
{
namespace connectivity
{
namespace al
{

    /**
    \brief struct al::AudioScenario.
    */
    struct PROXY_EXPORT AudioScenario
    {
        CIPtr< CIString > configFile; // optional=True
        int32_t micLevel; // optional=False
        int32_t speakerLevel; // optional=False
        bool echoSwitchOn; // optional=False
        private:
            AudioScenario()
            :
            configFile(),
            micLevel(),
            speakerLevel(),
            echoSwitchOn()
            { }
            friend class AudioScenarioFactory;
            friend class CIFactory<AudioScenario>;
#ifdef _MSC_VER  // these are only needed under VC++ and harmful elsewhere
            friend struct std::_Default_allocator_traits< std::allocator<asi::connectivity::al::AudioScenario> >;
            friend class ipl::vector<AudioScenario>;
            friend class ipl::allocator<AudioScenario>;
#endif
    };

    typedef CIPtrArray<AudioScenario> CIAudioScenarioArray;

    /** \brief factory for al::AudioScenario. */
    class PROXY_EXPORT AudioScenarioFactory  : CIFactory<AudioScenario> {
    public:
        static inline CIPtr<AudioScenario> createAudioScenario() {
            return CIFactory<AudioScenario>::createObject();
        }
        static inline void createAudioScenario(CIPtr<AudioScenario> & s) {
            CIFactory<AudioScenario>::createObject(s);
        }
        static inline CIPtr<CIAudioScenarioArray> createAudioScenarioArray(size_t size) {
            return CIFactory<AudioScenario>::createArray(size);
        }
        static inline void createAudioScenarioArray(CIPtr<CIAudioScenarioArray>& a, size_t size) {
            CIFactory<AudioScenario>::createArray(a, size);
        }
    };
}//namespace asi
}//namespace connectivity
}//namespace al


#endif// ASI_CONNECTIVITY_AL_AUDIOSCENARIO_HXX
