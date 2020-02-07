#include<iostream>
using namespace std;

class Mutex {
public:
	void Lock() { cout << "Lock" << endl; }
	void UnLock() { cout << "UnLock" << endl; }

	class Autolock {
		Mutex& mtx;
	public:
		inline Autolock(Mutex&m) : mtx(m) { mtx.Lock(); }
		inline ~Autolock() { mtx.UnLock(); }
	};

};

template<typename TYPE>
class Singleton{
protected:
	Singleton() {}
	Singleton(const Singleton&);
	~Singleton() {}
	void operator=(const Singleton&);

	static TYPE* sInstance;
	static Mutex sLock;

public:
	static TYPE& getInstance() {
		Mutex::Autolock sl(sLock);
		if (sInstance == 0)
			sInstance = new TYPE;

		return *sInstance;
	}// 실제로는 Instance로 작업할 때도 Mutex 걸어야 할 듯..
};

template<typename TYPE> TYPE* Singleton<TYPE>::sInstance = 0;
template<typename TYPE> Mutex Singleton<TYPE>::sLock;

class Mouse
{

};
// 이 외에도 매크로로도 싱글톤 선언 가능..

#define MAKE_SINGLETON( classname )                 \
    private:                                        \
        classname(){}                               \
        classname(const classname&);                \
        void operator=(const classname&);           \
    public:                                         \
        static classname& getInstace()              \
        {                                           \
            static classname instance;              \
            return instance;                        \
        }

class Cursor
{
	MAKE_SINGLETON(Cursor);
};

int main()
{
	Cursor::getInstace();
	return 0;
}


