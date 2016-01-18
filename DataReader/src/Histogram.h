//A. Guayaquil
//10.2015

#pragma once

#include <iostream>
#include <map>

namespace gg
{
	class Histogram
	{
	public:
		void generate(char * buffer, int size = 0)
		{
			for (int i = 0; i < size; i++)
			{
				/// Current number
				int number = int(buffer[i]);

				/// Not in histogram, create value
				if (m_dataContainer.find(number) == m_dataContainer.end())
				{
					m_dataContainer[number] = 0;
				}
				/// Already in histogram, increment frequency
				{
					m_dataContainer[number]++;
				}
			}
		}

		void print()
		{
			for (auto & data : m_dataContainer)
			{
				std::cout << data.first << " : " << data.second << std::endl;
			}
		}

	private:
		std::map<int, int> m_dataContainer;
	};
}