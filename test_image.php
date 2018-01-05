<?php

$ret = wkhtmltox_convert('image',
    array('out' => '/tmp/test.jpg', 'in' => 'http://www.baidu.com/','imageQuality'=>100)); // global settings

var_dump($ret);
?>
