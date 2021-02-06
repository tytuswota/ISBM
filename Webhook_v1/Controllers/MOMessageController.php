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
        $processed = self::processedMessage($message->data);

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
            return unpack("i", hex2bin(self::hexArray($message->data)[0]))[1];
        }else{
            return 0;
	}
    }

    public static function processedMessage($data)
    {
        if(self::hexArray($data)[0] > 0)
        {
            if(in_array(unpack("i", hex2bin(self::hexArray($data)[0]))[1], $GLOBALS['PROTOCOL_NUMBERS']))
	        {
                return 'true';
            }else {
                return 'falseA';
            }
        } else {
            return 'falseB';
        }
    }

    public static function hexArray($data)
    {
        $hexArray = [];
        try
        {
            return $hexArray = str_split($data, 8);
        }catch (Exception $exceptione){
            return $hexArray[0] = 0;
        }
    }
}
