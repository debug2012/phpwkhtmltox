<?php
if(!extension_loaded('phpwkhtmltox')) {
	dl('phpwkhtmltox.' . PHP_SHLIB_SUFFIX);
}
$i = 0;
foreach (range(1, 4) as $i) {
    $ret = wkhtmltox_convert('pdf',
        array('out' => '/tmp/test'.$i.'.pdf', 'imageQuality' => '95'), // global settings
        array(
            array('page' => 'http://www.sina.com/'),
            array('page' => 'http://www.baidu.com/')
            )); // object settings
    var_dump($ret);
}

?>
