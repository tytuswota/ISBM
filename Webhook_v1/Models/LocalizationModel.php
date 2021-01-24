<?php


class LocalizationModel extends Model
{
    public $id;
    public $boat_id;
    public $longitude;
    public $latitude;
    public $date_time;
    private $table_name = "localization";

    public function store($values)
    {
        parent::create($values, $this->table_name);
    }

    public function getById($id)
    {
        $this->fillFields(parent::selectWhere(['id'=>$id], $this->table_name));
    }

    public function getAll()
    {
        parent::selectAll($this->table_name);
    }

    public function getByBoatId($boatId)
    {
        $this->fillFields(parent::selectWhere(['boat_id'=>$boatId], $this->table_name));
    }

    public function getByDate($date_time){
        $this->fillFields(parent::selectWhere(['date_time'=>$date_time], $this->table_name));
    }

    public function getByLongitudeLatitude($longitude, $latitude)
    {
        $this->fillFields(parent::selectWhere(['longitude'=>$longitude,'latitude'=>$latitude], $this->table_name));
    }

    private function fillFields($data)
    {
        $this->id        = $data["id"];
        $this->boat_id   = $data["boat_id"];
        $this->longitude = $data["longitude"];
        $this->latitude  = $data["latitude"];
        $this->date_time = $data["date_time"];
    }

}
