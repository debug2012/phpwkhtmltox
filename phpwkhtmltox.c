#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <string.h>

#include "php.h"
#include "phpwkhtmltox.h"
#include "wkhtmltox/pdf.h"
#include "wkhtmltox/image.h"

ZEND_DECLARE_MODULE_GLOBALS(phpwkhtmltox)

static zend_function_entry phpwkhtmltox_functions[] = {
        PHP_FE(wkhtmltox_convert, NULL)
        PHP_FE(wkhtmltox_pdf, NULL)
        PHP_FE(wkhtmltox_image, NULL)
        PHP_FE_END
};

static void php_phpwkhtmltox_init_globals(zend_phpwkhtmltox_globals *phpwkhtmltox_globals) {
    phpwkhtmltox_globals->wkhtmltoimage_initialized = 0;
    phpwkhtmltox_globals->wkhtmltopdf_initialized = 0;
}

PHP_MINIT_FUNCTION (phpwkhtmltox) {
    ZEND_INIT_MODULE_GLOBALS(phpwkhtmltox, php_phpwkhtmltox_init_globals, NULL);

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION (phpwkhtmltox) {
    if (PHPWKHTMLTOX_G(wkhtmltoimage_initialized)) {
        wkhtmltoimage_deinit();
    }

    if (PHPWKHTMLTOX_G(wkhtmltopdf_initialized)) {
        wkhtmltopdf_deinit();
    }

    return SUCCESS;
}

PHP_RINIT_FUNCTION (phpwkhtmltox) {
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION (phpwkhtmltox) {
    return SUCCESS;
}

PHP_MINFO_FUNCTION (phpwkhtmltox) {
    php_info_print_table_start();
    php_info_print_table_row(2, "phpwkhtmltox", "enabled");
    php_info_print_table_row(2, "version", wkhtmltopdf_version());
    php_info_print_table_end();
}

zend_module_entry phpwkhtmltox_module_entry = {
        STANDARD_MODULE_HEADER,
        PHP_PHPWKHTMLTOX_EXTNAME,
        phpwkhtmltox_functions,
        PHP_MINIT(phpwkhtmltox),
        PHP_MSHUTDOWN(phpwkhtmltox),
        PHP_RINIT(phpwkhtmltox),
        PHP_RSHUTDOWN(phpwkhtmltox),
        PHP_MINFO(phpwkhtmltox),
        PHP_PHPWKHTMLTOX_VERSION,
        STANDARD_MODULE_PROPERTIES
};

void _wkhtmltox_pdf(zval *global_params, zval *object_params, zval *return_value) {
    int ret;
    // temp variable for foreach
    zend_ulong long_key;
    zend_string *str_key = NULL;
    zval *attr_value;

    if (!PHPWKHTMLTOX_G(wkhtmltopdf_initialized)) {
        PHPWKHTMLTOX_G(wkhtmltopdf_initialized) = wkhtmltopdf_init(0);
    }

    wkhtmltopdf_global_settings *global_settings = wkhtmltopdf_create_global_settings();
    wkhtmltox_set_params((void *) global_settings, (fp) wkhtmltopdf_set_global_setting, global_params);
    wkhtmltopdf_converter *c = wkhtmltopdf_create_converter(global_settings);

    ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(object_params), long_key, str_key, attr_value)
            {
                if (Z_TYPE_P(attr_value) == IS_ARRAY) {
                    wkhtmltopdf_object_settings *object_settings = wkhtmltopdf_create_object_settings();
                    wkhtmltox_set_params((void *) object_settings, (fp) wkhtmltopdf_set_object_setting,
                                         attr_value);
                    wkhtmltopdf_add_object(c, object_settings, NULL);
                }
            }ZEND_HASH_FOREACH_END();


    ret = wkhtmltopdf_convert(c);
    wkhtmltopdf_destroy_converter(c);
    RETURN_BOOL(ret)
}

void _wkhtmltox_image(zval *global_params, zval *return_value) {
    int ret;
    if (!PHPWKHTMLTOX_G(wkhtmltoimage_initialized)) {
        PHPWKHTMLTOX_G(wkhtmltoimage_initialized) = wkhtmltoimage_init(0);
    }

    wkhtmltoimage_global_settings *global_settings = wkhtmltoimage_create_global_settings();

    wkhtmltox_set_params((void *) global_settings, (fp) wkhtmltoimage_set_global_setting, global_params);

    wkhtmltoimage_converter *c = wkhtmltoimage_create_converter(global_settings, NULL);
    ret = wkhtmltoimage_convert(c);
    wkhtmltoimage_destroy_converter(c);

    RETURN_BOOL(ret)
}

PHP_FUNCTION (wkhtmltox_pdf) {
    zval *global_params;
    zval *object_params;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a|a", &global_params, &object_params) == FAILURE) {
        RETURN_NULL()
    }

    _wkhtmltox_pdf(global_params, object_params, return_value);

}

PHP_FUNCTION (wkhtmltox_image) {
    zval *global_params;

    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "a", &global_params) == FAILURE) {
        RETURN_NULL()
    }

    _wkhtmltox_image(global_params, return_value);
}

/**
 * bool wkhtmltox_convert(format, array global_settings, 2d array settings)
 */
PHP_FUNCTION (wkhtmltox_convert) {
    // receives the format parameter
    char *format;
    size_t format_len;

    // receives the global and object parameters
    zval *global_params;
    zval *object_params;

    // parse out parameters passed
    if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sa|a",
                              &format, &format_len, &global_params, &object_params) == FAILURE) {
        RETURN_NULL();
    }

    if (strcmp(format, "image") == 0) {
        _wkhtmltox_image(global_params, return_value);
    } else if (strcmp(format, "pdf") == 0) {
        _wkhtmltox_pdf(global_params, object_params, return_value);
    } else {
        RETURN_FALSE
    }
}

void wkhtmltox_set_params(void *settings, fp set_function, zval *params) {
    zend_ulong long_key;
    zend_string *str_key = NULL;
    zval *attr_value;

    ZEND_HASH_FOREACH_KEY_VAL(Z_ARRVAL_P(params), long_key, str_key, attr_value)
            {
                switch (Z_TYPE_P(attr_value)) {
                    case IS_TRUE:
                        set_function(settings, ZSTR_VAL(str_key), "true");
                        break;
                    case IS_FALSE:
                        set_function(settings, ZSTR_VAL(str_key), "false");
                    case IS_STRING:
                        set_function(settings, ZSTR_VAL(str_key), Z_STRVAL_P(attr_value));
                        break;
                    default:
                        convert_to_string(attr_value)
                        set_function(settings, ZSTR_VAL(str_key), Z_STRVAL_P(attr_value));
                        break;
                }
            }ZEND_HASH_FOREACH_END();
}

#ifdef COMPILE_DL_PHPWKHTMLTOX
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(phpwkhtmltox)
#endif