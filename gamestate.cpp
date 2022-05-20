#include "gamestate.h"

#include <cstdlib>
#include <ctime>

#include <iostream>

#include <SDL.h>

#include "utilities.h"


extern SDL_Renderer* gRenderer; // Global renderer that handles the drawing

/*
 * ====================================
 * Public methods start here
 * ====================================
 */

GameState::GameState()
{
    board = new Board;
    if (!music->loadAudio()) {
        music->deleteAudio();
        next_state = exit_game;
    }
}

GameState::~GameState()
{
    for (auto i : mButtons)
    {
        delete i;
    }
    delete board;
    //inGamePausestate->~Pausestate();
    delete inGamePausestate;
    music->deleteAudio();
    music = NULL;
    delete music;
    //Mix_CloseAudio();
}

// Stores current block, deletes filled lines and creates a new block.
void GameState::checkState()
{
    board->storePiece(currentPiece);
    int tmp = board->fullLineCleared;
    board->clearFullLines();
    if (board->fullLineCleared > tmp && audioPlayed) {
        music->currentSoundEffect = music->gClear;
        music->playSoundEffect();
    }
    score.update(board->fullLineCleared);
    if (!board->isGameOver())
    {
        createNewPiece();
    }
    hold_block_used = false;
}

void GameState::createNewPiece()
{
    currentPiece.piece_type = nextPiece.piece_type;
    currentPiece.rotation = nextPiece.rotation;
    currentPiece.r = currentPiece.getInitialOffsetR();
    currentPiece.c = config::playfield_width / 2 + currentPiece.getInitialOffsetC();

    for (int i = 0; i < 2; i++)
    {
        currentPiece.r++;
        if (!board->isPositionLegal(currentPiece))
        {
            currentPiece.r--;
        }
    }
    if (currentPiece.piece_type > 1)
    {
        currentPiece.r++;
        if (!board->isPositionLegal(currentPiece))
        {
            currentPiece.r--;
        }
    } // when piece_type isn't I or O its piece will be rendered at row 21

    nextPiece.piece_type = getRandom(0, 6);
    nextPiece.rotation = 0; // Pieces must always start flat according to the offical Tetris guidelines
}

void GameState::drawState()
{
    Texture* background = new Texture();
    background->loadFromImage("assets/background.png");
    background->render(0, 0);
    background->free();
    mButtons.at(pauseButtonIndex)->draw();
    if (audioPlayed) {
        mButtons.at(unmuteButtonIndex)->draw();
    }
    else {
        mButtons.at(muteButtonIndex)->draw();
    }
    drawBoard();
    drawCurrentPiece(currentPiece);
    if (!board->isGameOver() && config::ghost_piece_enabled) drawGhostPiece(currentPiece);
    if (!hold_block_first_time) drawHoldPiece(holdPiece);
    drawNextPiece(nextPiece);
    score.drawCurrentScore();
    score.drawHighestScore();
}

