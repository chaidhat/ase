#pragma once

#include <asepch.hpp>
#include "core/event.hpp"

namespace ase
{

    class DataException : public std::runtime_error 
    {
    public:
        DataException(const std::string& msg):
            runtime_error(msg)
        {}
    };

    class DuplicateException : public DataException
    {
    public:
        DuplicateException(const std::string& msg):
            DataException(msg)
        {}
    };

    class NotFoundException : public DataException
    {
    public:
        NotFoundException(const std::string& msg):
            DataException(msg)
        {}
    };

    class TypeException : public DataException
    {
    public:
        TypeException(const std::string& msg):
            DataException(msg)
        {}
    };

    // pure abstract class - aka interface
    class DataInterface : public EventInterface
    {
    public:
        virtual void Start() = 0;
        virtual void Update() = 0;
    };

    template <class T>
    class DataRef : public DataInterface
    {
    public:
        // TODO: try a bit of copy assignment operators for simplicity.
        //
        DataRef(const std::string dataRef, T* pData) :
            m_datapath(dataRef), m_pData(pData)
        {
        }

        ~DataRef()
        {
            delete m_pData;
        }

        void Start()
        {
            bool fIsRegistered = true;
            m_dataref = XPLMFindDataRef(m_datapath.c_str());

            // check existence of dataref
            if (m_dataref == NULL)
                fIsRegistered = false;

            // check type of dataref
            XPLMDataTypeID datarefType = XPLMGetDataRefTypes(m_dataref); 
            if (!CheckTypeXpDataRef(datarefType))
                throw TypeException("Data " + m_datapath + " has the wrong type!");

            // check write capabilities of dataref
            m_fCanWrite = XPLMCanWriteDataRef(m_dataref);

            if (fIsRegistered)
            {
                // access exisitng dataRef
            }
            else
            {
                // register new dataRef
                RegisterXpDataRef();
            }
        }

        void Update()
        {
        }
        
        T& GetData()
        {
            T& pData = *m_pData;
            return pData;
        }


        XPLMDataRef m_dataref;
        const std::string m_datapath;
    private:
        T* m_pData;
        T m_memData; // check for any changes in data
        bool m_fCanWrite;
        bool CheckTypeXpDataRef(XPLMDataTypeID dataRefType);
        void RegisterXpDataRef();
        void AccessXpDataRef();
    };

    namespace DataManager
    {
        static std::list<DataInterface*> m_data;

        template <typename T>
        T& RegisterDataRef(const std::string dataRef)
        {
            // check for duplicate registers
            for (DataInterface* pData : m_data)
            {
                DataRef<int>* pDataRef = (DataRef<int>*)pData;
                if (pDataRef->m_datapath == dataRef)
                    return pDataRef->GetData();
            }
            
            // none found, creating new dataRef
            T* pDataLocation = new T;
            DataRef<T>* pDataRef = new DataRef<T>("777/path/dataRef", pDataLocation);
            m_data.push_back((DataInterface*)pDataRef);

            return pDataRef->GetData();
        }

        template <typename T>
        void DeregisterDataRef(const T&& pInpDataRef)
        {
            for (DataInterface* pData : m_data)
            {
                DataRef<int>* pDataRef = (DataRef<int>*)pData;
                // is the memory location of the output reference equal to the input memory location of the reference?
                if (&pDataRef->GetData() == pInpDataRef)
                    free(pDataRef); // implicitly calls destructor of ase::DataRef
            }
        }
        void DeregisterDataRef(const std::string dataRef);

    }

    template<typename T>
    T GetXpDataRef(void* pInRefcon)
    {
        T* pOutInt = (T*)pInRefcon;
        return *pOutInt;
    }

    template<typename T>
    void SetXpDataRef(void* pInRefcon, T pInValue)
    {
        T* pData = (T*) pInRefcon;
        *pData = pInValue;
    }

}
