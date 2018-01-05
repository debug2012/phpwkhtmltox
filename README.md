# phpwkhtmltox
PHP extension of libwkhtmltox base on a awesome [wkhtmltox](wkhtmltopdf.org) project

- PHP wrapper of libwkhtmltox
- Thanks to mreiferson, this project fork from his [php-wkhtmltox](https://github.com/mreiferson/php-wkhtmltox), although it didn't maintain any more

Follow this link `https://wkhtmltopdf.org/libwkhtmltox/pagesettings.html` to see more parameters, or you can use wkhtmltopdf/wkhtmltoimage -h to get some useful tips

# Requirements

- Download the lastest stable version wkhtmltox from http://wkhtmltopdf.org
- Copy libwkhtmltox.* to somewhere in your LD path(/usr/local/lib)
- Copy src/include/wkhtmltox to somewhere on your include path(/usr/local/include)

# Installation

```
phpize
./configure
make && make install
```

edit your php.ini

```
extension=phpwkhtmltox.so
```

