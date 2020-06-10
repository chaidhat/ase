#pragma once

#include "asepch.hpp"

#include "ase/core/event.hpp"

namespace ase
{
    enum DataModeRead
    {
        READ_ONLY, // do not get the data
        READ_LAZY, // every 1 second
        READ_NORMAL, // every 0.01 second
    };

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

    class TypeException : public DataException
    {
    public:
        TypeException(const std::string& msg):
            DataException(msg)
        {}
    };

    class WriteException : public DataException
    {
    public:
        WriteException(const std::string& msg):
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
        DataRef(const std::string dataPath, T* pData) :
            m_dataPath(dataPath), m_pData(pData)
        {
        }

        ~DataRef()
        {
            delete m_pData;
        }

        void Start()
        {
            m_dataRef = XPLMFindDataRef(m_dataPath.c_str());

            // check existence of dataref
            m_fIsRegistered = true;
            if (m_dataRef == NULL)
                m_fIsRegistered = false;

            if (m_fIsRegistered)
            {
                // link existing dataRef
                
                // check type of dataRef
                XPLMDataTypeID dataRefType = XPLMGetDataRefTypes(m_dataRef); 
                if (!CheckTypeXpDataRef(dataRefType))
                    throw TypeException("Data " + m_dataPath + " has the wrong type!");

                // check write capabilities of dataref
                m_fCanWrite = XPLMCanWriteDataRef(m_dataRef);

                // init to value
                GetXpDataRef();
            }
            else
            {
                // register new dataRef
                RegisterXpDataRef();

                // init to 0
                *m_pData = 0;
                m_memData = 0;
            }
            ase::Debug::Log("Created dataref " + m_dataPath);
        }

        void Update()
        {
            ase::Debug::Log("Updating " + m_dataPath);
            // registered dataRefs already have a refCon to set it
            if (m_fIsRegistered)
            {
                // is the data changed by plugin?
                if (m_memData != *m_pData)
                {
                    // can the data be written to?
                    if (m_fCanWrite)
                        SetXpDataRef();
                    else
                        throw WriteException("Data " + m_dataPath + " cannot be written to!");
                    m_memData = *m_pData;
                }
                else
                    GetXpDataRef();
            }
        }

        T& GetRef()
        {
            T& pData = *m_pData;
            return pData;
        }


        XPLMDataRef m_dataRef;
        DataModeRead dmr;
        const std::string m_dataPath;
    private:
        T* m_pData;
        T m_memData; // check for any changes in data
        bool m_fCanWrite;
        bool m_fIsRegistered;
        bool CheckTypeXpDataRef(XPLMDataTypeID dataRefType);
        void RegisterXpDataRef();

        void GetXpDataRef();
        void SetXpDataRef();
    };

    namespace DataManager
    {
        static std::list<DataInterface*> m_data;

        template <typename T>
        T& RegisterDataRef(const std::string dataRef, const DataModeRead dmr = READ_NORMAL)
        {
            ase::Debug::Log("Registering dataref " + dataRef);
            // check for duplicate registers
            for (DataInterface* pData : m_data)
            {
                DataRef<int>* pDataRef = (DataRef<int>*)pData;
                if (pDataRef->m_datapath == dataRef)
                    return pDataRef->GetData();
            }
            // none found, creating new dataRef
            T* pDataLocation = new T;
            DataRef<T>* pDataRef = new DataRef<T>(dataRef, pDataLocation);
            //m_data.push_back((DataInterface*)pDataRef);
            EventManager::RegisterEvent((EventInterface*)pDataRef);

            return pDataRef->GetRef();
        }

        template <typename T>
        void DeregisterDataRef(const T&& pInpDataRef)
        {
            // TODO: consider using std::iterator()
            for (DataInterface* pData : m_data)
            {
                DataRef<int>* pDataRef = (DataRef<int>*)pData;
                // is the memory location of the output reference equal to the input memory location of the reference?
                if (&pDataRef->GetRef() == pInpDataRef)
                {
                    free(pDataRef); // implicitly calls destructor of ase::DataRef
                    m_data.remove(pData);
                    EventManager::DeregisterEvent((EventInterface*)pData);
                }
            }
        }
    }

    template<typename T>
    T GetXpDataRefRefCon(void* pInRefcon)
    {
        T* pOutInt = (T*)pInRefcon;
        return *pOutInt;
    }

    template<typename T>
    void SetXpDataRefRefCon(void* pInRefcon, T pInValue)
    {
        T* pData = (T*) pInRefcon;
        *pData = pInValue;
    }
}
