// **********************************************************************
//
// Copyright (c) 2003-2013 ZeroC, Inc. All rights reserved.
//
// This copy of Ice is licensed to you under the terms described in the
// ICE_LICENSE file included in this distribution.
//
// **********************************************************************
//
// Ice version 3.5.1
//
// <auto-generated>
//
// Generated from file `base_query_interface.ice'
//
// Warning: do not edit this file.
//
// </auto-generated>
//

#include <base_query_interface.h>
#include <Ice/LocalException.h>
#include <Ice/ObjectFactory.h>
#include <Ice/BasicStream.h>
#include <Ice/Object.h>
#include <IceUtil/Iterator.h>

#ifndef ICE_IGNORE_VERSION
#   if ICE_INT_VERSION / 100 != 305
#       error Ice version mismatch!
#   endif
#   if ICE_INT_VERSION % 100 > 50
#       error Beta header file detected
#   endif
#   if ICE_INT_VERSION % 100 < 1
#       error Ice patch level mismatch!
#   endif
#endif

namespace
{

const ::std::string __kelp__QueryInterface__Foo_name = "Foo";

}
::IceProxy::Ice::Object* ::IceProxy::kelp::upCast(::IceProxy::kelp::QueryInterface* p) { return p; }

void
::IceProxy::kelp::__read(::IceInternal::BasicStream* __is, ::IceInternal::ProxyHandle< ::IceProxy::kelp::QueryInterface>& v)
{
    ::Ice::ObjectPrx proxy;
    __is->read(proxy);
    if(!proxy)
    {
        v = 0;
    }
    else
    {
        v = new ::IceProxy::kelp::QueryInterface;
        v->__copyFrom(proxy);
    }
}

::kelp::BinData
IceProxy::kelp::QueryInterface::Foo(const ::std::string& str, const ::Ice::Context* __ctx)
{
    ::IceInternal::InvocationObserver __observer(this, __kelp__QueryInterface__Foo_name, __ctx);
    int __cnt = 0;
    while(true)
    {
        ::IceInternal::Handle< ::IceDelegate::Ice::Object> __delBase;
        try
        {
            __checkTwowayOnly(__kelp__QueryInterface__Foo_name);
            __delBase = __getDelegate(false);
            ::IceDelegate::kelp::QueryInterface* __del = dynamic_cast< ::IceDelegate::kelp::QueryInterface*>(__delBase.get());
            return __del->Foo(str, __ctx, __observer);
        }
        catch(const ::IceInternal::LocalExceptionWrapper& __ex)
        {
            __handleExceptionWrapper(__delBase, __ex, __observer);
        }
        catch(const ::Ice::LocalException& __ex)
        {
            __handleException(__delBase, __ex, true, __cnt, __observer);
        }
    }
}

::Ice::AsyncResultPtr
IceProxy::kelp::QueryInterface::begin_Foo(const ::std::string& str, const ::Ice::Context* __ctx, const ::IceInternal::CallbackBasePtr& __del, const ::Ice::LocalObjectPtr& __cookie)
{
    __checkAsyncTwowayOnly(__kelp__QueryInterface__Foo_name);
    ::IceInternal::OutgoingAsyncPtr __result = new ::IceInternal::OutgoingAsync(this, __kelp__QueryInterface__Foo_name, __del, __cookie);
    try
    {
        __result->__prepare(__kelp__QueryInterface__Foo_name, ::Ice::Normal, __ctx);
        ::IceInternal::BasicStream* __os = __result->__startWriteParams(::Ice::DefaultFormat);
        __os->write(str);
        __result->__endWriteParams();
        __result->__send(true);
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __result->__exceptionAsync(__ex);
    }
    return __result;
}

