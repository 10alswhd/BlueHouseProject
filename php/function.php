<?php
/*
 * This is a sample function that guarantees unique URLs for frontend assets.
 *  Images for example.
 *  Include this and your users will never re-download an asset they already 
 *    have just just because you push a new build.
 *  If including this in your stylesheet then you should set this up in you
 *    should be using something like Amazon Cloud Front to cache a static
 *    version of it.
 */
function getAssetImage($path)
{
  $md5 = sha1_file($path);
  preg_match('/\.([a-zA-Z]{3,4})$/', $path, $matches);
  $ext = $matches[1];
  $dest = "/img/static/{$md5}.{$ext}";
  if(!file_exists($dest))
    copy($path, $dest);
  return $dest;
}
?>
