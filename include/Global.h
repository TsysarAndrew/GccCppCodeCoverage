#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <string>

#define GETMETHOD(Type, MemberName, FaceName) \
    public:\
    Type Get##FaceName() const { \
        return MemberName; \
     };

#define SETMETHOD(Type, MemberName, FaceName) \
    public:\
    void Set##FaceName(Type value) { \
        MemberName = value; \
  }\
    private:\
        Type MemberName;\
    public:

#define GETSET(Type, MemberName, FaceName) \
  GETMETHOD(Type, MemberName, FaceName); \
  SETMETHOD(Type, MemberName, FaceName);



#endif // GLOBAL_H_INCLUDED
