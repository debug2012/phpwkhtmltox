<?php

$desc = [
    0 => ['pipe','r'],
    1 => ['pipe','w'],
    2 => ['file', '/tmp/error.log','a']
];

$cwd = '/tmp/';

$env = [];
$t = microtime(true);
$process = proc_open("wkhtmltopdf http://www.baidu.com baidu.pdf",$desc,$pipes);
print_r(stream_get_contents($pipes[1]));
echo "cost:".(microtime(true) - $t)."\n";