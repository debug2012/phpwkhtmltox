# phpwkhtmltox
PHP extension of libwkhtmltox base on a awesome [wkhtmltox](http://wkhtmltopdf.org) project

- PHP wrapper of libwkhtmltox
- Thanks to mreiferson, this project fork from his [php-wkhtmltox](https://github.com/mreiferson/php-wkhtmltox), although it didn't maintain any more

Follow this link `https://wkhtmltopdf.org/libwkhtmltox/pagesettings.html` to see more parameters, or you can use wkhtmltopdf/wkhtmltoimage -h to get some useful tips

# Requirements
- php7.x
- Download the lastest stable version wkhtmltox from http://wkhtmltopdf.org
- Copy libwkhtmltox.* to somewhere in your LD path(/usr/local/lib)
- Copy src/include/wkhtmltox to somewhere in your include path(/usr/local/include)

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

# Usage
```
$ret = wkhtmltox_convert('pdf',
        ['out' => '/tmp/baidu.pdf', 'imageQuality' => '100','pageSize'=>'A4','test'=>true], // global settings
        [
            //['page' => 'http://www.sina.com/','jsdelay'=>100],
            ['page' => 'http://www.baidu.com/'],
        ]); // object settings
var_dump($ret);
```
```
$ret = wkhtmltox_pdf(['out' => '/tmp/baidu1.pdf', 'imageQuality' => '100','pageSize'=>'A4','test'=>true], // global settings
        [
            //['page' => 'http://www.sina.com/','jsdelay'=>100],
            ['page' => 'http://www.baidu.com/'],
        ]); // object settings
var_dump($ret);
```
```
$t = microtime(true);
$ret = wkhtmltox_convert('image',
    ['out' => '/tmp/baidu.jpg', 'in' => 'http://www.baidu.com/','imageQuality'=>100]); // global settings

var_dump($ret);
```
see test_pdf.php test_image.php
