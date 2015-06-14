#include <collision.h>
#include <stdio.h>
#include <math.h>

extern float kSpeed;
extern int const kBlockSize;

int collide_circles(float x, float y, float x2, float y2) {
  float dx = x2 - x;
  float dy = y2 - y;
  float distance = sqrt((double) (dx * dx + dy * dy));
  //printf("distance %f\n", distance);
  if (distance < 1.0f - kSpeed / 6.0f) {
    return 1;
  }
  return 0;
}

int collide_player_with_level(player* player, level* level) {
  int x = (player->x) / 1;
  int y = (player->y) / 1;
  float dx = player->x - x;
  float dy = player->y - y;
  //printf("%dx%d %fx%f\n", x, y, dx, dy);
  //printf("x %f, dx %f, x int:  %d\n", player->x, dx, (int) player->x);
  //printf("y %f %d\n", player->y, (int) player->y);

  int collided = 0;
  if (level->level[y][x] == '#') {
    collided += collide_circles(player->x, player->y, x, y);
  }
  if (x - 1 > 0 && level->level[y][x - 1] == '#') {
    collided += collide_circles(player->x, player->y, x - 1, y);
  }
  if (x + 1 < level->w && level->level[y][x + 1] == '#') {
    collided += collide_circles(player->x, player->y, x + 1, y);
  }
  
  if (y - 1 > 0 && level->level[y - 1][x] == '#') {
    collided += collide_circles(player->x, player->y, x, y - 1);
  }
  if (y - 1 > 0 && x - 1 > 0 && level->level[y - 1][x - 1] == '#') {
    collided += collide_circles(player->x, player->y, x - 1, y - 1);
  }
  if (y - 1 > 0 && x + 1 < level->w && level->level[y - 1][x + 1] == '#') {
    collided += collide_circles(player->x, player->y, x + 1, y - 1);
  }

  if (y + 1 < level->h && level->level[y + 1][x] == '#') {
    collided += collide_circles(player->x, player->y, x, y + 1);
  }
  if (y + 1 < level->h && x - 1 > 0 && level->level[y + 1][x - 1] == '#') {
    collided += collide_circles(player->x, player->y, x - 1, y + 1);
  }
  if (y + 1 < level->h && x + 1 < level->w && level->level[y + 1][x + 1] == '#') {
    collided += collide_circles(player->x, player->y, x + 1, y + 1);
  }
  
  return collided;
  if (x > 0) {
    if (level->level[y][x] == '#') {
      if (1.0f - dx < 0.005f)
	return 0;
      return 1;
    }
    if (level->level[y][x - 1] == '#') {
      if (1.0f - dx < 0.005f)
	return 0;
      return 1;
    }
  }
  if (x < level->w) {
    if (level->level[y][x + 1] == '#') {
      if (dx < 0.005f)
	return 0;
      return 1;
    }
  }
  if (y >= 0) {
    if (level->level[y][x] == '#') {
      if (1.0f - dy < 0.005f)
	return 0;
      return 1;
    }
  }
  if (y < level->h) {
    if (level->level[y + 1][x] == '#') {
      if (dy < 0.005f)
	return 0;
      return 1;
    }
  }
     
  //  if (level->level[(int) player->y][(int) player->x] == '#');
  return 0;
}
