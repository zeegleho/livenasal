#!/usr/bin/perl

$HOME =  $ARGV[0]; #`echo \$LIVENASALHOME`;
chomp($HOME);
$SRCHOME = "$HOME/src";
chomp($SRCHOME);
$OBJHOME = "$HOME/obj";
chomp($OBJHOME);
$input_file = "$SRCHOME/messages/messages.def";
$output_file_h = "$SRCHOME/messages/messages.h";
$output_file_m = "$SRCHOME/messages/messagesMacros.h";
$output_file_c = "$SRCHOME/messages/messages.cc";

$define_macros = "";   #for .h
$declarations = "";     #for .h
$defines = "";        #for .cc 

$current_name = "";
$current_msg = "";
$current_sev= "";
$current_id= "";
$current_comment= "";

sub createCCode;
sub buildMsg;
sub delHeadBlank;
sub HeadOUTPUT_C;
sub HeadOUTPUT_H;
sub TailOUTPUT_C;
sub TailOUTPUT_H;

if (! -e $input_file){
    print "$input_file does not exist!";
    exit(1);
}

open(OUTPUT_H, ">$output_file_h");
open(OUTPUT_M, ">$output_file_m");
open(OUTPUT_C, ">$output_file_c");
 
if (open(INPUT, "<$input_file")) {

    HeadOUTPUT_C(OUTPUT_C);
    HeadOUTPUT_H(OUTPUT_H);

    while(<INPUT>){
	$line = $_;
	chomp($line);

	$head = substr($line, 0, 1);
	if( $head eq "#" ) { 
	}
	elsif( $head eq "X" ) { 
	    $current_id = `echo "$line" | awk '{print \$2}'`;
	    chomp( $current_id );
	    print OUTPUT_C "//id reset as $current_id\n";
	}
	elsif( $head eq "M" ) { 
	    $current_msg = substr( $line, 2, length($line)-2 );
	    chomp( $current_msg );
	}
	elsif( $head eq "N" ) { 
	    $current_name = `echo "$line" | awk '{print \$2}'`; 
	    chomp( $current_name );
	}
	elsif( $head eq "S" ) { 
	    $current_sev = `echo "$line" | awk '{print \$2}'`;
	    chomp( $current_sev );
	}
	elsif( $head eq "C" ) { 
	    $current_comment = substr( $line, 2, length($line)-2 );
	    chomp( $current_comment );
	    print OUTPUT_C "//$current_comment\n";
	}
	else{
	}

	if ($current_name ne "" && $current_msg ne "" && $current_sev ne "" ){
	    buildMsg();
	}
    }

    TailOUTPUT_C(OUTPUT_C);
    TailOUTPUT_H(OUTPUT_H);

}



sub createCCode{
    $line = delHeadBlank($_[0]);
}

sub buildMsg{
    if( $current_name eq "" ) {
	return 0;
    }

    my $count = 0; 

    $define_macros = "#define MSG_$current_name\_$count Messages::msg_$current_name\_$count \n";
    print OUTPUT_M $define_macros;
    $declarations = "    static MessageDef *msg_$current_name\_$count; \n";
    print OUTPUT_H $declarations;
    $defines = "MessageDef * Messages::msg_$current_name\_$count = new MessageDef( 
	NSIdent::create( \"$current_name\" ), 
	NSIdent::create( $current_msg ), 
	$current_sev, 
	$current_id  
	);\n\n";
    print OUTPUT_C $defines;


    $current_name = "";
    $current_msg = "";
    $current_sev= "";
    $current_comment= "";
    $current_id ++;
    return 1;
}

sub delHeadBlank{
    $res = $_[0];
    return $res;
}

sub HeadOUTPUT_C{
    print OUTPUT_C "#include \"messageDef.h\"","\n";
    print OUTPUT_C "#include \"messages.h\"","\n";
    

}
sub HeadOUTPUT_H{
    print OUTPUT_H "#ifndef MESSAGES_H","\n";
    print OUTPUT_H "#define MESSAGES_H","\n";
    print OUTPUT_H "#include \"messageDef.h\"","\n";
    print OUTPUT_H "#include \"messagesMacros.h\"\n";
    print OUTPUT_H "class Messages{", "\n";
    print OUTPUT_H "public:", "\n";
}
sub TailOUTPUT_C{
}
sub TailOUTPUT_H{
    print OUTPUT_H "};", "\n";
    print OUTPUT_H "#endif //MESSAGES_H","\n";
}

sub defineMsgSeverity{
$define_severitys = "

    ";
    print OUTPUT_M $define_severitys;
}
