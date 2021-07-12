#pragma once

#include"RepositoryException.h"

#include <string>
#include <vector>
#include <fstream>

using namespace std;

//an abstract class which will allow me implementing the RepositoryFileCSV and the RepositoryFileTXT
//future posibility: implement RepositoryFieJSON
template<class T>
class RepoFile
{
protected:
	vector<T> elements;
	string fileName;
public:
	RepoFile(string name);
	~RepoFile();

	virtual void saveToFile() = 0;
	virtual void loadFromFile() = 0;

	void setFileName(string);

	vector<T> getAll();

	bool find(T el);
	void add(T el);
	void update(T old_elem, T new_elem);
	void deleteElem(T elem);
	T getElementByID(int id);
};

template<class T>
inline RepoFile<T>::RepoFile(string name)
{
	this->fileName = name;
}

template<class T>
inline RepoFile<T>::~RepoFile()
{
	this->elements.clear();
}

template<class T>
inline void RepoFile<T>::setFileName(string newFileName)
{
	this->fileName = newFileName;
}

template<class T>
inline vector<T> RepoFile<T>::getAll()
{
	return this->elements;
}

template<class T>
inline bool RepoFile<T>::find(T el)
{
	for (T elCrt : this->elements) {
		if (elCrt == el) {
			return true;
		}
	}
	return false;
}

template<class T>
inline void RepoFile<T>::add(T el)
{
	this->elements.push_back(el);
	this->saveToFile();
}

template<class T>
inline void RepoFile<T>::update(T old_elem, T new_elem)
{
	for (int i = 0; i < this->elements.size(); i++) {
		if (this->elements[i] == old_elem) {
			this->elements[i] = new_elem;
			break;
		}
	}
	this->saveToFile();
}

template<class T>
inline void RepoFile<T>::deleteElem(T elem)
{
	for (int i = 0; i < this->elements.size(); i++) {
		if (this->elements[i] == elem) {
			this->elements.erase(this->elements.begin() + i);
			break;
		}
	}
	this->saveToFile();
}

template<class T>
inline T RepoFile<T>::getElementByID(int id)
{
	for (T elCrt : this->elements) {
		if (elCrt.getID() == id) {
			return elCrt;
		}
	}
	throw RepositoryException("The element does not exist!");
}
