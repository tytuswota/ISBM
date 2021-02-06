<?php

class LocalizationController
{
    public static function getAll()
    {
      $localization = new Localization();
      return $localization->getAll();
    }

    public static function createLocalization($data = "")
    {
        $month = unpack("i", hex2bin(self::hexArray($data)[4]))[1];
        $day = unpack("i", hex2bin(self::hexArray($data)[3]))[1];
        $hour = unpack("i", hex2bin(self::hexArray($data)[5]))[1];
        $minute = unpack("i", hex2bin(self::hexArray($data)[6]))[1];
        $dateTimeString = "2021-" . $month . '-' . $day . ' ' . $hour . ':' . $minute . ':' . '00';

        echo $dateTimeString;

    	$values = [
		'boat_id' => 1,
		'longitude' => unpack("f", hex2bin(self::hexArray($data)[1]))[1],
		'latitude' => unpack("f", hex2bin(self::hexArray($data)[2]))[1],
		'date_time' => $dateTimeString
	];

	$localization = new LocalizationModel();
	$localization->store($values);
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
