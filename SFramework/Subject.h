#ifndef _SUBJECT_H_
#define _SUBJECT_H_
#include <vector>
#include <list>
#include "IObserver.h"

class Subject
{
	//Lets keep a track of all the shops we have observing
	std::list<IObserver*> list;

public:
	void Attach(IObserver *observer);
	void Detach(IObserver *observer);
	void Notify(int keyCode);
	Subject();
	~Subject();
};

#endif // !_SUBJECT_H_



