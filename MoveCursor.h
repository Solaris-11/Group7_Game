#include <termios.h>
#include <unistd.h>

//Move Cursor Functions
void setNonCanonicalMode();
void restoreTerminalMode();
void clearScreen();
void moveCursorTo(int x, int y);

// Function: setNonCanonicalMode
// Set the terminal to non-canonical mode
void setNonCanonicalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Function: restoreTerminalMode
// Restore the terminal to canonical mode
void restoreTerminalMode() {
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

// Function: clearScreen
// Clear the terminal screen
  void clearScreen() {
    cout << "\033[2J";
}

// Funtion: moveCursorTo
// Move the terminal cursor to the specified position
void moveCursorTo(int x, int y) {
    cout << "\033[" << y << ";" << x << "H";
}
