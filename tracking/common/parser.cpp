#pragma warning (disable : 4786)
#include <string>
#include <vector>
using namespace std;
#pragma warning (disable : 4761)
#include "ini_file.h"
#include "parser.h"
#include "boost/spirit.hpp"

using namespace boost;
using namespace spirit;

struct AddCategory
{
	CategoryList * m_file;
	void operator() (char const* str, char const* end) const
	{
		string name(str, end);
		Category cat;
		cat.name = name;
		m_file->push_back(cat);
	}
};


struct AddName
{
	CategoryList * m_file;
	void operator() (char const* str, char const* end) const
	{
		string name(str, end);
		int last_cat_id = m_file->size() - 1;
		if (last_cat_id == -1)
		{
			Category cat;
			cat.name = "Globals";
			m_file->push_back(cat);
			last_cat_id = 0;
		}
		Entry entry;
		entry.name = name;
		m_file->at(last_cat_id).entries.push_back(entry);
	}
};


struct AddValue
{
	CategoryList * m_file;
	void operator() (char const* str, char const* end) const
	{
		string value(str, end);
		int last_cat_id = m_file->size() - 1;
		int last_entry_id = m_file->at(last_cat_id).entries.size() - 1;
		if (last_entry_id == -1)
		{
			Entry entry;
			entry.name = "";
			m_file->at(last_cat_id).entries.push_back(entry);
			last_entry_id = 0;
		};
		m_file->at(last_cat_id).entries[last_entry_id].value = value;
	}
};


int ParseIniFile(char * buffer, CategoryList & file_data)
{
	string name, value;

	AddCategory addCategory;
	addCategory.m_file = &file_data;

	AddName addName;
	addName.m_file = &file_data;

	AddValue addValue;
	addValue.m_file = &file_data;

	rule<> char_ident_start = alpha_p | ch_p('_') ;
	rule<> char_ident_middle = alnum_p | ch_p('_') ;
	rule<> ident = char_ident_start >> * char_ident_middle ;
	rule<> char_start_comment = ch_p('#') | ch_p(';') | str_p("//");
	rule<> blanks_p = * blank_p;
	rule<> value_p = * ( alnum_p | blank_p | punct_p );
	
	rule<> l_category = 
					blanks_p >> 
					ch_p('[') >> 
					blanks_p >> 
					ident [ addCategory ] >>
					blanks_p >> 
					ch_p(']') >> 
					blanks_p >> 
					eol_p
	;
	
	rule<> l_comment = blanks_p >> char_start_comment >> * print_p >> eol_p; 
	rule<> l_empty = blanks_p >> eol_p; 
	rule<> c_comment_rule = confix_p("/*", *anychar_p, "*/");

	rule<> b_comment = 
					blanks_p >> 
					c_comment_rule >>
					blanks_p >> 
					eol_p
	; 

	rule<> l_entry =  
					blanks_p >>
					ident [ addName ] >> 
					blanks_p >>
					ch_p('=') >> 
					blanks_p >>
					value_p [ addValue ] >> 
					blanks_p >>
					eol_p
	; 

	rule<> lines = l_comment | b_comment | l_category | l_entry | l_empty;
	rule<> ini_file =  lexeme_d [ * lines ] ;

	file_data.clear();
	
	int errcode = parse(buffer, ini_file).full;

	return errcode;
}

