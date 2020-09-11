#pragma once

template <class T>
class mystack_v
{
private:
	T *data;
	int maxlen;
	int top;
public:
	mystack_v(int n=100);
	~mystack_v(void);
	const bool push(T);
	T pop(void);
	T read(void);
	const bool Empty(void);
	

};

template<class T>
inline mystack_v<T>::mystack_v(int n) : maxlen(n), top(-1)
{	
	data = new T[maxlen];
}

template<class T>
inline mystack_v<T>::~mystack_v(void)
{
	delete[] data;
}

template<class T>
const bool mystack_v<T>::push(T x)
{
	if (top == maxlen - 1) return false;
	data[++top] = x;
	return true;
}

template<class T>
inline T mystack_v<T>::pop(void)
{
	return data[top--];
}

template<class T>
inline T mystack_v<T>::read(void)
{
	return data[top];
}

template<class T>
inline const bool mystack_v<T>::Empty(void)
{
	return top<0;
}
