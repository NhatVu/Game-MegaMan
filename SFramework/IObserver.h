#ifndef _IObserver_H_
#define _IObserver_H_


class IObserver
{
public:
	IObserver();
	~IObserver();
	virtual void update(int keyCode);
};

#endif // !_IObserver_H_