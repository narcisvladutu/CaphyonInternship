#pragma once
#include "RepositoryFile.h"

//allow working with csv files

template <class T>
class RepositoryFileCSV : public RepoFile<T>
{
public:
	RepositoryFileCSV(string);
	void saveToFile();
	void loadFromFile();
	~RepositoryFileCSV();
};

template<class T>
RepositoryFileCSV<T>::RepositoryFileCSV(string name) :RepoFile<T>(name) {
	this->loadFromFile();
}

template<class T>
RepositoryFileCSV<T>::~RepositoryFileCSV()
{
}

template<class T>
void RepositoryFileCSV<T>::saveToFile()
{
	ofstream f(this->fileName);
	for (T crt : this->elements) {
		string result = crt.toStringDelimiter(',');
		f << crt.toStringDelimiter(',') << endl;
	}
	f.close();
}

template<class T>
void RepositoryFileCSV<T>::loadFromFile()
{
	string line;
	ifstream f(this->fileName);
	this->elements.clear();
	while (std::getline(f, line)) {
		try {
			T ob(line, ',');
			this->elements.push_back(ob);
		}
		catch (exception ex) {
			throw ex;
		}
	}
}	
