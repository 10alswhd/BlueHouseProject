$toList         = array('test1@test.ru', 'test2@test.ru');
$subject        = 'My subject';
$message        = 'My message';
$from           = 'test@test.ru';

$headers        =   'From: '. $from . "\r\n" .
                    'Content-type: text/html; charset=utf-8' . " \r\n" .
                    'Reply-To: '. $from . "\r\n" .
                    'X-Mailer: PHP/' . phpversion();

foreach ($toList as $key => $to) 
    mail($to, $subject, $message, $headers);
