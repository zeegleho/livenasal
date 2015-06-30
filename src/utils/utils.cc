
/*
 * Copyright (c) 2015, zeegle.ho@gmail.com, He Zhigang, Beijing
 * All rights reserved.
 * LiveNasal, a simulator of nasal, created by zeegle.ho/he zhigang.
 */
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <regex>
//#include <assert>
#include <regex.h>
#include <stdio.h>
#include "utils.h"

std::string Utils::delim = " ";
std::string& Utils::delim_ = delim;
//std::string Utils::delim_(" ");

char* Utils::substr(const char*str, unsigned start, unsigned end)
{
    unsigned n = end - start;
    static char stbuf[256];
    strncpy(stbuf, str + start, n);
    stbuf[n] = 0;
    return stbuf;
}

void Utils::reStyle(std::string& s) {
    size_t comment_index=s.find_first_of(";");
    s = s.substr( 0, comment_index ); 
    comment_index=s.find_first_of("//");
    s = s.substr( 0, comment_index ); 
    
    if( s.length()==0 )
    {
	return;
    }

    const char* orignal_string = s.c_str();

    unsigned int b, e;
    std::string temp("");

    b = 0; 
    e = 0;
    while( orignal_string[e] == ' ' 
	   || orignal_string[e] == '\t' )
	e ++;
    s.erase( 0, e );
    for( b = 0; b<s.length(); b++){
	while( b<s.length() 
	       && orignal_string[b] != ' ' 
	       && orignal_string[b] != '\t' )
	   b ++;
	if( b==s.length() ) break;

	e = b+1;
	while( orignal_string[e] == ' ' 
	       || orignal_string[e] == '\t' )
	   e ++;

	s.replace( b, e-b, " ");
    }
    b = s.length(); 
    while( b>0
	   &&( orignal_string[b-1] == ' ' || orignal_string[b-1] == '\t' )
	   )
	b --;
    if( b!=s.length() )
    s.erase( b, s.length()-b );

   /* 
    regex_t reg;
    const size_t nmatch = 10;
    regmatch_t pm[4];
    char *pattern ="[a-zA-Z_]*"; 
    int z;
    char ebuf[128], lbuf[256];

    if (regcomp(&reg, pattern, REG_EXTENDED |REG_NEWLINE) != 0){
	fprintf(stderr, "Cannot regex compile!");
	return;
    }

	std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;
    z = regexec(&reg, s.c_str(), nmatch, pm, 0);
	std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;
    if (z != 0) {
	std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;
	regerror(z, &reg, ebuf, sizeof(ebuf));
	fprintf(stderr, "%s: regcom('%s')\n", ebuf, lbuf);
	return;
    }
	std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<" "<<nmatch<<std::endl;


    //for ( int x = 0; x < nmatch && pm[x].rm_so != -1; x++ ) {
    for ( int x = 0; x < nmatch ; x++ ) {
	//if (!x) printf("%04d: %s\n", lno, lbuf);
	//std::cout<<"    $"<<x<<"='"<<substr(s.c_str(), pm[x].rm_so, pm[x].rm_eo)<<"'"<<std::endl;
	std::cout<<"    "<< pm[x].rm_so<<" "<< pm[x].rm_eo<<std::endl;
    }
    std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;

    //regfree(&reg);
    */

    /*
    std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;
    std::regex e ("[\\s]{2}"); 
    std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;
    while ( std::regex_match (s,e) ){
	s = std::regex_replace (s,e,delim);
    std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;
    }
    std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;

    std::regex head_e ("^ "); 
    if ( std::regex_match (s,head_e) ){
	s = std::regex_replace (s,head_e,delim);
    }
    std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;
    
    std::regex tail_e (" $"); 
    if ( std::regex_match (s,tail_e) ){
	s = std::regex_replace (s,tail_e,delim);
    }
    std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;
*/
    /*
    std::cmatch cm;    // same as std::match_results<const char*> cm;
    std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;
    std::regex tail_e ( "([a-zA-Z_]){2}" ); 
    std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;
    std::regex_search (s.c_str(),cm, tail_e);
    if ( cm.size()==0 ){
	return;
    }
    std::cout<<cm.size()<<"-";
    for( unsigned int i=0;i<cm.size();i++){
	std::cout<<"-"<<cm[i];
    }
    std::cout<<std::endl;
    std::cout<<"-----zeegle--------"<<__FILE__<<":"<<__LINE__<<"-"<<s<<"-"<<s.length()<<std::endl;
*/

}
void Utils::split(std::string& s, std::string& delim,std::vector< std::string >* ret)  
{  
    
    if( s.length()==0 )
    return;

    reStyle(s);

    size_t last = 0;  
    size_t index=s.find_first_of(delim,last);  
    while (index!=std::string::npos)  
    {  
        ret->push_back(s.substr(last,index-last));  
        last=index+1;  
        index=s.find_first_of(delim,last);  
    }  
    if (index-last>0)  
    {  
        ret->push_back(s.substr(last,index-last));  
    }  

    //std::cout<<"------------zeegle---------"<<__FILE__<<":"<<__LINE__<<" "<<ret->size();
    //for( std::vector< std::string>::iterator it = ret->begin(); it!=ret->end();it++)
	//std::cout<<"-"<<(*it).c_str();
    //std::cout<<std::endl;
}  
std::string& Utils::getDelim(){
	return delim_;
}

void Utils::setDelim( std::string& d ){
	delim_ = d;
}
