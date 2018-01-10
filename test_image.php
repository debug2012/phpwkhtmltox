<?php
$t = microtime(true);
$ret = wkhtmltox_convert('image',
    ['out' => '/tmp/baidu.jpg', 'in' => 'http://www.baidu.com/','imageQuality'=>100]); // global settings

var_dump($ret);

echo "cost:".(microtime(true) - $t)."\n";