void GameState::handleEvent(Action action)
{
    switch (action)
    {
    case Action::move_down:
    {
        currentPiece.r++;
        if (!board->isPositionLegal(currentPiece))
        {
            currentPiece.r--;
            checkState();
        }
        if (audioPlayed) {
            music->currentSoundEffect = music->gMove;
            music->playSoundEffect();
        }
        break;
    }

    case Action::move_left:
    {
        currentPiece.c--;
        if (!board->isPositionLegal(currentPiece))
        {
            currentPiece.c++;
        }
        if (audioPlayed) {
            music->currentSoundEffect = music->gMove;
            music->playSoundEffect();
        }
        break;
    }

    case Action::move_right:
    {
        currentPiece.c++;
        if (!board->isPositionLegal(currentPiece))
        {
            currentPiece.c--;
        }
        if (audioPlayed) {
            music->currentSoundEffect = music->gMove;
            music->playSoundEffect();
        }
        break;
    }

    case Action::drop:
    {
        while (board->isPositionLegal(currentPiece))
        {
            currentPiece.r++;
        }
        currentPiece.r--;
        checkState();
        if (audioPlayed) {
            music->currentSoundEffect = music->gDrop;
            music->playSoundEffect();
        }
        break;
    }

    case Action::rotate:
    {
        currentPiece.rotation = (currentPiece.rotation + 1) % 4;
        if (!board->isPositionLegal(currentPiece))
        {
            currentPiece.rotation = (currentPiece.rotation + 3) % 4;
        }
        if (audioPlayed) {
            music->currentSoundEffect = music->gRotate;
            music->playSoundEffect();
        }
        break;
    }

    case Action::hold:
    {
        if (hold_block_first_time)
        {
            holdPiece = Piece(currentPiece);
            holdPiece.rotation = 0;
            createNewPiece();
            hold_block_first_time = false;
            hold_block_used = true;
        }
        else if (!hold_block_used)
        {
            swap(currentPiece, holdPiece);
            holdPiece.rotation = 0;
            currentPiece.r = currentPiece.getInitialOffsetR();
            currentPiece.c = config::playfield_width / 2 + currentPiece.getInitialOffsetC();

            for (int i = 0; i < 2; i++)
            {
                currentPiece.r++;
                if (!board->isPositionLegal(currentPiece))
                {
                    currentPiece.r--;
                }
            }
            if (currentPiece.piece_type > 1)
            {
                currentPiece.r++;
                if (!board->isPositionLegal(currentPiece))
                {
                    currentPiece.r--;
                }
            }
            hold_block_used = true;
        }
    }
    }
}

void GameState::initializeState()
{
    srand(time(0));
    hold_block_first_time = true;
    hold_block_used = false;
    // Get random first piece
    nextPiece.piece_type = getRandom(0, 6);
    nextPiece.rotation = 0;                 // Pieces must always start flat according to the offical Tetris guidelines
    createNewPiece();
    nextPiece.r = config::next_box_y;
    nextPiece.c = config::next_box_x;

    // Load necessary textures
    tetrominoSprites.loadFromImage("assets/tetrominoSprites.png");
    playfieldFrame.loadFromImage("assets/playfieldFrame.png");

    mButtons.push_back(new Button("assets/button-pause.png", 5, config::logical_window_height-35));
    mButtons.push_back(new Button("assets/button-unmute.png", 35, config::logical_window_height - 35));
    mButtons.push_back(new Button("assets/button-mute.png", 35, config::logical_window_height - 35));
    // Create the right clips sprites
    for (int i = 0; i < 7; i++)
    {
        tetrominoSpriteClips[i].x = 16 * i;
        tetrominoSpriteClips[i].y = 0;
        tetrominoSpriteClips[i].w = 16;
        tetrominoSpriteClips[i].h = 16;
    }
    for (int i = 0; i < 4; i++)
    {
        playfieldFrameClips[i].x = config::frame_sprite_size * i;
        playfieldFrameClips[i].y = 0;
        playfieldFrameClips[i].w = config::frame_sprite_size;
        playfieldFrameClips[i].h = config::frame_sprite_size;
    }
}

bool GameState::isGameOver()
{
    return board->isGameOver();
}

void GameState::movePieceDown()
{
    currentPiece.r++;
    if (!board->isPositionLegal(currentPiece))
    {
        currentPiece.r--;
        checkState();
    }
}

