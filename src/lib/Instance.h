/*
 * Instance.h
 *
 *  Created on: 02/05/2015
 *      Author: vagner
 */

#ifndef INSTANCE_H_
#define INSTANCE_H_
#include <list>
#include <string>
#include <iterator>

namespace PAA {

template <class T> class Instance {
private:
	int size;
	std::list<T>* instanceList;
	typename std::list<T>::iterator nextItem;
protected:
	int getSize();
	void setSize(int);
	void incrementSize(void);
	void decreaseSize(void);
	void addInstanceItem(const T&);
	T getInstanceItem(int);
	T getByID(int);
	T getNextItem(void);
	void setNextItem(typename std::list<T>::iterator);
	typename std::list<T>::iterator getBeginList();
	typename std::list<T>::iterator getEndList();
	bool hasMore(void);
	void sort(void);
	virtual void load(std::string&) = 0;
	virtual void print(void) = 0;



public:
	Instance();
	virtual ~Instance();
};

template<class T> void Instance<T>::decreaseSize(void){

	if(this->getSize() > 0){
		this->setSize((this->getSize()-1));
	}
}

template<class T> int Instance<T>::getSize(void){

	return this->size;

}

template<class T> void Instance<T>::incrementSize(void){

	this->setSize((this->getSize()+1));
}

template<class T> void Instance<T>::setSize(int newSize){
	this->size = newSize;
}

template<class T> void Instance<T>::addInstanceItem(const T& instanceItem){

	this->instanceList->push_back(instanceItem);
	this->incrementSize();

}

template<class T> typename std::list<T>::iterator Instance<T>::getBeginList(){

	if(!this->instanceList->empty()){
		return this->instanceList->begin();
	}

}
template<class T> typename std::list<T>::iterator Instance<T>:: getEndList(){

	if(!this->instanceList->empty()){
			return this->instanceList->end();
		}
}

template<class T> T Instance<T>::getInstanceItem(int offSet){

	if(offSet >= 0 && offSet <= this->getSize()){

		typename std::list<T>::iterator it;
		it = this->getBeginList();
		if(offSet > 0){
			//Increase the iterator by offset
			std::advance (it,offSet);
		}
		return *(it);
	}
}

template<class T> T Instance<T>::getByID(int idItem){
	typename std::list<T>::iterator it;
	T findItem;

	for(it = this->instanceList->begin(); it != this->instanceList->begin(); it++){

		if(it->getID == idItem){
			findItem = *(it);
		}

	}
	return findItem;
}

template<class T> T Instance<T>::getNextItem(void){
	T item;
	if(this->nextItem != this->getEndList()){
		item = *(this->nextItem);

		this->nextItem++;

	}

	return item;
}

template<class T> bool Instance<T>::hasMore(void){

	return (this->nextItem != this->getEndList());
}

template<class T> void Instance<T>::setNextItem(typename std::list<T>::iterator it){

	this->nextItem = it;
}
template<class T> void Instance<T>::sort(void){

	this->instanceList->sort();
	this->nextItem = this->getBeginList();
}
template<class T> Instance<T>::Instance() {

	this->instanceList = new std::list<T>();
	this->setSize(0);
	this->nextItem = instanceList->begin();
}



template<class T> Instance<T>::~Instance() {
	delete this->instanceList;
}



} /* namespace PAA */

#endif /* INSTANCE_H_ */
