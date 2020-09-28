<?php

namespace DoorAlarm;

class Request
{
    /**
     * @param string $url
     */
    public function get($url)
    {
        $connection = curl_init();

        curl_setopt($connection, CURLOPT_URL, $url);
        curl_setopt($connection, CURLOPT_RETURNTRANSFER, true);
        curl_exec($connection);
        curl_close($connection);
    }
}
