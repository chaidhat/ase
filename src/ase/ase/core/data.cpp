#include "asepch.hpp"
#include "ase/core/data.hpp"

namespace ase
{
    template<>
    bool DataRef<int>::CheckTypeXpDataRef(XPLMDataTypeID dataRefType)
    {
        if (dataRefType != xplmType_Int)
            return false;
        return true;
    }

    template<>
    void DataRef<int>::RegisterXpDataRef()
    {
         m_dataRef = XPLMRegisterDataAccessor(m_dataPath.c_str(),
             xplmType_Int,                                  // The types we support
             1,                                             // Writable
             GetXpDataRefRefCon<int>, SetXpDataRefRefCon<int>,              // Integer accessors
             NULL, NULL,                                    // Float accessors
             NULL, NULL,                                    // Doubles accessors
             NULL, NULL,                                    // Int array accessors
             NULL, NULL,                                    // Float array accessors
             NULL, NULL,                                    // Raw data accessors
             &m_pData, &m_pData                             // RefCons
             );      
    }

    template<>
    void DataRef<int>::GetXpDataRef()
    {
        *m_pData = XPLMGetDatai(m_dataRef);
        m_memData = *m_pData;
    }

    template<>
    void DataRef<int>::SetXpDataRef()
    {
        XPLMSetDatai(m_dataRef, *m_pData);
    }

}
