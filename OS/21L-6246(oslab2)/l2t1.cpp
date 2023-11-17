#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    // Check if a filename argument is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1; // Exit with an error code
    }

    // Get the filename from the command-line argument
    std::string filename = argv[1];

    // Attempt to open the file
    std::ifstream file(filename);

    // Check if the file was successfully opened
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return 2; // Exit with an error code
    }

    // Read and print the file contents line by line
    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }

    // Close the file
    file.close();

    return 0; // Exit successfully
}
