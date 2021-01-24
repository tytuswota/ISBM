<?php

class DB
{
    private $host = "localhost";
    private $data_base = "webhook";
    private $user = "phpmyadmin";
    private $password = "xxx";
    private $db;

    function __construct(){
	try{
            $dns = "mysql:host=" . $this->host . ";dbname=" . $this->data_base;
	    $this->db = new PDO($dns, $this->user, $this->password);
	}catch (PDOException $ex){
            echo $ex->getMessage();
        }

    }

    public function getDb()
    {
        if ($this->db instanceof PDO) {
            return $this->db;
        }
    }
}
