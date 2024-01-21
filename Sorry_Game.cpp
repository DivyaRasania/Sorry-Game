/* Program name: Sorry_Game.cpp
*  Authors: Divya Rasania, Elaina Baker, Cheyanne Aubri Anderson
*  Authors responsibilities:
*       Elaina Baker: 1-7 on instructions
*       Divya Rasania: 8-15 on instructions
*       Cheyanne Aubri Anderson: Extra credit, testing, and user guide
*  Date last updated: 05/04/2023
*  Purpose: Play the game of Sorry
*/

#include <QtGui>

int main() {
    // Create a new application object
    QApplication app(argc, argv);

    // Create a new window
    QWidget window;

    // Add a label to the window
    QLabel label("Sorry");
    label.setGeometry(100, 100, 100, 30);
    window.addWidget(&label);

    // Add a button to the window
    QPushButton button("Roll Dice");
    button.setGeometry(200, 100, 100, 30);
    window.addWidget(&button);

    // Connect the button to the code
    connect(&button, SIGNAL(clicked()), this, SLOT(on_button_clicked()));

    // Show the window
    window.show();

    // Run the application
    return app.exec();
}

void on_button_clicked() {
    // Get the number of players
    int numPlayers;
    QInputDialog inputDialog("Number of Players", "Please enter the number of players (2-4): ", 2, 4);
    if (inputDialog.exec() == QDialog::Accepted) {
        numPlayers = inputDialog.value();
    }
    else {
        return;
    }

    // Create an array to track the player's positions on the playing board
    int playPosition[numPlayers];

    // The playing board has 50 spaces (with 50 being the winning space)
    int boardSpaces[50];

    // Set the player's positions to 0
    for (int i = 0; i < numPlayers; i++) {
        playPosition[i] = 0;
    }

    // Roll the dice
    int dice1 = randomNum();
    int dice2 = randomNum();

    // Display the dice rolls
    QMessageBox messageBox("Dice Rolls", QString("You rolled %1 and %2").arg(dice1).arg(dice2));
    messageBox.exec();

    // Move the players' pieces
    for (int i = 0; i < numPlayers; i++) {
        playPosition[i] += dice1 + dice2;
        if (playPosition[i] > 50) {
            playPosition[i] -= 50;
        }
    }

    // Display the players' positions
    QMessageBox messageBox("Player Positions", QString("Player 1 is on space %1, Player 2 is on space %2, Player 3 is on space %3, and Player 4 is on space %4").arg(playPosition[0]).arg(playPosition[1]).arg(playPosition[2]).arg(playPosition[3]));
    messageBox.exec();

    // Check for a winner
    int winner = -1;
    for (int i = 0; i < numPlayers; i++) {
        if (playPosition[i] == 50) {
            winner = i;
            break;
        }
    }

    // Display the winner
    if (winner != -1) {
        QMessageBox messageBox("Winner!", QString("Player %1 has won!").arg(winner + 1));
        messageBox.exec();
    }
}

int randomNum() {
    srand(time(NULL));
    return rand() % 12 + 2;
}
