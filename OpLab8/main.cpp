#include <iostream>

using namespace std;

void append_to_file(char* filename, char * str); //Додаванн рядку до файлу
char* read_file(FILE * file, int length);//Зчитування файлу
void clear_file(char* filename);//Очищення файлу
int get_file_length(FILE* file);//Довжина файлу
char* get_string_to_write(char * line, int& sum_length);//Отримання рядку, який нам потрібно записати в новий файл

void main() {
	//Створити текстовий файл.Визначити в кожному його рядку кількість слів і довжину найбільшого слова.
	//Дописати значення кількості слів на початок від - повідного рядка, 
	//довжину максимального слова - в його кінець.Вивести вміст вхідного і перетвореного файлів.

    char* source = "source.txt";
	char* dest = "result.txt";
	
	clear_file(dest);

	FILE* file = fopen("source.txt", "r");
	
	int length = get_file_length(file);

	char* str = read_file(file, length);

	cout << "File content: " << str << endl; //Вивід вмісту файлу
	int gen = 0;
	char* line = strtok(str, "\n"); //Розбивання тексту файлу на рядки
	while (line != NULL) {
		int sum_length = 0;
		char* newline = get_string_to_write(line, sum_length);
		append_to_file(dest, newline);

		gen += sum_length + 1;
		
		line = strtok(line + sum_length, "\n");
		
		if (gen > length) 
			break;
	}
	
	fclose(file);
}


void append_to_file(char* filename, char * str){
	FILE * file = fopen(filename, "a");
	fwrite(str, sizeof(char), strlen(str), file);
	fclose(file);
}

char* read_file(FILE * file, int length){
	char* str = new char[length];
	fread(str, sizeof(char), length, file);
	str[length - 1] = '\0';
	return str;
}

void clear_file(char* filename){
	FILE* write = fopen("result.txt", "w");
	fclose(write);
}

int get_file_length(FILE* file){
	fseek(file, 0, SEEK_END);
	int length = ftell(file) - 1;
	fseek(file, 0, SEEK_SET);
	return length;
}

char* get_string_to_write(char * line, int& sum_length){
	char* temp_line = new char[strlen(line) + 1];
	strcpy(temp_line, line);

	char* word = strtok(temp_line, " ");//Розбивання рядку на слова

	int max = 0;
	int count = 0;

	sum_length = 0;
	while (word != NULL){
		if (strlen(word) > max)
			max = strlen(word);

		sum_length += strlen(word);

		word = strtok(NULL, " ");
		count++;
	}

	char* max_str = new char[11];
	char* count_str = new char[11];

	_itoa(max, max_str, 10);
	_itoa(count, count_str, 10);

	char* newline = new char[strlen(line) + strlen(max_str) + strlen(count_str) + 3];//Створення нового рядку
	strcpy(newline, max_str);
	strcat(newline, " ");
	strcat(newline, line);
	strcat(newline, " ");
	strcat(newline, count_str);
	strcat(newline, "\n");


	cout << "Max word: " << max << " Count: " << count << " Line: " << line << endl;

	cout << "New line: " << newline << endl;

	sum_length += count;

	return newline;
}
