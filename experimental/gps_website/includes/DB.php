<?php 
   class DB{
        private $host = "localhost";
        private $data_base = "boat_data";
        private $user = "root";
        private $password = ":;9(=W;P,CDmr5cj";
        public $db;

        function __construct(){
	    try{
                $dns = "mysql:host=" . $this->host . ";dbname=" . $this->data_base;
                $this->db = new PDO($dns, $this->user, $this->password);
            }catch (PDOException $ex){
                echo "Unable to connect";
            }

        }

    }
