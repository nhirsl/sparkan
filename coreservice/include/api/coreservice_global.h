#include <QtGlobal>

#if defined CORESERVICE
 #define CORESERVICE_DLLSPEC Q_DECL_EXPORT
#else
 #define CORESERVICE_DLLSPEC Q_DECL_IMPORT
#endif

