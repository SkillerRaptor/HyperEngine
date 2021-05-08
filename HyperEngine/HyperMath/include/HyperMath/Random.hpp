#pragma once

#include <HyperCore/Assert.hpp>
#include <HyperCore/Log.hpp>

#include <random>
#include <type_traits>
#include <utility>

namespace HyperEngine
{
	class Random
	{
	public:
		Random(uint32_t seed = std::random_device()());
		
		template <class T>
		T Generate(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max1())
		{
			if constexpr (min > max)
			{
				std::swap(min, max);
				HYPERENGINE_CORE_WARNING("The minimum is greater than the maximum in random number generator!");
			}
			
			if constexpr (std::is_integral_v<T>)
			{
				std::uniform_int_distribution<T> distribution{ min, max };
				return static_cast<T>(distribution(m_randomEngine));
			}
			
			if constexpr (std::is_floating_point_v<T>)
			{
				std::uniform_real_distribution<T> distribution{ min, max };
				return static_cast<T>(distribution(m_randomEngine));
			}
			
			if constexpr (std::is_same_v<T, bool>)
			{
				std::bernoulli_distribution distribution{ 0.5f };
				return static_cast<T>(distribution(m_randomEngine));
			}
			
			constexpr bool isValid = std::is_integral_v<T> || std::is_floating_point_v<T> || std::is_same_v<T, bool>;
			HYPERENGINE_ASSERT(isValid, "Failed to generate random number of invalid arithmetic type!");
		}
	
	private:
		std::mt19937 m_randomEngine;
	};
}