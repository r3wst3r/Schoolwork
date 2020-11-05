
namespace ADS
{
	template<class T, class F>
	T& Singleton<T, F>::getInstance()
	{
		if (!exists())
		{
			create();
		}

		return *priv::Unique<T>::instance;
	}

	template<class T, class F>
	void Singleton<T, F>::create(bool force, F const& ctor)
	{
		if (exists() && force)
		{
			destroy();
			create(force, ctor);
		}
		else
		{
			priv::Unique<T>::instance = ctor();
		}
	}

	template<class T, class F>
	void Singleton<T, F>::destroy()
	{
		if (exists())
		{
			delete priv::Unique<T>::instance;
			priv::Unique<T>::instance = 0;
		}
	}

	template<class T, class F>
	bool Singleton<T, F>::exists()
	{
		return priv::Unique<T>::instance != 0;
	}

	template<class T, class F>
	Singleton<T, F>::Singleton() {}
}
