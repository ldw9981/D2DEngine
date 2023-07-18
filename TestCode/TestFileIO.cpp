#include "TestFileIO.h"


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>

struct Person {
	char name[50];
	int age;
	float height;
};
int Test_C_FileIO_Binary() {
	// Example data to write to the file
	struct Person person1 = { "John Doe", 30, 5.9 };
	// Writing binary data to a file
	FILE* fileWrite;
	if (fopen_s(&fileWrite, "data.bin", "wb") != 0) {
		printf("Error opening file for writing.\n");
		return 1;
	}
	// Write the data to the file
	fwrite(&person1, sizeof(struct Person), 1, fileWrite);
	// Close the file
	fclose(fileWrite);
	// Reading binary data from the file
	struct Person person2;
	FILE* fileRead;
	if (fopen_s(&fileRead, "data.bin", "rb") != 0) {
		printf("Error opening file for reading.\n");
		return 1;
	}
	// Read the data from the file
	fread(&person2, sizeof(struct Person), 1, fileRead);
	// Close the file
	fclose(fileRead);
	// Display the data read from the file
	printf("Name: %s\n", person2.name);
	printf("Age: %d\n", person2.age);
	printf("Height: %f\n", person2.height);
	return 0;
}



int Test_C_FileIO_Text() 
{
	// Writing text data to a file
	FILE* fileWrite;
	if (fopen_s(&fileWrite, "data.txt", "w") != 0) {
		printf("Error opening file for writing.\n");
		return 1;
	}

	// Write data to the file
	fprintf(fileWrite, "Hello, this is a text file.\n");
	fprintf(fileWrite, "You can write multiple lines.\n");
	fprintf(fileWrite, "And even format data: %d, %f, %s\n", 42, 3.14, "text");

	// Close the file
	fclose(fileWrite);

	// Reading text data from the file
	char buffer[256];

	FILE* fileRead;
	if (fopen_s(&fileRead, "data.txt", "r") != 0) {
		printf("Error opening file for reading.\n");
		return 1;
	}

	// Read data from the file
	while (fgets(buffer, sizeof(buffer), fileRead) != NULL) {
		printf("%s", buffer); // Print each line to the console
	}

	// Close the file
	fclose(fileRead);

	return 0;
}

struct PersonCPP {
	char name[50];
	int age;
	float height;
};

void Test_CPP_writeBinaryFile() {
	// Example data to write to the file
	PersonCPP person1;
	strcpy_s(person1.name, "John Doe");
	person1.age = 30;
	person1.height = 5.9f;

	// Writing binary data to a file
	std::ofstream fileWrite("data.bin", std::ios::binary);
	if (!fileWrite) {
		std::cout << "Error opening file for writing.\n";
		return;
	}

	// Write the data to the file
	fileWrite.write(reinterpret_cast<char*>(&person1), sizeof(PersonCPP));

	// Close the file (done automatically when the ofstream object goes out of scope)
}

void Test_CPP_readBinaryFile() {
	// Reading binary data from the file
	PersonCPP person2;

	std::ifstream fileRead("data.bin", std::ios::binary);
	if (!fileRead) {
		std::cout << "Error opening file for reading.\n";
		return;
	}

	// Read the data from the file
	fileRead.read(reinterpret_cast<char*>(&person2), sizeof(PersonCPP));

	// Close the file (done automatically when the ifstream object goes out of scope)

	// Display the data read from the file
	std::cout << "Name: " << person2.name << std::endl;
	std::cout << "Age: " << person2.age << std::endl;
	std::cout << "Height: " << person2.height << std::endl;
}