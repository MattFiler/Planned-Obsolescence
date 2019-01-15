//
// Created by tobyj on 15/01/2019.
//

#ifndef PLANNEDOBSOLESCENCE_CONSTANTS_H
#define PLANNEDOBSOLESCENCE_CONSTANTS_H
/**
 @brief   Constants that are used throughout the game.
 @details Add any new constants to this file.
*/
// These 2 values should not be changed after development as they represent the
// base size of the game which then gets scaled up for different resolutions
constexpr int BASE_WIDTH = 1280; /**< The base width of the game window */
constexpr int BASE_HEIGHT = 720; /**< The base height of the game window */

constexpr float ASPECT_RATIO = 1.77777778f;
enum SceneName
{
  exit_game = -2,
  dont_change,
  title
};
#endif // PLANNEDOBSOLESCENCE_CONSTANTS_H
