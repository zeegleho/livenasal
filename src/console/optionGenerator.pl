#!/usr/bin/perl

$HOME = $ARGV[0]; #`echo \$LIVENASALHOME`;
chomp($HOME);
$SRCHOME = "$HOME/src";
chomp($SRCHOME);
$OBJHOME = "$HOME/obj";
chomp($OBJHOME);
$input_file = "$SRCHOME/console/options.def";
$output_file_h = "$SRCHOME/console/options.h";
$output_file_m = "$SRCHOME/console/optionsMacros.h";
$output_file_c = "$SRCHOME/console/options.cc";

$define_macros_index = "";   #for .h
$define_macros_def =" ";
$define_macros = "";   #for .h
$declarations = "";     #for .h
$defines = "";        #for .cc 

$option_items_num = "";
#name|descriptions|valueType|candidateValue|defaultValue
$option_id = 0;
$option_name = "";
$option_value_type = "";
$options_value_array_size= "";
$option_candidate_value = "";
$option_default_value = "";
$option_accessable= "";
$option_descriptions= "";

sub createCCode;
sub buildOption;
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
	if( $option_id==0 ) { 
	    $option_items_num = `echo '$line' | awk -F \\\; \'{print NF}\'`;
	    $option_id ++;
	}elsif( $head eq "#" )  {
	}else{
	    @items = `echo '$line' | awk -F \\\; '{for (i = 1; i <= NF; i++) print \$i}'`;

	    $i=0;
	    $option_name = $items[$i++];
	    $option_value_type = $items[$i++];
	    $options_value_array_size= $items[$i++];
	    $option_candidate_value = $items[$i++];
	    $option_default_value =$items[$i++];
	    $option_accessable = $items[$i++];
	    $option_descriptions = $items[$i++];
	    chomp( $option_name );
	    chomp( $option_value_type );
	    chomp( $option_candidate_value );
	    chomp( $option_default_value );
	    chomp( $options_value_array_size );
	    chomp( $option_descriptions );

	    if( $option_name ne "" ){
		buildOption();
		$option_id ++;
	    }
	}

    }

    TailOUTPUT_C(OUTPUT_C);
    TailOUTPUT_H(OUTPUT_H);

}



sub createCCode{
    $line = delHeadBlank($_[0]);
}

