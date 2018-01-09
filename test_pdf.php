<?php
if(!extension_loaded('phpwkhtmltox')) {
	dl('phpwkhtmltox.' . PHP_SHLIB_SUFFIX);
}
$ret = wkhtmltox_convert('pdf',
        array('out' => '/tmp/test.pdf', 'imageQuality' => '100','pageSize'=>'A4','test'=>true), // global settings
        array(
            //array('page' => 'http://www.sina.com/','jsdelay'=>100),
            array('page' => 'http://www.baidu.com/')
            )); // object settings
var_dump($ret);
?>
