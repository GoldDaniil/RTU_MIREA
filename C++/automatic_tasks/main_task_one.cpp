//The program "Life", (describing the life of microorganisms)
//Introduction
//Once upon a time there were microbes.They lived happily ever after, but here's the trouble:
//death always comes after life.And the microbes were different : small and not so small, old men and babies – and
//each of them had their own standard of living.So, for example, a newly born
//the microbe was equal to 1, and as he grew up, the standard of living also grew(from 1
//	up to 12).When the microbe reached the last stage(i.e. 12), it, alas, died(now
//		its standard of living is 0).If the microbe's level was equal to 0, then it was born
//	anew and went through life again with a brisk step from 1 to 12.
//	In total, there are a lot of microbes in the world, as you know, and their life is interesting.Therefore
//	, the idea came up to write a program describing their life.This program should
//	tell us the number of microbes in each generation and "draw" them on the field
//	(on the screen).
//	The program should work as follows.
//	1. First, a work.dat file(microbes' home) and a work.out file (describing
//		the current generation of microbes, their development) are created.The work.dat file consists of various
//	symbols, among which microbes "live".
//	2. It is necessary to create arrays "present" and "future".The
//	current generation of microbes is recorded in the "present" array, and the next generation is recorded in the "future" file.Arrays
//	are created with a size of 21x21.
//	3. The program prompts the user on the screen : "Enter the number of generations."
//	That's how many generations the program will describe.
//	4. Now the program creates a generation number 1 in the work.out file.To do this
//	, the program opens and checks for the presence of microbes in the file(each character, among
//		which a microbe can get lost).If a microbe is hidden under the symbol(for example,
//			the symbol "X"), then one is written to the array "present" (1, i.e.a microbe has just been
//				born), and if not a microbe, then zero(0, i.e.no one lives there).Now in the array
//	The "present" is a field of 1 and 0 (it consists of newborn babies and
//		empty spaces).All subsequent generations are also written to the work.out file.
//	The work.dat file is being closed, and work is now being done only with the work.out.
//	5 file.Now the next generation is being described.It is created after checking the array
//	"the present." Microbes and their neighbors are checked(the result is recorded in
//		the "future" array) :
//	-if the life level of the microbe is from 1 to 11 then :
//	--if there are 2 or 3 neighbors, then the microbe continues to live and grows(i.e.its standard
//		of living increases by 1),
//	--otherwise, the microbe dies(= 0), because it suffocates or dies of boredom;
//-if the life level of the microbe is 0, then the microbe is born again(i.e.its life
//	level is 1);
//-if the life level of the microbe is 12, then the microbe dies(from
//	old age).
//	6. After checking, the number of lives of this generation is calculated(i.e., how
//		many units).Then the program checks if anyone is "alive on the field" or if everyone is dead
//		(i.e.zeros).
//	7. Now the program replaces generations : the array "future" becomes
//	"present"

#include<iostream>
#include<fstream>

using namespace std;

const int size = 21;
const int max_life_level = 12;

//int** generation = new int* [size];
//for (int i = 0; i < size; ++i) {
//}

void display_generation(int generation[size][size]) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			cout << (generation[i][j] == 0 ? "." : to_string(generation[i][j]));
		}
		cout << endl;
	}

}

void generate_next_generation(int current[size][size], int next[size][size]) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (current[i][j] > 0 && current[i][j] < max_life_level) {
				int neighbors = 0;
				for (int x = -1; x <= 1; ++x) {
					for (int y = -1; y <= 1; ++y) {
						int ni = i + x;
						int nj = j + y;

						if (ni >= 0 && ni < size && nj >= 0; nj < size && !()) {
							neighbors += (current[ni][nj] > 0 && current[ni][nj] < max_life_level);
						}
					}
				}

				if (neighbors == 2 || neighbors == 3) {
					next[i][j] == current[i][j] + 1;
				}
				else {
					next[i][j] = 0;
				}
			}
			else if (current[i][j]) {
				next[i][j] = 1;
			}
			else if (current[i][j] == max_life_level) {
				next[i][j] = 0;
			}
		}
	}
}

int count_living_cells(int generation[size][size]) {
	int count = 0;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			count += (generation[i][j] > 0 && generation[i][j] < max_life_level);
		}
	}
	return count;
}

void initialize_generation_from_file(ifstream& file, int generation[size][size]) {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (current[i][j] > 0 && current[i][j] < max_life_level) {
				int neighbors = 0;
				
				for (int x = -1; x <= -1; ++x) {
					for (int y = -1; y <= -1; ++y) {

					}
				}

			}
		}

	}


}
