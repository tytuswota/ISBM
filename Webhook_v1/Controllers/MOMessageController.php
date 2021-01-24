<?php

class MOMessageController
{
    public static function getAll()
    {
        $moMessage = new MOMessageModel();
        return $moMessage->getAll();
    }

    public static function createMessage($message)
    {
        $processed = self::processedMessage(self::decodeHexToText($message->data));

        $values = [
            'processed'         => $processed,
            'emei'              => $message->imei,
            'transmit_time'     => FormatDateTime::formatDT($message->transmit_time),
            'iridium_latitude'  => $message->iridium_latitude,
            'iridium_longitude' => $message->iridium_longitude,
            'iridium_cep'       => $message->iridium_cep,
            'data'              => $message->data,
        ];

        $moMessage = new MOMessageModel();
        $moMessage->store($values);

        if($processed){
            return explode(';', self::decodeHexToText($message['data']))[0];
        }else{
            return 0;
	}
    }

    public static function processedMessage($data)
    {
        if(strpos($data, ';') !== false)
        {
            $dataArray = explode(';', $data);
            if(in_array($dataArray[0], $GLOBALS['PROTOCOL_NUMBERS']))
	    {
                return 'true';
            }else {
                return 'false';
            }
        } else {
            return 'false';
        }
    }

    public static function decodeHexToText($hex) {
        $str = '';
        for($i=0;$i<strlen($hex);$i+=2) $str .= chr(hexdec(substr($hex,$i,2)));
        return $str;
    }
}