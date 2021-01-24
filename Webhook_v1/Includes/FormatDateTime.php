<?php

class FormatDateTime
{
    public static function formatDT($date)
    {
        $date = new DateTime($date);
        return $date->format('Y-m-d H:i:s');
    }
}