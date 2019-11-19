// main.cc

#include "endless_runner.h"

int main(int argc, char **argv)
{
   endless_runner game;
   if (!game.init())
      return -1;
   game.run();

   return 0;
}