::kelp::BinData
IceProxy::kelp::QueryInterface::end_Foo(const ::Ice::AsyncResultPtr& __result)
{
    ::Ice::AsyncResult::__check(__result, this, __kelp__QueryInterface__Foo_name);
    ::kelp::BinData __ret;
    bool __ok = __result->__wait();
    try
    {
        if(!__ok)
        {
            try
            {
                __result->__throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                throw ::Ice::UnknownUserException(__FILE__, __LINE__, __ex.ice_name());
            }
        }
        ::IceInternal::BasicStream* __is = __result->__startReadParams();
        __is->read(__ret);
        __result->__endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& ex)
    {
        __result->__getObserver().failed(ex.ice_name());
        throw;
    }
}

const ::std::string&
IceProxy::kelp::QueryInterface::ice_staticId()
{
    return ::kelp::QueryInterface::ice_staticId();
}

::IceInternal::Handle< ::IceDelegateM::Ice::Object>
IceProxy::kelp::QueryInterface::__createDelegateM()
{
    return ::IceInternal::Handle< ::IceDelegateM::Ice::Object>(new ::IceDelegateM::kelp::QueryInterface);
}

::IceInternal::Handle< ::IceDelegateD::Ice::Object>
IceProxy::kelp::QueryInterface::__createDelegateD()
{
    return ::IceInternal::Handle< ::IceDelegateD::Ice::Object>(new ::IceDelegateD::kelp::QueryInterface);
}

::IceProxy::Ice::Object*
IceProxy::kelp::QueryInterface::__newInstance() const
{
    return new QueryInterface;
}

::kelp::BinData
IceDelegateM::kelp::QueryInterface::Foo(const ::std::string& str, const ::Ice::Context* __context, ::IceInternal::InvocationObserver& __observer)
{
    ::IceInternal::Outgoing __og(__handler.get(), __kelp__QueryInterface__Foo_name, ::Ice::Normal, __context, __observer);
    try
    {
        ::IceInternal::BasicStream* __os = __og.startWriteParams(::Ice::DefaultFormat);
        __os->write(str);
        __og.endWriteParams();
    }
    catch(const ::Ice::LocalException& __ex)
    {
        __og.abort(__ex);
    }
    bool __ok = __og.invoke();
    ::kelp::BinData __ret;
    try
    {
        if(!__ok)
        {
            try
            {
                __og.throwUserException();
            }
            catch(const ::Ice::UserException& __ex)
            {
                ::Ice::UnknownUserException __uue(__FILE__, __LINE__, __ex.ice_name());
                throw __uue;
            }
        }
        ::IceInternal::BasicStream* __is = __og.startReadParams();
        __is->read(__ret);
        __og.endReadParams();
        return __ret;
    }
    catch(const ::Ice::LocalException& __ex)
    {
        throw ::IceInternal::LocalExceptionWrapper(__ex, false);
    }
}

::kelp::BinData
IceDelegateD::kelp::QueryInterface::Foo(const ::std::string& str, const ::Ice::Context* __context, ::IceInternal::InvocationObserver&)
{
    class _DirectI : public ::IceInternal::Direct
    {
    public:

        _DirectI(::kelp::BinData& __result, const ::std::string& __p_str, const ::Ice::Current& __current) : 
            ::IceInternal::Direct(__current),
            _result(__result),
            _m_str(__p_str)
        {
        }
        
        virtual ::Ice::DispatchStatus
        run(::Ice::Object* object)
        {
            ::kelp::QueryInterface* servant = dynamic_cast< ::kelp::QueryInterface*>(object);
            if(!servant)
            {
                throw ::Ice::OperationNotExistException(__FILE__, __LINE__, _current.id, _current.facet, _current.operation);
            }
            _result = servant->Foo(_m_str, _current);
            return ::Ice::DispatchOK;
        }
        
    private:
        
        ::kelp::BinData& _result;
        const ::std::string& _m_str;
    };
    
    ::Ice::Current __current;
    __initCurrent(__current, __kelp__QueryInterface__Foo_name, ::Ice::Normal, __context);
    ::kelp::BinData __result;
    try
    {
        _DirectI __direct(__result, str, __current);
        try
        {
            __direct.getServant()->__collocDispatch(__direct);
        }
        catch(...)
        {
            __direct.destroy();
            throw;
        }
        __direct.destroy();
    }
    catch(const ::Ice::SystemException&)
    {
        throw;
    }
    catch(const ::IceInternal::LocalExceptionWrapper&)
    {
        throw;
    }
    catch(const ::std::exception& __ex)
    {
        ::IceInternal::LocalExceptionWrapper::throwWrapper(__ex);
    }
    catch(...)
    {
        throw ::IceInternal::LocalExceptionWrapper(::Ice::UnknownException(__FILE__, __LINE__, "unknown c++ exception"), false);
    }
    return __result;
}

