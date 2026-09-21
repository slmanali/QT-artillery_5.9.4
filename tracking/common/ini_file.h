#ifndef _INI_FILE_H_
#define _INI_FILE_H_

#include <string>
#include <vector>
#include <stdio.h>
using namespace std;
struct Entry
{
	string name;
	string value;
};

struct Category
{
	string name;
	vector<Entry> entries;
};

typedef vector<Category> CategoryList;

class CIniFile
{
	CategoryList m_file;
	int m_crt_category;
	int m_crt_entry;
private:
	int b_CategoryIsValid();
	int b_EntryIsValid();

public:
	CIniFile();
	void ClearAll();

	int m_status;
	void LoadFile(string filename);
	void SaveToFile(string filename);

	int GetNumCategories();
	void SetCategory(int cat);
	int SetCategory(string name);
	string GetCategoryName();
	void AddCategoryUnique(string name);
	void AddCategory(string name);

	int GetNumEntries();
	void SetEntry(int entry);
	int SetEntry(string name);
	int SetEntryByValue(string value);

	string GetEntryName();
	string GetEntryValue();
	string GetEntryValueByName(string name);
	void AddEntryUnique(string name, string value);
	void AddEntry(string name, string value);
	void ChangeEntry(string name, string value);
	void SetValue(string value);

	void DeleteEntry(string name);
	void DeleteEntry(int entry);
	void DeleteByValue(string value);


};



#endif

