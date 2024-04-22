#include <iostream>
#include <fstream>
#include <limits> // For numeric_limits

void clearInputBuffer() {
    // Clear the input buffer
    std::cin.clear();
    // Ignore any remaining characters in the input buffer
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void PauseMenu() {
    int choice;
    bool validInput = false;

    while (!validInput) {
        std::cout << "Enter (1) to continue" << std::endl;
        std::cout << "Enter (2) to save and quit" << std::endl;
        std::cout << "Enter (3) to choose another level" << std::endl;
        std::cout << "Enter (4) to restart" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) { // Check if input failed
            std::cout << "Invalid input. Please enter a number between 1 and 4." << std::endl;
            clearInputBuffer(); // Clear input buffer
        } else {
            switch (choice) {
                case 1:
                    std::cout << "Continuing..." << std::endl;
                    validInput = true;
                    break;
                case 2:
                    std::cout << "Saving and quitting..." << std::endl;
                    MainChoose(); 
                    break;
                case 3:
                    std::cout << "Choosing another level..." << std::endl;
                    RunNewGame(); 
                    validInput = true;
                    break;
                case 4:
                    std::cout << "Restarting..." << std::endl;
                    RunNewGame(); 
                    validInput = true;
                    break;
                default:
                    std::cout << "Invalid input. Please enter a number between 1 and 4." << std::endl;
                    break;
            }
        }
    }
}

// Load game function
Setting LoadGame(const std::string& filename) {
    Setting loadedSetting;

    std::ifstream file(filename);
    if (file.is_open()) {
        // Read game settings from file
        file >> loadedSetting.nRows >> loadedSetting.nCols >> loadedSetting.numF;
        file.close();
        std::cout << "Game loaded successfully." << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
        // If unable to open file, initialize default values
        loadedSetting = {0, 0, 0};
    }

    return loadedSetting;
}

// Run load game function
void RunLoadGame() {
    std::string saveFile = "savegame.txt"; // Save file name
    Setting loadedSetting;

    // Load game from save file
    loadedSetting = LoadGame(saveFile);

    // You can use the loaded game settings here
}

int main() {
    PauseMenu();
    return 0;
}
