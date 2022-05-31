#include "polyPhaseMerge.h"
#include "testsHelper.h"


void polyPhaseMerge(std::string filename)
{
	int count = 6;
	FileManager manager(1, count - 1);
	std::fstream file;
	file.open(filename, std::ios::in);
	firstDistrib(file, manager);
	file.close();

	/* Сливаем пустые серии*/
	int min = manager.output[0].idleSeries;
	for (int i = 1; i < count -1; i++)
	{
		if (min > manager.output[i].idleSeries)
		{
			min = manager.output[i].idleSeries;
		}
	}
	for (int i = 0; i < count - 1; i++)
	{
		manager.output[i].idleSeries -= min;
	}
	manager.input[0].idleSeries += min;

	manager.swap();
	merge(manager);

	/* Записываем результат в файл*/
	manager.swap(); 
	std::fstream result;
	result.open(filename.insert(filename.length() - 4, "(sorted)"), std::ios::out);
	int len = manager.read(0);
	for (int i = 0; i < len; i++)
	{
		result << " " << manager.read(0);
	}
	result.close();
}

void merge(FileManager& manager)
{
	std::multimap <int, int> buffer;				
	int *seriesLen = new int[manager.getInCount()];
	int seriesSum = 2;
	int currentLen;
	int count = manager.getInCount();

	while (seriesSum > 1)
	{
		/* Начальное заполнение буфера */
		currentLen = 0;
		for (int i = 0; i <count; i++)
		{
			if (manager.input[i].idleSeries)
			{
				seriesLen[i] = 0;
				manager.input[i].idleSeries--;
			}
			else
			{
				if (!manager.input[i].numSeries)
				{
					manager.swap(i, 0);
					if (manager.input[i].idleSeries)
					{
						i--;
						continue;
					}
				}
				seriesLen[i] = manager.read(i);
				manager.input[i].numSeries--;
				buffer.insert(std::pair <int, int>(manager.read(i), i));			
			}
			currentLen += seriesLen[i]--;
		}

		manager.write(0, currentLen);
		manager.output[0].numSeries++;

		/* Сливание серии*/
		auto it = buffer.begin();
		while (!buffer.empty())
		{
			it = buffer.begin();
			manager.write(0, it->first);
			if (seriesLen[it->second]--)
			{
				buffer.insert(std::pair <int, int>(manager.read(it->second), it->second));
			}
			buffer.erase(it);
		}

		/* Считаем сумму серий */
		seriesSum = 0;
		for (int i = 0; i < count; i++)
		{
			seriesSum += manager.input[i].numSeries + manager.input[i].idleSeries;
		}
		seriesSum += manager.output[0].numSeries + manager.output[0].idleSeries;

		cout << "Series count: " << seriesSum << endl;
	}
}

void firstDistrib(std::fstream& stream, FileManager&  manager)
{	
	int count = manager.getOutCount();
	Fibonacci fib(count);
	
	int current = 0;
	int len = 0;

	std::streampos startPos, endPos;
	startPos = manager.output[current].file.tellg();
	manager.write(current, 0);

	int* diff = new int[count];
	for (int i = 0; i < count; i++)
	{
		diff[i] = 1;
	}
	diff[0] = 0;

	bool stop = 0;

	int prev = 0, next;
	stream >> next;
	manager.output[current].numSeries++;
	for(;;)
	{
		// Записываем серию 
		while (prev <= next)
		{
			manager.write(current, next);
			len++;
			prev = next;
			if (!stream.eof())
			{
				stream >> next;
			}
			else
			{
				stop = 1;
				break;
			}
		}
		if (stop) break;

		// Дописываем длину серии
		{
			endPos = manager.output[current].file.tellg();
			manager.output[current].file.seekg(startPos);
			manager.write(current, len);
			manager.output[current].file.seekg(endPos);

			// Меняем файл согласно распределению по Фибоначчи 
			if ((current < count - 1) && ((diff[current] + 1) == diff[current + 1]))
			{
				current++;
				diff[current]--;
				manager.output[current].numSeries++;
			}
			else
			{
				if (!diff[count - 1])
				{
					fib.next();
					for (int i = 0; i < count; i++)
					{
						diff[i] = fib.sum[i] - manager.output[i].numSeries;
					}

				}
				current = 0;
				diff[current]--;
				manager.output[current].numSeries++;
			}
			
			// Резервируем место для длины следующей серии
			startPos = manager.output[current].file.tellg();
			manager.write(current, 0);

			// Записываем элемент следующей серии 
			manager.write(current, next);
			len = 1;
			prev = next;
			if (!stream.eof())
			{
				stream >> next;
			}
			else
			{
				break;
			}
		}
	}
	// Дописываем длину серии
	endPos = manager.output[current].file.tellg();
	manager.output[current].file.seekg(startPos);
	manager.write(current, len);
	manager.output[current].file.seekg(endPos);

	// Записываем количество пустых серий
	for (int i = 0; i < count; i++) 
	{
		manager.output[i].idleSeries = diff[i];
	}
}
