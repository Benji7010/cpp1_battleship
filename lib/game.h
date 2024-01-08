#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "consts.h"

class BaseGame {
protected:
  Board * board;
  virtual int solve() = 0;
public:
  BaseGame();
  ~BaseGame();
  int run();
};


class ControlGame : public BaseGame {
protected:
    int solve() override {
        int hits = 0;
        for(int i = 0; i < HEIGHT; i++)
        {
            for(int j = 0; j < WIDTH; j++)
            {
                if(this->board->guess(i, j) == ResponseType::HIT)
                {
                    hits += 1;
                }
            }
        }
        return hits;
    }
};

class AssignmentGame : public BaseGame {
  protected:
      
      bool checked[100][100] = { false };
      int hits = 0;

      int solve() override {
            //IMPLEMENT YOUR SEARCH ALGORITHM HERE
            
            //Use this variable to store a responce whenever you are checking a guess for more than one responce type.
            ResponseType responce = ResponseType::MISS;
            for(int i = 0; i < HEIGHT; i++)
            {
                for(int j = 0; j < WIDTH; j++)
                {
                    responce = memGuess(i, j);
                    if(responce == ResponseType::NEARMISS)
                    {
                        //This can be optimised as a method that calls itself whenever it gets a near miss.
                        //Not sure that has_adjacent works like I think it does.
                        if(i != 99)
                        {
                            if (memGuess(i + 1, j) == ResponseType::HIT) { hits += 1; }
                        }
                        if(j != 99)
                        {
                            if(memGuess(i, j + 1) == ResponseType::HIT) { hits += 1; }
                        }
                        if(i != 0)
                        {
                            if(memGuess(i - 1, j) == ResponseType::HIT) { hits += 1; }
                        }
                        if(j != 0)
                        {
                            if(memGuess(i, j - 1) == ResponseType::HIT) { hits += 1; }
                        }
                        //Diagonals
                        if (i != 99 && j != 99)
                        {
                            if (memGuess(i + 1, j + 1) == ResponseType::HIT) { hits += 1; }
                        }
                        if (i != 0 && j != 99)
                        {
                            if (memGuess(i - 1, j + 1) == ResponseType::HIT) { hits += 1; }
                        }
                        if (i != 99 && j != 0)
                        {
                            if (memGuess(i + 1, j - 1) == ResponseType::HIT) { hits += 1; }
                        }
                        if (i != 0 && j != 0)
                        {
                            if (memGuess(i - 1, j - 1) == ResponseType::HIT) { hits += 1; }
                        }
                    }
                    else if(responce == ResponseType::HIT)
                    {
                        hits += 1;
                    }
                }
            }
            return hits;
      }

      ///Runs the guess, but checks and records if the tile was checked already.
      ResponseType memGuess(int i, int j) {
          //Prevents the compiler from getting mad at me.
          ResponseType responce = ResponseType::MISS;
          if (checked[i][j] == false && hits < SHIP_COUNT)
          {
              checked[i][j] = true;
              responce = this->board->guess(i, j);
          }
          return responce;
      }
};


#endif /* GAME_H */
