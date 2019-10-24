#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(COMMONFILTER_LIB)
#  define COMMONFILTER_EXPORT Q_DECL_EXPORT
# else
#  define COMMONFILTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define COMMONFILTER_EXPORT
#endif
