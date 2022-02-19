#pragma once

#include "dbj-dll.h"

#pragma region infrastructure

struct dbj_component_version_
{
    unsigned major;
    unsigned minor;
    unsigned patch;
    char description[0xFF];
};

typedef struct dbj_component_version_ (*DBJ_COMPONENT_SEMVER_FP)(void);
/* 
unloading is also exactly the same for every DBJ Component aka DLL
because each one of them implements this function
But then, should we bother and unload manually at all? Or just leave it to the OS.
*/
typedef bool (*DBJ_COMPONENT_UNLOAD_FP)(void);

/*
return dll handle
one is hoping OS is caching the dll in memory for the next call
returns null on error
*/
static inline HINSTANCE dbj_dll_load(
    /* 
    we search in the application folder or in the system32
    just a file name, not a path! 
    we deliberately do not allow paths for reason of security
    */
    const char dll_file_name_[static 1])
{
    HINSTANCE dll_handle_ = LoadLibraryExA(
        dll_file_name_,
        NULL,
        /* we limit the locations of dll#s we load deliberately! */
        LOAD_LIBRARY_SEARCH_APPLICATION_DIR | LOAD_LIBRARY_SEARCH_SYSTEM32);

    if (NULL == dll_handle_)
    {
        DBJ_DBG_PRINT("DLL Loader error: [%d]. "
                  "NOTE! By design looking only in system folders and application folder."
                  " Could not find the DLL by name: %s",
                  GetLastError(), dll_file_name_);
    }
    // no exitm thus client has ti check the result 
    return dll_handle_;
}

/*
one is hoping OS is caching the dll + function, in memory for the next call;
on error return null
*/
static inline void *dbj_dll_get_factory_function(HINSTANCE *dll_handle_)
{
    // Funny fact: GetProcAddress has no unicode equivalent
    FARPROC result =
        GetProcAddress((HINSTANCE)*dll_handle_, DBJCS_INTEFACE_FACTORY_STR);
    if (result == 0)
    {
      DBJ_DBG_PRINT("\nFailed to find the address for a function: '%s'\n",
                    DBJCS_INTEFACE_FACTORY_STR);
    }
    return result;
}

// there are only 3 functions def-ined for each and any dbj dll component
// so this is not going to be used very often, and probably never by users
static inline void *dbj_dll_get_any_function(HINSTANCE *dll_handle_, const char fname_[static 1]) {
  // Funny fact: GetProcAddress has no unicode equivalent
  FARPROC result = GetProcAddress((HINSTANCE)*dll_handle_, fname_);
  if (result == 0) {
    DBJ_DBG_PRINT("\nFailed to find the address for a function: '%s'\n",
                  fname_);
  }
  return result;
}

// this is just for debug builds
// returns EINVAL on erro, 0 on OK
static inline int dbj_dll_version_report(HINSTANCE dll_handle_, const char dll_name[static 1])
{
    // using the version info is exactly the same for every DBJ Component
    DBJ_COMPONENT_SEMVER_FP get_version =
        (DBJ_COMPONENT_SEMVER_FP)dbj_dll_get_any_function(
            &dll_handle_, DBJCS_COMPONENT_VERSION_STR);

    if (!get_version)
    {
     // error is already reported (in debug builds), so just leave
        return EINVAL;
    }
    struct dbj_component_version_ info_ = get_version();
    DBJ_DBG_PRINT("\n %s version info", dll_name);
    DBJ_DBG_PRINT("\nMajor: %d, minor: %d, patch: %d", info_.major, info_.minor, info_.patch);
    DBJ_DBG_PRINT("\nDescription: %s", info_.description);
    return 0;
}

// returns EXIT_FAILURE on error
// returns EXIT_SUCCESS on OK
static inline int dbj_dll_unload_dll(HINSTANCE dll_handle_, const char dll_name[static 1])
{
    // unloading is also exactly the same for every DBJ Component
    DBJ_COMPONENT_UNLOAD_FP can_unload =
        (DBJ_COMPONENT_UNLOAD_FP)
        dbj_dll_get_any_function(&dll_handle_, DBJCS_CAN_UNLOAD_NOW_STR);
    if (!can_unload)
    {
      // error is already reported, just return with failure
        return EXIT_FAILURE;
    }

    if (can_unload())
        if (!FreeLibrary(dll_handle_))
        {
            DBJ_DBG_PRINT("\ndbjdll_load FreeLibrary failed. The DLL name is: %s\n", dll_name);
            return EXIT_FAILURE;
        }
    return EXIT_SUCCESS;
}

#if 0

/*

DBJ DLL factory function returns a pointer to the inteface implementations
It differs between concrete dbj DLL's because it returns a pointer to the struct
that represents the concrete component interface.

obtain the pointer to the interface factory, example:

  DBJ_DLL_IFP( particular_client_ifp, interface_var_name, handle_to_dbj_dll );

*/
#define DBJ_DLL_IFP(FP_, N_, DLLHANDLE_) \
  FP_ N_ = (FP_)dbj_dll_get_factory_function(&DLLHANDLE_, DBJCS_INTEFACE_FACTORY_STR)

/*
 
 So how do we obtain the type of a method on DBJ DLL interface?  (if we need one)

 __typeof__ is 20+ years old, GCC extension not in the ISO C standard; yet

 to obtain and hold, a functon pointer to a method on some DBJ DLL interface we use
  20+ years old GCC extension not in the ISO C standard; yet

  Example: we have the interface pointer (from above) but we want a type of some method
  lets assume 

  struct some_dbj_dll_interface {
  const char *(*itoa)(int);
  } ;

  DBJ_DLL_IFP( factory_fp, factory_, dll_handle ); 

  struct some_dbj_dll_interface * interface_  =  factory_();
  
  DBJ_TYPE_OF(interface_->itoa) itoa_func = interface_->itoa;

  After that we just use itoa_func()
*/
#define DBJ_TYPE_OF(IFACE_PTR_METHOD_NAME) \
    __typeof__(IFACE_PTR_METHOD_NAME)

#endif // 0

#pragma endregion // infrastructure
