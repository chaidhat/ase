#pragma once

#include "asepch.hpp"

#include "ase/core/event.hpp"

namespace ase
{
    enum DataReadMode
    {
        RM_NORMAL, // do get and set
        RM_GET_ONLY, // do not set the data
        RM_SET_ONLY, // do not get the data
        RM_INIT_ONLY, // get it only once on init
    };

    enum DataReadSpeed
    {
        RS_NORMAL, // every 0.01 second
        RS_LAZY, // every 0.1 second
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
        virtual void Stop() = 0;

        virtual void Update() = 0;
        virtual void LazyUpdate() = 0;
    };

    template <class T>
    class DataRef : public DataInterface
    {
    public:
        // TODO: try a copy assignment operators for simplicity.
        //
        DataRef(const std::string dataPath, T* pData, DataReadMode readMode, DataReadSpeed readSpeed) :
            m_dataPath(dataPath), m_pData(pData), m_readMode(readMode), m_readSpeed(readSpeed)
        {
        }

        ~DataRef()
        {
            Debug::Log("Data: Removing dataref " + m_dataPath);
            delete m_pData;
        }

        void Start()
        {
            Debug::Log("Data: Creating dataref " + m_dataPath);
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
        }

        void Stop()
        {
            // destruction is done in destructor
        }

        void Update()
        {
            if (m_readSpeed == RS_NORMAL)
                UpdateDataref();
        }

        void LazyUpdate()
        {
            if (m_readSpeed == RS_LAZY)
                UpdateDataref();
        }

        T& GetRef()
        {
            T& pData = *m_pData;
            return pData;
        }


        XPLMDataRef m_dataRef;
        DataReadMode m_readMode;
        DataReadSpeed m_readSpeed;
        const std::string m_dataPath;
    private:
        T* m_pData;
        T m_memData; // check for any changes in data
        bool m_fCanWrite;
        bool m_fIsRegistered;

        void UpdateDataref()
        {
            // registered dataRefs already have a refCon to set it
            if (m_fIsRegistered)
            {
                    // is the data changed by plugin?
                    if (m_memData != *m_pData)
                    {
                        if (m_readMode == RM_NORMAL || m_readMode == RM_SET_ONLY)
                        {
                            // can the data be written to?
                            if (m_fCanWrite)
                                SetXpDataRef();
                            else
                                throw WriteException("Data " + m_dataPath + " cannot be written to!");
                            m_memData = *m_pData;
                        }
                    }
                    else
                    {
                        if (m_readMode == RM_NORMAL || m_readMode == RM_GET_ONLY)
                            GetXpDataRef();
                    }
            }
        }

        bool CheckTypeXpDataRef(XPLMDataTypeID dataRefType);
        void RegisterXpDataRef();

        void GetXpDataRef();
        void SetXpDataRef();
    };

    namespace DataManager
    {
        static std::list<DataInterface*> m_data;

        template <typename T>
        T& RegisterDataRef(const std::string dataRef, const DataReadMode readMode, const DataReadSpeed readSpeed)
        {
            // check for duplicate registerations
            for (DataInterface* pData : m_data)
            {
                DataRef<int>* pDataRef = (DataRef<int>*)pData;
                if (pDataRef->m_dataPath == dataRef)
                    return pDataRef->GetRef(); // return existing duplicate registerations
            }
            // none found, creating new dataRef
            T* pDataLocation = new T;
            DataRef<T>* pDataRef = new DataRef<T>(dataRef, pDataLocation, readMode, readSpeed);
            m_data.push_back((DataInterface*)pDataRef);
            EventManager::RegisterEvent((EventInterface*)pDataRef);
            return pDataRef->GetRef();
        }

        template <typename T>
        T& RegisterDataRef(const std::string dataRef)
        {
            return RegisterDataRef<T>(dataRef, RM_NORMAL, RS_NORMAL);
        }

        template <typename T>
        T& RegisterDataRef(const std::string dataRef, const DataReadSpeed readSpeed)
        {
            return RegisterDataRef<T>(dataRef, RM_NORMAL, readSpeed);
        }

        template <typename T>
        T& RegisterDataRef(const std::string dataRef, const DataReadMode readMode)
        {
            return RegisterDataRef<T>(dataRef, readMode, RS_NORMAL);
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