sub buildOption{

    $define_macros_index = "#define Macors_$option_name\_index $option_id\n";
    print OUTPUT_M $define_macros_index;
    $define_macros_def = "#define Macors_$option_name\_def Options::getOption( Macors_$option_name\_index ) \n";
    print OUTPUT_M $define_macros_def;
    $define_macros = "#define Macors_$option_name Options::getOption( Macors_$option_name\_index ) \n";
    print OUTPUT_M $define_macros;
    $declarations = "    static OptionDef *option_$option_name; \n";
    print OUTPUT_H $declarations;
    if( $options_value_array_size eq "" ) {$options_value_array_size="-1";}
    $defines = "OptionDef * Options::option_$option_name = new OptionDef( 
	NSIdent::create( \"$option_name\" ), 
	NSIdent::create( \"$option_value_type\"   ), 
	NSIdent::create( \"$option_candidate_value\"  ), 
	NSIdent::create( \"$option_default_value\" ), 
	NSIdent::create( \"$option_descriptions\" ), 
	$options_value_array_size,
	$option_id  
	);
    \n\n";
    print OUTPUT_C $defines;

    $option_name = "";
    $option_value_type = ""; 
    $option_candidate_value = "";
    $option_default_value = "";
    $option_descriptions= "";

    return 1;
}

sub delHeadBlank{
    $res = $_[0];
    return $res;
}

sub HeadOUTPUT_C{
    print OUTPUT_C "#include \"optionDef.h\"","\n";
    print OUTPUT_C "#include \"options.h\"","\n";
    print OUTPUT_C "
    //index -> options_name 
    std::map< int, OptionDef* >* Options::options_ =
	    new std::map< int, OptionDef* >;
    //options_name -> index
    std::map< NSIdent*, int, NSIdentLess>* Options::options_index_=
	    new std::map< NSIdent*, int, NSIdentLess>;
    std::map< NSIdent*, OptionValue_t, NSIdentLess>* Options::options_type_=
	    new std::map< NSIdent*,  OptionValue_t, NSIdentLess>;

    OptionDef* Options::initOptionType( ){
	if(options_type_->size()==0){
	   options_type_->insert( std::pair<NSIdent*, OptionValue_t>( NSIdent::create(\"bool\"),  OptionValueType::type_bool) ) ;
	   options_type_->insert( std::pair<NSIdent*, OptionValue_t>( NSIdent::create(\"int\") ,  OptionValueType::type_int ) );
	   options_type_->insert( std::pair<NSIdent*, OptionValue_t>( NSIdent::create(\"double\"),          OptionValueType::type_double ) );
	   options_type_->insert( std::pair<NSIdent*, OptionValue_t>( NSIdent::create(\"string\"),          OptionValueType::type_string ) );
	   options_type_->insert( std::pair<NSIdent*, OptionValue_t>( NSIdent::create(\"boolarray\"),       OptionValueType::type_boolarray ) );
	   options_type_->insert( std::pair<NSIdent*, OptionValue_t>( NSIdent::create(\"intarray\") ,        OptionValueType::type_intarray ) );
	   options_type_->insert( std::pair<NSIdent*, OptionValue_t>( NSIdent::create(\"doublearray\"),     OptionValueType::type_doublearray ) );
	   options_type_->insert( std::pair<NSIdent*, OptionValue_t>( NSIdent::create(\"stringarray\"),     OptionValueType::type_stringarray ) );
	   options_type_->insert( std::pair<NSIdent*, OptionValue_t>( NSIdent::create(\"file\"),            OptionValueType::type_file ) )        ;
	    //OptionValueType::type_unknow;
	}
    }
    OptionDef* Options::getOption( int idx ){
	return (*options_)[idx];
    }
    OptionDef* Options::getOption( NSIdent* name ){
	return (*options_)[ mapOptionNameToIndex( name )];
    }
    void Options::setOption( NSIdent* name ){
	OptionDef* optdef = getOption( name );
	optdef->setValue( true );
    }
    void Options::setOption( NSIdent* name,  VALUETYPE value ){
	OptionDef* optdef = getOption( name );
	optdef->setValue( value );
    }
    void Options::setOption( int idx,  VALUETYPE value ){
	OptionDef* optdef = getOption( idx );
	optdef->setValue( value );
    }
    void Options::setOption( NSIdent* name,  NSIdent* value ){
	OptionDef* optdef = getOption( name );
	optdef->setValue( value );
    }
    void Options::setOption( int idx, NSIdent* value ){
	OptionDef* optdef = getOption( idx );
	optdef->setValue( value );
    }
   void Options::addOption( int index, OptionDef* option ){ 
       options_->insert( std::pair<int, OptionDef*>( index, option) ); 
   }
    \n\n";

}
sub HeadOUTPUT_H{
    print OUTPUT_H "#ifndef OPTIONS_H","\n";
    print OUTPUT_H "#define OPTIONS_H","\n";
    print OUTPUT_H "#include <map>","\n";
    print OUTPUT_H "#include \"optionDef.h\"","\n";
    print OUTPUT_H "#include \"optionsMacros.h\"\n";
    print OUTPUT_H "#include \"../utils/nsIdent.h\"\n";
    print OUTPUT_H "class Options{
    public:
        static OptionDef* initOptionType( );
	static OptionDef* getOption( int idx );
	static OptionDef* getOption( NSIdent* );
	static void setOption( NSIdent* name );
	static void setOption( NSIdent* name,  VALUETYPE value );
	static void setOption( int idx,  VALUETYPE value );
	static void setOption( NSIdent* name,  NSIdent* value );
	static void setOption( int idx, NSIdent* value );
	static void addOption( int index, OptionDef* option );
	static void addOptionIndex( NSIdent* name, int index ){
	    options_index_->insert( std::pair<NSIdent*, int>( name, index) ); 
	}
	static int mapOptionNameToIndex( NSIdent* name ){
	    return (*options_index_)[ name ];
	}
static OptionValue_t mapValueType( NSIdent* type ){
    if( options_type_->size()==0 )
	initOptionType( );
    return (*options_type_)[type];
}
	static std::map< int, OptionDef* >* options_;
	static std::map< NSIdent* , int, NSIdentLess > *options_index_;
	static std::map< NSIdent* ,  OptionValue_t, NSIdentLess > *options_type_;\n\n";
}
sub TailOUTPUT_C{
    print OUTPUT_C "
	\n\n";
}
sub TailOUTPUT_H{
    print OUTPUT_H "};","\n";
    print OUTPUT_H "#endif //OPTIONS_H","\n";
}

sub CreateClassOptionDef{
 }
