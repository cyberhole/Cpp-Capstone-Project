#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include <sstream>
#include <fstream>

#define scorePath "../src/score.txt"


std::string ReadHighScore (std::string path){
  std::ifstream myfile;
  myfile.open(path);
  std::string line;
    if (myfile.is_open()){
     getline(myfile,line);
     std::cout<<"Previous high score is: "<<line<<"\n";
     myfile.close();
     return line;
     }
     else 
     std::cout<<"Unable to open file"<<"\n";
}

void WriteHighScore (int highScore,std::string path){
  std::ofstream myfile;
  myfile.open(path);
  std::string line;
    if (myfile.is_open()){
     myfile<<highScore;
     std::cout<<"Congratulations on your new score!!!"<<"\n";
     myfile.close();
     }
     else 
     std::cout<<"Unable to open file"<<"\n";
}



int main() {

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

int highScore {0};
try {
highScore=stoi(ReadHighScore(scorePath));
}
catch(...){
highScore=0;
}

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame,highScore);


  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";

if (highScore<game.GetScore())
WriteHighScore (game.GetScore(),scorePath);
return 0;
}