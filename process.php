<?php
/* 'homeostasis' is defined as being closer to the control temperature than the dead-world temperature */

$clearance = array("100", "095", "090");
$cleartime = array("31500", "32000", "32500");
$solar_int = array();
$count = 10;
$check = "35000";
$folder = "data.final";

$empty_frame = load_frame("$folder/empty.dat", $check);
$base_temp = $empty_frame[5];
echo " * Base temperature is $base_temp\n";
foreach($cleartime as $k => $a) {
    $empty_frame = load_frame("$folder/empty.dat", $a);
    $solar_int[$k] = $empty_frame[1];
}

$result = array();

foreach($clearance as $c) {
    $result[$c] = array();
    foreach($cleartime as $k => $a) {
        $result[$c][$k] = 0;
    }
    
    for($i = 1; $i <= $count; $i++) {
        $this_frame = load_frame("$folder/forestry-$c-$i.dat", $check);
        if(is_homeostatic($this_frame[9], $base_temp, $this_frame[5])) {
            $result[$c][0]++;
        }
        if(is_homeostatic($this_frame[13], $base_temp, $this_frame[5])) {
            $result[$c][1]++;
        }
        if(is_homeostatic($this_frame[17], $base_temp, $this_frame[5])) {
            $result[$c][2]++;
        }
    }
}

foreach($result as $baz => $foo) {
    $a = "";
    foreach($foo as $k => $bar) {
        $a .= round($solar_int[$k],3) . "\t" . $bar . "\n";
    }
    file_put_contents("$folder/summary-$baz.dat", $a);
}

function is_homeostatic($world_temp, $base_temp, $homeostatic_temp) {
    $ok = abs($base_temp - $world_temp) > abs($homeostatic_temp - $world_temp) ? "1" : "0";
    echo "$world_temp $base_temp $homeostatic_temp $ok\n";
    return $ok;
}

function load_frame($file, $frame) {
    $f = file_get_contents($file);
    $b = explode("\n", $f);
    foreach($b as $l) {
        $a = explode("\t", $l);
        if($a[0] == $frame) {
            return $a;
        }
    }
    return false;
}

?>
