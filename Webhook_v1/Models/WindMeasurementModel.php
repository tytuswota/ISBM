<?php


class WindMeasurementModel extends Model
{
    public $id;
    public $ms;
    public $knots;
    public $localization_id;
    private $table_name = "boat_sensors";

    public function store($values)
    {
        parent::create($values, $this->table_name);
    }

    public function getAll()
    {
        parent::selectAll($this->table_name);
    }

    public function getById($id)
    {
        $this->fillFields(parent::selectWhere(['id'=>$id], $this->table_name));
    }

    public function getLocalizationId($localization_id)
    {
        $this->fillFields(parent::selectWhere(['localization_id'=>$localization_id], $this->table_name));
    }

    public function getByDate($date_time){
        $this->fillFields(parent::selectWhere(['date_time'=>$date_time], $this->table_name));
    }

    private function fillFields($data)
    {
        $this->id              = $data["id"];
        $this->ms              = $data["ms"];
        $this->knots           = $data["knots"];
        $this->localization_id = $data["localization_id"];
        $this->date_time       = $data["date_time"];
    }
}