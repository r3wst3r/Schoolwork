#ifndef _SINGLETON_H_
#define _SINGLETON_H_

#include <SFML/System/NonCopyable.hpp>

#include "SingletonPriv.h"

namespace ADS
{
	template <class T, class F = priv::DefaultNew<T>>
	class Singleton : sf::NonCopyable
	{
	public:
		static T& getInstance();

		static void create(bool force = false, F const& factory = F());

		static void destroy();

		static bool exists();

	protected:
		Singleton();
	};
}

#include "Singleton.inc"

#endif // !_SINGLETON_H_
