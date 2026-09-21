#pragma warning (disable : 4786)
#define _CRT_SECURE_NO_DEPRECATE
#include <string>
#include <vector>
using namespace std;
#include "ini_file.h"
#include "parser.h"
#include <stdio.h>

CIniFile::CIniFile()
{
	m_status = 0;
}

void CIniFile::ClearAll()
{
	m_file.clear();
	m_status = 0;
}

void CIniFile::LoadFile(string filename)
{
	m_file.clear();

	if (filename.empty())
	{
		m_status = 1;
		return;
	}

	FILE * fin = fopen(filename.c_str(),"rt");

	if (fin)
	{
		fseek(fin,0, SEEK_END);
		int filesize = ftell(fin);
		fseek(fin,0, SEEK_SET);
		char * buffer = (char *)calloc(filesize + 1, 1 );
		fread(buffer, filesize, 1, fin);
		fclose(fin);
		int ec = ParseIniFile(buffer, m_file);
		if (!ec)
			m_status = 2;

		free(buffer);
	}
	else
	{
       ///////////////////////fin = fopen(filename.c_str(),"wt");
		m_status = 1;
		//////////////////////printf("Could not open input file %s\n", filename.c_str());
	}
}


void CIniFile::SaveToFile(string filename)
{
	FILE * fout = fopen(filename.c_str(),"wt");

	if (fout)
	{
		unsigned int c;
		for (c=0;c<m_file.size();c++)
		{
			fprintf(fout,"[%s]\n",m_file[c].name.c_str());
			unsigned int i;
			for (i=0;i<m_file[c].entries.size();i++)
			{
				fprintf(fout,"%s=%s\n", m_file[c].entries[i].name.c_str(), m_file[c].entries[i].value.c_str());
			}
			fprintf(fout,"\n");
		}
		fclose(fout);
	}
	else
	{
		printf("Could not open output file %s\n", filename.c_str());
	}
}


int CIniFile::GetNumCategories()
{
	return (int)m_file.size();
}

void CIniFile::SetCategory(int cat)
{
	m_crt_category = cat;
}

int CIniFile::b_CategoryIsValid()
{
	if ( ( m_crt_category >= 0 ) && ( m_crt_category < m_file.size() ) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
		
}

int CIniFile::b_EntryIsValid()
{
	if (b_CategoryIsValid())
	{
		if ( ( m_crt_entry >= 0) && ( m_crt_entry < m_file[m_crt_category].entries.size() ) )
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}


int CIniFile::SetCategory(string name)
{
	int i;
	for (i=0;i<m_file.size();i++) 
	{
		if (m_file[i].name == name)
		{
			m_crt_category = i;
			return 1;
		}
	}
	return 0;
}

void CIniFile::AddCategoryUnique(string name)
{
	if ( SetCategory(name) )
		return;

	Category cat;
	cat.name = name;
	m_file.push_back(cat);
	m_crt_category = m_file.size() - 1;
}

void CIniFile::AddCategory(string name)
{
	Category cat;
	cat.name = name;
	m_file.push_back(cat);
	m_crt_category = m_file.size() - 1;
}

int CIniFile::GetNumEntries()
{
	if ( ! b_CategoryIsValid() )
	{
		return 0;
	}
	return m_file[m_crt_category].entries.size();
}

void CIniFile::SetEntry(int entry)
{
	m_crt_entry = entry;
}

int CIniFile::SetEntry(string name)
{
	if ( ! b_CategoryIsValid() )
	{
		return 0;
	};

	int i;
	for (i=0;i<m_file[m_crt_category].entries.size();i++) 
	{
		if (m_file[m_crt_category].entries[i].name == name)
		{
			m_crt_entry = i;
			return 1;
		};
	};
	return 0;
}

int CIniFile::SetEntryByValue(string value)
{
	if ( ! b_CategoryIsValid() )
	{
		return 0;
	};

	int i;
	for (i=0;i<m_file[m_crt_category].entries.size();i++) 
	{
		string cval = m_file[m_crt_category].entries[i].value;
		if (cval == value)
		{
			m_crt_entry = i;
			return 1;
		};
	};
	return 0;
}

void CIniFile::ChangeEntry(string name, string value)
{
	if ( !SetEntry(name) )
		return;
	m_file[m_crt_category].entries[m_crt_entry].value = value;
}

void CIniFile::SetValue(string value)
{
	if ( ! b_EntryIsValid() )
	{
		return ;
	};
	m_file[m_crt_category].entries[m_crt_entry].value = value;
}

void CIniFile::AddEntryUnique(string name, string value)
{
	if ( SetEntry(name) )
	{
		ChangeEntry( name, value);
		return;
	}
	Entry entry;
	entry.name = name;
	entry.value = value;
	
	m_file[m_crt_category].entries.push_back(entry);
	m_crt_entry = m_file[m_crt_category].entries.size() - 1;
}

void CIniFile::AddEntry(string name, string value)
{
	Entry entry;
	entry.name = name;
	entry.value = value;
	m_file[m_crt_category].entries.push_back(entry);
	m_crt_entry = m_file[m_crt_category].entries.size() - 1;
}


string CIniFile::GetCategoryName()
{
	if ( ! b_CategoryIsValid() )
	{
		return "";
	};
	return m_file[m_crt_category].name;
}

string CIniFile::GetEntryName()
{
	if ( ! b_EntryIsValid() )
	{
		return "";
	};

	return m_file[m_crt_category].entries[m_crt_entry].name ;
}

string CIniFile::GetEntryValue()
{
	if ( ! b_EntryIsValid() )
	{
		return "";
	};

	return m_file[m_crt_category].entries[m_crt_entry].value ;
}

string CIniFile::GetEntryValueByName(string name)
{
	SetEntry(name);
	return GetEntryValue();
}

void CIniFile::DeleteEntry(string name)
{
	if ( SetEntry(name) )
	{
		DeleteEntry(m_crt_entry);
	}
}

void CIniFile::DeleteEntry(int entry)
{
	if ( ! b_EntryIsValid() )
	{
		return ;
	};

	vector<Entry> & entries = m_file[m_crt_category].entries;
	entries.erase( entries.begin() + m_crt_entry );
}

void CIniFile::DeleteByValue(string value)
{
	if ( SetEntryByValue(value) )
	{
		DeleteEntry(m_crt_entry);
	}
}

