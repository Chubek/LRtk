#if !defined(_Toolbox_fixwarn_h)
#define _Toolbox_fixwarn_h

// Macro included from "/usr/include/ctype.h".
// Replace old-style casts with C++ casts.
#undef __isctype
#define __isctype(c, type) \
    (__ctype_b[static_cast<int>(c)] & static_cast<unsigned short int>(type))

  #endif
