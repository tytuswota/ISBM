<?php

//this model communicates with the MTMessages table
class MTMessageModel extends Model
{
    public $id;
    public $emei;
    public $transmit_time;
    public $iridium_latitude;
    public $iridium_longtitude;
    public $iridium_cep;
    public $data;
    private $table_name = "mt_messages";

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


    private function fillFields($data)
    {
        $this->id                 = $data["id"];
        $this->emei               = $data["emei"];
        $this->transmit_time      = $data["transmit_time"];
        $this->iridium_latitude   = $data["iridium_latitude"];
        $this->iridium_longtitude = $data["iridium_longtitude"];
        $this->iridium_cep        = $data["iridium_cep"];
        $this->data               = $data["data"];
    }
}