::Ice::Object* kelp::upCast(::kelp::QueryInterface* p) { return p; }

namespace
{
const ::std::string __kelp__QueryInterface_ids[2] =
{
    "::Ice::Object",
    "::kelp::QueryInterface"
};

}

bool
kelp::QueryInterface::ice_isA(const ::std::string& _s, const ::Ice::Current&) const
{
    return ::std::binary_search(__kelp__QueryInterface_ids, __kelp__QueryInterface_ids + 2, _s);
}

::std::vector< ::std::string>
kelp::QueryInterface::ice_ids(const ::Ice::Current&) const
{
    return ::std::vector< ::std::string>(&__kelp__QueryInterface_ids[0], &__kelp__QueryInterface_ids[2]);
}

const ::std::string&
kelp::QueryInterface::ice_id(const ::Ice::Current&) const
{
    return __kelp__QueryInterface_ids[1];
}

const ::std::string&
kelp::QueryInterface::ice_staticId()
{
    return __kelp__QueryInterface_ids[1];
}

::Ice::DispatchStatus
kelp::QueryInterface::___Foo(::IceInternal::Incoming& __inS, const ::Ice::Current& __current)
{
    __checkMode(::Ice::Normal, __current.mode);
    ::IceInternal::BasicStream* __is = __inS.startReadParams();
    ::std::string str;
    __is->read(str);
    __inS.endReadParams();
    ::kelp::BinData __ret = Foo(str, __current);
    ::IceInternal::BasicStream* __os = __inS.__startWriteParams(::Ice::DefaultFormat);
    __os->write(__ret);
    __inS.__endWriteParams(true);
    return ::Ice::DispatchOK;
}

namespace
{
const ::std::string __kelp__QueryInterface_all[] =
{
    "Foo",
    "ice_id",
    "ice_ids",
    "ice_isA",
    "ice_ping"
};

}

::Ice::DispatchStatus
kelp::QueryInterface::__dispatch(::IceInternal::Incoming& in, const ::Ice::Current& current)
{
    ::std::pair< const ::std::string*, const ::std::string*> r = ::std::equal_range(__kelp__QueryInterface_all, __kelp__QueryInterface_all + 5, current.operation);
    if(r.first == r.second)
    {
        throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
    }

    switch(r.first - __kelp__QueryInterface_all)
    {
        case 0:
        {
            return ___Foo(in, current);
        }
        case 1:
        {
            return ___ice_id(in, current);
        }
        case 2:
        {
            return ___ice_ids(in, current);
        }
        case 3:
        {
            return ___ice_isA(in, current);
        }
        case 4:
        {
            return ___ice_ping(in, current);
        }
    }

    assert(false);
    throw ::Ice::OperationNotExistException(__FILE__, __LINE__, current.id, current.facet, current.operation);
}

void
kelp::QueryInterface::__writeImpl(::IceInternal::BasicStream* __os) const
{
    __os->startWriteSlice(ice_staticId(), -1, true);
    __os->endWriteSlice();
}

void
kelp::QueryInterface::__readImpl(::IceInternal::BasicStream* __is)
{
    __is->startReadSlice();
    __is->endReadSlice();
}

void 
kelp::__patch(QueryInterfacePtr& handle, const ::Ice::ObjectPtr& v)
{
    handle = ::kelp::QueryInterfacePtr::dynamicCast(v);
    if(v && !handle)
    {
        IceInternal::Ex::throwUOE(::kelp::QueryInterface::ice_staticId(), v);
    }
}