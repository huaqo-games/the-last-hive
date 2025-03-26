// initButton(&m->startButton, "Start Game", GetScreenWidth() / 10, GetScreenHeight() / 20, GetScreenWidth() / 2, GetScreenHeight() / 2);
// initButton(&m->quitButton, "Quit Game", GetScreenWidth() / 10, GetScreenHeight() / 20, GetScreenWidth() / 2,
//         GetScreenHeight() / 2 + (GetScreenHeight() / 20 * 2));

// if (isButtonClicked(&m->startButton)) {
//     state->gameStarted = true;
//     m->startButton.text = "Continue";
//     state->currentScreen = GAMEPLAY;
// }
// if (isButtonClicked(&m->quitButton) || (WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))) {
//     state->running = false;
// }

// if (state->gameStarted){
//     if (IsKeyPressed(KEY_ESCAPE)){
//         state->currentScreen = GAMEPLAY;
//     }
// }
// renderButton(&m->startButton);
// renderButton(&m->quitButton);