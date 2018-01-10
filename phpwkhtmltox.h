#ifndef PHP_PHPWKHTMLTOX_H
#define PHP_PHPWKHTMLTOX_H

#define PHP_PHPWKHTMLTOX_VERSION "0.10.1"
#define PHP_PHPWKHTMLTOX_EXTNAME "phpwkhtmltox"

#ifdef PHP_WIN32
#define PHP_PHPWKHTMLTOX_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#define PHP_PHPWKHTMLTOX_API __attribute__ ((visibility("default")))
#else
#define PHP_PHPWKHTMLTOX_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_BEGIN_MODULE_GLOBALS(phpwkhtmltox)
    int wkhtmltoimage_initialized;
    int wkhtmltopdf_initialized;
ZEND_END_MODULE_GLOBALS(phpwkhtmltox)

#define PHPWKHTMLTOX_G(v) ZEND_MODULE_GLOBALS_ACCESSOR(phpwkhtmltox,v)


PHP_FUNCTION (wkhtmltox_convert);

PHP_FUNCTION (wkhtmltox_pdf);

PHP_FUNCTION (wkhtmltox_image);

typedef int (*fp)(void *settings, const char *name, const char *value);

void wkhtmltox_set_params(void *settings, fp set_function, zval *params);

extern zend_module_entry phpwkhtmltox_module_entry;
#define phpext_phpwkhtmltox_ptr &phpwkhtmltox_module_entry

#if defined(ZTS) && defined(COMPILE_DL_PHPWKHTMLTOX)
ZEND_TSRMLS_CACHE_EXTERN()
#endif

#endif