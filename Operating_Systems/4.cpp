#include<iostream>
#include<cstdlib>
#include<string>
int main(int argc, char* argv[]) {
	if(argc != 2) {
		std::cout << "Usage: fileinfo filename\n";
		exit(1);	
	} else {
		std::string cmd("ls -l ");
		cmd += argv[1];
		const char* command = cmd.c_str();
		std::system(command);
	}
}