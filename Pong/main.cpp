#include "Game.h"

int main() {

	// window initialization

	Game game;

	while (game.running()) {

		// Update delta time
		game.updateDT();
		// Update
		game.update();
		// Render
		game.render(); 

	}


	return 0;
}