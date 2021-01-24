<?php

//this is the base model. Here we have the update create and delete logic
class Model
{
    protected $table;

    protected function create($values, $table_name)
    {
        $this->table = $table_name;
        //(name=>val,name2=>val2)
        $dataBase = new DB();
        $pdo = $dataBase->getDb();

        foreach ($values as $field => $v)
            $ins[] = ':' . $field;

        $ins = implode(',', $ins);
        $fields = implode(',', array_keys($values));
        $sql = "INSERT INTO $this->table ($fields) VALUES ($ins)";

        $sth = $pdo->prepare($sql);
        foreach ($values as $f => $v)
        {
            $sth->bindValue(':' . $f, $v);
        }
        if (!$sth->execute()) {
            print_r($sth->errorInfo());
        }

        $sth->debugDumpParams();
    }

    protected function selectAll($table_name)
    {
        $this->table = $table_name;

        $dataBase = new DB();
        $pdo = $dataBase->getDb();

        $sql = "SELECT * From `$this->table`";
        $sth = $pdo->prepare($sql);
        $sth->execute();

        return $sth->fetch(\PDO::FETCH_ASSOC);
    }

    protected function selectWhere($values, $table_name)
    {
        //(name=>val,name2=>val2)
        $this->table = $table_name;
        $dataBase = new DB();
        $pdo = $dataBase->getDb();

        foreach ($values as $field => $v)
            $wheres[] = ':' . $field;

        $wheres = implode(',', $wheres);
        $fields = implode(',', array_keys($values));

        $sql = "SELECT * FROM `$this->table` WHERE `$fields` LIMIT 1";

        $sth = $pdo->prepare($sql);
        foreach ($values as $f => $v)
        {
            $sth->bindValue(':' . $f, $v);
        }
        $sth->execute();

        return $sth->fetch(PDO::FETCH_ASSOC);
    }

    protected function update()
    {
        //NO NEED FOR A UPDATE BECAUSE ALL NEEDS TO BE SAVED
    }

    protected function delete()
    {
        //NO NEED FOR A DELETE BECAUSE ALL NEEDS TO BE SAVED
    }
}