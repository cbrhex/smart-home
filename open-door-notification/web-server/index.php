<?php

namespace DoorAlarm;

include "Request.php";

class Main
{
    const BOT_TOKEN = "9999999:XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX"; // ТОКЕН бота який буде відправляти сповіщення
    const USER_ID = "99999999"; // ІД юзера якому будуть приходити сповіщення

    /**
     *
     */
    public function run()
    {
        $request = new Request;

        if ($this->getState()) {
            $message = 'Двері відкрито!';
        } else {
            $message = 'Двері закрито!';
        }

        $request->get($this->getUrl(self::BOT_TOKEN, self::USER_ID, $message));
    }

    /**
     * @param $botId
     * @param $userId
     * @param $message
     * @return string
     */
    private function getUrl($botId, $userId, $message)
    {
        return "https://api.telegram.org/bot${botId}/sendMessage?chat_id=${userId}&text=${message}";
    }

    /**
     * @return mixed
     */
    private function getState()
    {
        $json = file_get_contents("php://input");
        $data = json_decode($json);

        return (bool) $data->state;
    }
}

(new Main)->run();


