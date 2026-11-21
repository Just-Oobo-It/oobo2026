#ifndef QPRINT
#define QPRINT


// #define qlog(...)
// #define qdebug(...)
// #define qerror(...)
// #define qvald(...)
// #define qvalf(...)


// #ifndef __FUNCTION__
// #define __FUNCTION__ "function"
// #endif

#define QDOXX qprint("$cb%s$0 @ $cb%s$0 : ", __FILE__, __FUNCTION__);

#ifndef qlog
#define qlog(...) QDOXX qprint(__VA_ARGS__);
#endif
#ifndef qdebug
#define qdebug(...) qprint(__VA_ARGS__);
#endif
#ifndef qerror
#define qerror(...) qprint("$cr$bERROR$0$b "); QDOXX qprint(__VA_ARGS__);
#endif
#ifndef qvald
#define qvald(x) qprint("%s = %d\n", #x, x);
#endif
#ifndef qvalf
#define qvalf(x) qprint("%s = %f\n", #x, x);
#endif

void qprint(char* str, ...);

#endif
