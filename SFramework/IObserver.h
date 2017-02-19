#ifndef _IObserver_H_
#define _IObserver_H_


class IObserver
{
public:
	IObserver();
	~IObserver();
	virtual void updateKeyboard(int keyCode);
};

#endif // !_IObserver_H_
