#!/usr/bin/perl

#all the unit is mm
@pipe = {}; 
@x_pipe = {}; 
@y_pipe = {}; 
@z_pipe = {}; 

if( scalar(@ARGV) !=1 ){
	$partical=30;
}else{
	$partical=$ARGV[0];
}
$pie = 3.14;

$x_begin = 0;
$x_end = 300;
$y_begin = 100;
$y_end = 200;
$z_begin = 100;
$z_end = 200;
$radius = ( $y_end - $y_begin) / 2;
$perimeter = (2 * $radius) * $pie;

$x_cent1 = $x_begin;
$y_cent1 = ( $y_begin + $y_end ) / 2;
$z_cent1 = ($z_begin + $z_end ) / 2 ;

$x_cent2 = $x_end;
$y_cent2 = ( $y_begin + $y_end ) / 2;
$z_cent2 = ($z_begin + $z_end ) / 2 ;


for( $i = $x_begin; $i<$x_end; $i+=$partical ){
	push( @x_pipe, $i );
}

for ( $step= 0; $step<$perimeter; $step+=$partical){
	$angle = $step/$radius;
	$sin_value = sin($angle);
	push( @y_pipe, ( $y_cent1 +  ($radius * sin($angle) ) )  );
	push( @z_pipe, ( $y_cent1 +  ($radius * cos($angle) ) )  );
}


for( $i =1; $i<scalar(@x_pipe) ; $i++ ){ 
	for( $j =1; $j< scalar(@y_pipe); $j++ ){
		print " $x_pipe[$i] $y_pipe[$j] $z_pipe[$j]\n";
	}
}

