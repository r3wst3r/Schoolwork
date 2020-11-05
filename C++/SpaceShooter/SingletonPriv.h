#ifndef _SINGLETONPRIV_H_
#define _SINGLETONPRIV_H_

// Structs used only by Singleton

namespace ADS
{
	namespace priv
	{
		template<class T>
		struct Unique
		{
			static T* instance;
		};

		template<class T>
		T* Unique<T>::instance = 0;

		template<class T>
		struct DefaultNew
		{
			T* operator() () const
			{
				return  new T();
			}
		};
	}
}
#endif // !_SINGLETONPRIV_H_

