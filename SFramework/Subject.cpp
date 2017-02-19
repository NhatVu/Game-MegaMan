#include "Subject.h"
#include <algorithm>

using namespace std;

Subject::Subject(){

}

Subject::~Subject(){

}

void Subject::Attach(IObserver *observer)
{
	list.push_back(observer);
}
void Subject::Detach(IObserver *observer)
{
	list.erase(std::remove(list.begin(), list.end(), observer), list.end());
}

void Subject::Notify(int keyCode)
{
	/*for (vector<IObserver*>::const_iterator iter = list.begin(); iter != list.end(); ++iter)
	{
		if (*iter != 0)
		{
			(*iter)->update(keyCode);
		}
	}*/

	std::list<IObserver*>::const_iterator iterator;
	for (iterator = list.begin(); iterator != list.end(); ++iterator) {
		if (*iterator != 0){
			IObserver* test = (*iterator);
			test->updateKeyboard(keyCode);
		}
	}
	
}