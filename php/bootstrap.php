<?php
define( 'DOC_ROOT', realpath(dirname(__FILE__) . '/../') );
define( 'URL_ROOT', substr(DOC_ROOT, strlen(realpath($_SERVER['DOCUMENT_ROOT']))) . '/' );
define( 'ENV', isset($_SERVER['ENV']) ? $_SERVER['ENV'] : 'dev' );
error_reporting( E_STRICT | E_ALL );
fCore::enableErrorHandling( 'html' );
fCore::enableExceptionHandling( 'html' );
fTimestamp::setDefaultTimezone( 'Europe/London' );
// This prevents cross-site session transfer
fSession::setPath( DOC_ROOT . '/storage/session/' );
/**
 * Automatically includes classes
 *
 * @throws Exception
 *
 * @param  string $class  Name of the class to load
 * @return void
 */
function __autoload( $class ){
    $dirs = glob( DOC_ROOT . '/vendor/flourish/*', GLOB_ONLYDIR );
    foreach( $dirs as $dir ){
        $file = "$dir/$class.php";
        if( file_exists($file) ){
            return require $file;
        }
    }
    throw new Exception( "The class $class could not be loaded" );
}
class Config {
    public static function get( $file ){
        $f = new fFile( DOC_ROOT . "/inc/$file" );
        return json_decode( $f->read() );
    }
}
// $config = Config::get( 'config.json' );
// function url( $path ){
//     return URL_ROOT . ( ENV == 'dev' ? 'app/' : NULL ) . $path;
// }
function url( $path ){
    return URL_ROOT . $path;
}
