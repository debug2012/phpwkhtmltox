<?php

$t = microtime(true);
$ret = wkhtmltox_pdf(['out' => '/tmp/baidu1.pdf', 'imageQuality' => '100','pageSize'=>'A4','test'=>true], // global settings
        [
            //['page' => 'http://www.sina.com/','jsdelay'=>100],
            ['page' => 'http://www.baidu.com/'],
        ]); // object settings
var_dump($ret);

echo "cost:".(microtime(true) - $t)."\n";