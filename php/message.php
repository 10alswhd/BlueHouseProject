<?php
define('HTTP_BAD_REQUEST', 400);
define('HTTP_NOT_FOUND',   404);
class Message
{
    static public $ja = array(
        HTTP_NOT_FOUND   => 'ページが見つかりません。',
        HTTP_BAD_REQUEST => '不正なリクエストです。'
    );  
    static public function __callStatic($property, $argments)
    {   
        return self::${self::locale()}[constant($property)];
    }   
    private function locale()
    {   
        return 'ja';
    }   
}
echo Message::HTTP_NOT_FOUND();
echo PHP_EOL;
echo Message::HTTP_BAD_REQUEST();
echo PHP_EOL;
