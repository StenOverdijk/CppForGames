#include <fstream>
#include <iostream>

struct highscore
{
	char name[4];
	uint32_t score;
};

int main()
{
	// Write ascii files.
	{
		std::ofstream highscores("highscores.txt");
		if (!highscores)
		{
			std::cerr << "ERROR: Could not open file for writing." << std::endl;
			return 1;
		}

		highscores << "DOM " << 2026 << std::endl;
		highscores << "LUC " << 1500 << std::endl;
		highscores << "SAM " << 3000 << std::endl;
		highscores << "LIZ " << 2500 << std::endl;
		highscores << "TOM " << 1800 << std::endl;

		if (highscores.bad())
		{
			std::cerr << "ERROR: Could not write to file." << std::endl;
			return 1;
		}

		highscores.close();
		// File is closed automatically when going out of scope.
	}

	{
		std::ofstream highscores("highscores.txt", std::ios::app);
		if (!highscores)
		{
			std::cerr << "ERROR: Could not open file for appending." << std::endl;
			return 1;
		}

		highscores << "ANN " << 2750 << std::endl;

		if (highscores.bad())
		{
			std::cerr << "ERROR: Could not write to file." << std::endl;
			return 1;
		}

		highscores.close();
	}

	{
		std::ifstream highscores("highscores.txt");
		if (!highscores)
		{
			std::cerr << "ERROR: Could not open file for reading." << std::endl;
			return 1;
		}

		char name[4];
 		int score;
		while (highscores >> name >> score)
		{
			std::cout << name << " " << score << std::endl;
		}

		if (highscores.bad())
		{
			std::cerr << "ERROR: Could not read from file." << std::endl;
			return 1;
		}

		highscores.close();
		// File is closed automatically when going out of scope.z
	}

	// Writing binary files
	{
		std::ofstream highscores("highscores.bin", std::ios::binary);
		if (!highscores)
		{
			std::cerr << "ERROR: Failed to write to file." << std::endl;
			return 1;
		}

		highscore scores[] = {
			{"JER", 2026},
			{"BAS", 1500},
			{"DAN", 3000},
			{"DON", 2500},
			{"RON", 1800}
		};
		auto numScores = std::size(scores);

		highscores.write(reinterpret_cast<const char*>(&numScores), sizeof(numScores));
		highscores.write(reinterpret_cast<const char*>(scores), numScores * sizeof(highscore));

		if (highscores.bad())
		{
			std::cerr << "ERROR: Failed to write to file." << std::endl;
			return 1;
		}

		highscores.close();
	}

	{
		std::ifstream highscores("highscores.bin", std::ios::binary);
		if (!highscores)
		{
			std::cerr << "ERROR: Failed to open file." << std::endl;
			return 1;
		}

		size_t numEntries;
		highscores.read(reinterpret_cast<char*>(&numEntries), sizeof(numEntries));

		highscore* scores = new highscore[numEntries];

		highscores.read(reinterpret_cast<char*>(scores), numEntries * sizeof(highscore));

		if (highscores.bad())
		{
			std::cerr << "ERROR: Failed to open file." << std::endl;
			return 1;
		}

		for (int i = 0; i < numEntries; ++i)
		{
			std::cout << scores[i].name << " " << scores[i].score << std::endl;
		}

		delete[] scores;

		highscores.close(); // return any system resources
	}

	return 0;
}