<?php

class LocalizationController
{
    public static function getAll()
    {
      $localization = new Localization();
      return $localization->getAll();
    }

    public static function createLocalization($data)
    {
    	$values = [
		'boat_id' => $data->boat_id,
		'longitude' => $data->longitude,
		'latitude' => $data->latitude,
		'date_time' => $data->date_time
	];

	$localization = new LocalizationModel();
	$localization->store($values);
    }

}
