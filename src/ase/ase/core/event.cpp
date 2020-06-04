#include "asepch.hpp"
#include "ase/core/data.hpp"

namespace ase
{
    namespace DataManager
    {
    }

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
         m_dataref = XPLMRegisterDataAccessor(m_datapath.c_str(),
             xplmType_Int,                                  // The types we support
             1,                                             // Writable
             GetXpDataRef<int>, SetXpDataRef<int>,              // Integer accessors
             NULL, NULL,                                    // Float accessors
             NULL, NULL,                                    // Doubles accessors
             NULL, NULL,                                    // Int array accessors
             NULL, NULL,                                    // Float array accessors
             NULL, NULL,                                    // Raw data accessors
             &m_pData, &m_pData 
             );      
    }

    template<>
    void DataRef<int>::AccessXpDataRef()
    {
         //m_dataref
    }

}