void GameState::run()
{
    music->playMusic();
    while (next_state == gameplay || next_state == pause) {
        inManager->clearEventQueue();
        renderer.clearScreen();
        drawState();
        renderer.updateScreen();
        SDL_Event event;
        unsigned long long time_snap1 = SDL_GetTicks();
        while (!inManager->isGameExiting() && !isGameOver() && next_state != pause)
        {
            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION) {
                    int tempIndex = -1; // get index of the selected button
                    for (auto i : mButtons) {
                        tempIndex++;
                        i->handleEvent(event);
                        if (i->selected) {
                            switch (tempIndex) {
                            case pauseButtonIndex:
                            {
                                next_state = pause;
                                break;
                            }
                            case unmuteButtonIndex:
                            {
                                audioPlayed = bSwap(audioPlayed);
                                music->pauseOrResumeMusic();
                                break;
                            }
                            }
                            break;
                        }
                    }
                }
                inManager->pollAction(event);
                handleEvent(inManager->getAction());
            }
            unsigned long long time_snap2 = SDL_GetTicks();
            if (time_snap2 - time_snap1 >= score.getCurrentWaitTime())
            {
                movePieceDown();
                time_snap1 = SDL_GetTicks();
            }
            renderer.clearScreen();
            drawState();
            renderer.updateScreen();
        }
        while (next_state==pause) {
            inGamePausestate = new Pausestate;
            next_state = runPausestate();
        }
        if (isGameOver()) {
            if (audioPlayed) {
                music->pauseOrResumeMusic();
                music->currentSoundEffect = music->gGameOver;
                music->playSoundEffect();
            }
            Texture gameover_text;
            gameover_text.loadFromText("GAME OVER!", config::another_text_color);
            Texture* tmp = new Texture;
            tmp->loadFromText("Press a to play again", config::another_text_color);
            Texture* frame = new Texture();
            frame->loadFromImage("assets/frame.png");
            while (!inManager->isGameExiting() && !inManager->isGamePlayedAgain())
            {
                while (SDL_PollEvent(&event) != 0)
                {
                    inManager->pollAction(event);
                }
                renderer.clearScreen();
                drawState();
                frame->renderCentered(config::logical_window_width / 2, config::logical_window_height / 2);
                renderer.renderTexture(&gameover_text, config::logical_window_width / 2, config::logical_window_height / 2 - 20);
                renderer.renderTexture(tmp, config::logical_window_width / 2, config::logical_window_height / 2 + 20);
                renderer.updateScreen();
            }
            tmp->free();
            frame->free();
        }
        if (inManager->isGameExiting()) {
            next_state = exit_game;
        }
        if (inManager->isGamePlayedAgain()) {
            next_state = playagain;
        }
    }
    score.updateData();
}

State GameState::runPausestate()
{
    inGamePausestate->initialize();
    inManager->clearEventQueue();
    while (inGamePausestate->next_state == pause) {
        inGamePausestate->run();
    }
    inGamePausestate->~Pausestate();
    State result = inGamePausestate->next_state;
    inGamePausestate = NULL;
    return result;
}

void GameState::resetPausestate()
{
    inGamePausestate->~Pausestate();
    inGamePausestate = NULL;
    inGamePausestate = new Pausestate;
}

/*
 * ====================================
 * Private methods start here
 * ====================================
 */

void GameState::drawBoard()
{
    for (int i = 0; i < 2 * config::true_playfield_height; i++)
    {
        // Left frame
        playfieldFrame.render(config::width_to_playfield - config::frame_sprite_size, config::height_to_playfield + i * config::frame_sprite_size,
            &playfieldFrameClips[0]);
        // Right frame
        playfieldFrame.render(config::width_to_playfield + config::block_size * config::playfield_width - (config::frame_sprite_size -
            config::frame_width), config::height_to_playfield + i * config::frame_sprite_size, &playfieldFrameClips[0]);
    }
    // Then the 2 corners
    playfieldFrame.render(config::width_to_playfield - config::frame_sprite_size, config::height_to_playfield +
        config::block_size * config::true_playfield_height - (config::frame_sprite_size - config::frame_width), &playfieldFrameClips[2]);
    playfieldFrame.render(config::width_to_playfield + config::block_size * config::playfield_width, config::height_to_playfield +
        config::block_size * config::true_playfield_height - (config::frame_sprite_size - config::frame_width), &playfieldFrameClips[3]);

    for (int i = 0; i < 2 * config::playfield_width; i++)
    {
        // And the bottom frame
        playfieldFrame.render(config::width_to_playfield + i * config::frame_sprite_size, config::height_to_playfield +
            config::block_size * config::true_playfield_height, &playfieldFrameClips[1]);
    }

    // Then draw the placed blocks
    for (int row = 0; row < config::playfield_height; row++)
    {
        for (int col = 0; col < config::playfield_width; col++)
        {
            if (!board->isBlockFree(row, col))
            {
                tetrominoSprites.render(config::width_to_playfield + col * config::block_size, config::height_to_playfield +
                    (row - (config::playfield_height - config::true_playfield_height)) * config::block_size, &tetrominoSpriteClips[board->getTetromino(row, col)]);
            }
        }
    }
}

