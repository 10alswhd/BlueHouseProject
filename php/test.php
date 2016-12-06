<?php
define('DARYO_ANDROID_REG_IDS', 'daryo_android_reg_ids');
define('DARYO_PUSH_API_KEY', 'daryo-push-key');
define('PLUGIN_PATH', dirname(__FILE__) . '/');
define('DARYO_PUSH_BULK_SIZE', 300);
define('DARYO_PUSH_SLEEP_TIME', 5);
if (count($argv) < 2) {
    exit();
}
set_time_limit(0);
ini_set('max_execution_time', 0);
// ini_set('display_errors', 'on');
// error_reporting(E_ALL);
date_default_timezone_set('Asia/Tashkent');
function find_wordpress_base_path() {
    $dir = dirname(__FILE__);
    do {
        if (file_exists($dir . "/wp-config.php")) {
            return $dir;
        }
    } while ($dir = realpath("{$dir}/.."));
    return null;
}
define('BASE_PATH', find_wordpress_base_path() . '/');
define('WP_USE_THEMES', false);
global $wp, $wpdb, $wp_query, $wp_the_query, $wp_rewrite, $wp_did_header;
ob_start();
require(BASE_PATH . 'wp-load.php');
ob_end_clean();
require_once(PLUGIN_PATH . 'ApnsPHP/Autoload.php');
$post_id = (int)$argv[1];
daryo_send_push_notification($post_id);
function daryo_send_push_notification($post_id) {
    global $wpdb;
    $folder_name = dirname(__FILE__) . '/logs/' . date('Y/m/d/');
    mkdir($folder_name, 0777, true);
    $api_key = get_option(DARYO_PUSH_API_KEY);
    $post = get_post($post_id);
    setup_postdata($post);
    $post_data = daryo_get_post_data_for_push($post);
    $data = array(
        'post' => $post_data,
    );
    $headers = array(
        'Authorization: key=' . $api_key,
        'Content-Type: application/json',
    );
    $table_name = $wpdb->prefix . DARYO_ANDROID_REG_IDS;
    $push_stats = array(
        'devices_count' => 0,
        'devices_success_count' => 0,
        'android_count' => 0,
        'android_success_count' => 0,
        'ios_count' => 0,
        'ios_success_count' => 0,
    );
    $offset = 0;
    while ($registration_ids = $wpdb->get_col("SELECT DISTINCT(`reg_id`) FROM {$table_name} WHERE `os_type`=0 LIMIT {$offset}, ".DARYO_PUSH_BULK_SIZE.";")) {
        $push_stats['devices_count'] += count($registration_ids);
        $push_stats['android_count'] += count($registration_ids);
        $fields = array(
            'registration_ids' => $registration_ids,
            'time_to_live' => 172800,
            'data' => $data,
        );
        $result = daryo_send_gcm($headers, $fields);
        $push_result_data = json_decode($result);
        foreach($push_result_data->results as $key => $res){
            if(in_array($res->error, array(
                'MissingRegistration',
                'InvalidRegistration',
                'NotRegistered'
            ))){
                $wpdb->delete($table_name, array('reg_id' => $registration_ids[$key]));
            }
        }
        $push_stats['devices_success_count'] += $push_result_data->success;
        $push_stats['android_success_count'] += $push_result_data->success;
        $offset += DARYO_PUSH_BULK_SIZE;
        sleep(DARYO_PUSH_SLEEP_TIME);
    }
    $offset = 0;
    while ($tokens = $wpdb->get_col("SELECT DISTINCT(`reg_id`) FROM {$table_name} WHERE `os_type`=1 LIMIT {$offset}, ".DARYO_PUSH_BULK_SIZE.";")) {
        $push_stats['devices_count'] += count($tokens);
        $push_stats['ios_count'] += count($tokens);
        $fails_count = daryo_send_apns($post_data, $tokens);
        $push_stats['devices_success_count'] += count($tokens) - $fails_count;
        $push_stats['ios_success_count'] += count($tokens) - $fails_count;
        $offset += DARYO_PUSH_BULK_SIZE;
        sleep(DARYO_PUSH_SLEEP_TIME);
    }
    file_put_contents($folder_name . "{$post_id}.txt", json_encode($push_stats));
}
function daryo_send_gcm($headers, $fields) {
    $ch = curl_init();
    curl_setopt($ch, CURLOPT_URL, 'https://android.googleapis.com/gcm/send');
    curl_setopt($ch, CURLOPT_POST, true);
    curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
    curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
    curl_setopt($ch, CURLOPT_POSTFIELDS, json_encode($fields));
    $result = curl_exec($ch);
    curl_close($ch);
    return $result;
}
function daryo_send_apns($post_data, $tokens) {
    $push = new ApnsPHP_Push(
        ApnsPHP_Abstract::ENVIRONMENT_PRODUCTION,
        dirname(__FILE__) . '/daryo.pem'
    );
    $push->connect();
    $index = 0;
    foreach ($tokens as $token) {
        $message = new ApnsPHP_Message($token);
        // Set a custom identifier. To get back this identifier use the getCustomIdentifier() method
        // over a ApnsPHP_Message object retrieved with the getErrors() message.
        $message->setCustomIdentifier(sprintf("msg-%03d", $index));
        $message->setText($post_data['title']);
        $message->setCustomProperty('post_id', $post_data['id']);
        $message->setExpiry(2 * 24 * 3600);
        $message->setSound('default');
        $message->setBadge(1);
        // Add the message to the message queue
        $push->add($message);
        $index++;
    }
    $push->send();
    $push->disconnect();
    $errors = $push->getErrors();
    global $wpdb;
    $table_name = $wpdb->prefix . DARYO_ANDROID_REG_IDS;
    foreach($errors as $error){
        try{
            $token = $error['MESSAGE']->getRecipient();
            $wpdb->delete($table_name, array('reg_id' => $token));
        }
        catch(ApnsPHP_Message_Exception $e ){
            
        }
    }
    return count($errors);
}
function daryo_get_post_data_for_push($post, $crop_thumb=true) {
    $match_result = array();
    $match = preg_match_all('#"(http:\/\/daryo\.uz\/[^"]+\/)"#si', $post->post_content, $match_result);
    $links = array();
    if ($match) {
        foreach ($match_result[1] as $link) {
            $link_post_id = url_to_postid($link);
            if (!empty($link_post_id)) {
                $links[$link] = $link_post_id;
            }
        }
    }
    if (function_exists('dy_get_related_posts')) {
        $related_posts = dy_get_related_posts();
        foreach ($related_posts as $related_post) {
            $links[get_permalink($related_post->ID)] = $related_post->ID;
        }
    }
    $url = 'http://daryo.uz/api/post/view/'.$post->ID.'/';
    return array(
        'id' => $post->ID,
        'title' => $post->post_title,
        'date' => $post->post_date,
        'thumbnail' => daryo_post_thumbnail($post->ID),
        'photo' => daryo_post_thumbnail($post->ID, false),
        'url' => $url,
        'link' => get_permalink($post->ID),
        'links' => $links,
    );
}
