#pragma once
#include "RepositoryFile.h"

//allow working with txt files

template <class T> class
RepositoryFileTXT : public RepoFile<T>
{
public:
	RepositoryFileTXT(string);
	void saveToFile();
	void loadFromFile();
	~RepositoryFileTXT();
};

template<class T>
inline RepositoryFileTXT<T>::RepositoryFileTXT(string name) :RepoFile<T>(name) {
	this->loadFromFile();
}

template<class T>
inline RepositoryFileTXT<T>::~RepositoryFileTXT()
{
}

template<class T>
inline void RepositoryFileTXT<T>::saveToFile()
{
	ofstream f(this->fileName);
	for (T crt : this->elements) {
		f << crt.toStringDelimiter(' ') << endl;
	}
	f.close();
}

template<class T>
inline void RepositoryFileTXT<T>::loadFromFile()
{
	string line;
	ifstream f(this->fileName);
	this->elements.clear();
	while (std::getline(f, line)) {
		try {
			T ob(line, ' ');
			this->elements.push_back(ob);
		}
		catch (exception ex) {
			throw ex;
		}
	}

}