void GameState::drawCurrentPiece(Piece p)
{
    for (int row = 0; row < config::matrix_blocks; row++)
    {
        for (int col = 0; col < config::matrix_blocks; col++)
        {
            if (p.getBlockType(row, col) != 0)
            {
                tetrominoSprites.render(config::width_to_playfield + (col + p.c) * config::block_size, config::height_to_playfield +
                    (row + p.r - (config::playfield_height - config::true_playfield_height)) * config::block_size, &tetrominoSpriteClips[p.piece_type]);
            }
        }
    }
}

// Draws the ghost piece of the piece given
void GameState::drawGhostPiece(Piece p)
{
    ghostPiece = p;
    while (board->isPositionLegal(ghostPiece))
    {
        ghostPiece.r++;
    }
    ghostPiece.r--;

    tetrominoSprites.setAlphaMode(config::transparency_alpha);  // Change transparency to render the ghost piece

    for (int row = 0; row < config::matrix_blocks; row++)
    {
        for (int col = 0; col < config::matrix_blocks; col++)
        {
            if (ghostPiece.getBlockType(row, col) != 0)
            {
                tetrominoSprites.render(config::width_to_playfield + (col + ghostPiece.c) * config::block_size, config::height_to_playfield +
                    (row + ghostPiece.r - (config::playfield_height - config::true_playfield_height)) * config::block_size, &tetrominoSpriteClips[ghostPiece.piece_type]);
            }
        }
    }

    tetrominoSprites.setAlphaMode(255); // Don't forget to change it back to normal!
}

void GameState::drawHoldPiece(Piece p)
{
    Texture* tmp = new Texture;
    tmp->loadFromText("hold piece", config::default_text_color);
    tmp->render(config::hold_box_x - 10, config::hold_box_y - 25);
    tmp->free();
    for (int row = 0; row < config::matrix_blocks; row++)
    {
        for (int col = 0; col < config::matrix_blocks; col++)
        {
            if (p.getBlockType(row, col) != 0)
            {
                tetrominoSprites.render(config::hold_box_x + col * config::block_size, config::hold_box_y + row * config::block_size,
                    &tetrominoSpriteClips[p.piece_type]);
            }
        }
    }
}

void GameState::drawNextPiece(Piece p)
{
    Texture *tmp = new Texture;
    tmp->loadFromText("next piece", config::default_text_color);
    tmp->render(config::next_box_x - 10, config::next_box_y - 25);
    tmp->free();
    for (int row = 0; row < config::matrix_blocks; row++)
    {
        for (int col = 0; col < config::matrix_blocks; col++)
        {
            if (p.getBlockType(row, col) != 0)
            {
                tetrominoSprites.render(config::next_box_x + col * config::block_size, config::next_box_y + row * config::block_size,
                    &tetrominoSpriteClips[p.piece_type]);
            }
        }
    }
}

int GameState::getRandom(int lower_limit, int upper_limit)
{
    return rand() % (upper_limit - lower_limit + 1) + lower_limit;
}