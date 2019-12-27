#include<iostream>
#include<Eigen/Dense>
#include <stdlib.h>
#include <unistd.h>

using namespace Eigen;

//The size of the game
#define num 20

//Define functions
MatrixXd create_world();
MatrixXd update_augments(MatrixXd world);
MatrixXd update_world(MatrixXd world);

//Main function
int main(int argc, char const *argv[]) {
  MatrixXd world(num+2,num+2);
  world = create_world();
  //Print only num x num
  // std::cout<<world.block<num,num>(1,1)<<std::endl;
  MatrixXd updated_augments(num+2,num+2);
  // updated_augments = update_augments(world);
  // std::cout<<updated_augments.block<num,num>(1,1)<<"\n"<<std::endl;
  // std::cout<<updated_augments<<"\n"<<std::endl;

  MatrixXd updated_world(num+2,num+2);
  // updated_world = update_world(updated_augments);
  // std::cout<<updated_world.block<num,num>(1,1)<<std::endl;
  updated_world = world;
  for (size_t count = 0; count < 100; count++) {
    updated_augments = update_augments(updated_world);
    updated_world = update_world(updated_augments);
    std::cout<<updated_world.block<num,num>(1,1)<<std::endl;
    usleep(200000);
    system("clear");
  }

  return 0;
}

//Function definition
//Create a new world
MatrixXd create_world(){
  //Create empty world
  MatrixXd world(num+2,num+2);
  world = MatrixXd::Zero(num+2,num+2);
  // std::cout<<world<<std::endl;
  //Initiate new world definition
  //Initiating this world with a glider
  world(2,1) = 1;
  world(3,2) = 1;
  world(3,3) = 1;
  world(1,3) = 1;
  world(2,3) = 1;
  // world(1,num) = 1;
  // world(num,1) = 1;
  return world;
}

//Update the augmented part of the world
MatrixXd update_augments(MatrixXd world){
  //First augment the matrix with edge values
  //Setting the right-most edge
  world.block<num,1>(1,num+1) = world.block<num,1>(1,1);
  //Setting the left-most edge
  world.block<num,1>(1,0) = world.block<num,1>(1,num);
  //Setting the upper-most edge
  world.block<1,num>(0,1) = world.block<1,num>(num,1);
  //Setting the lower-most edge
  world.block<1,num>(num+1,1) = world.block<1,num>(1,1);

  return world;
}

//Update the world
MatrixXd update_world(MatrixXd world){
  MatrixXd updated_world(num+2,num+2);
  //Initiating with the previous world
  updated_world = world;
  //Rules of game of life
  for (size_t i = 1; i <= num; i++) {
    for (size_t j = 1; j <= num; j++) {
      //Rule 1
      int n = 0;
      n = world(i-1,j-1) + world(i-1,j) + world(i-1,j+1) + world(i,j-1) + world(i,j+1)\
       + world(i+1,j-1) + world(i+1,j) + world(i+1,j+1);
       //Under-population
      if (n<2) updated_world(i,j) = 0;
      //Over-population
      else if (n==2) updated_world(i,j) = world(i,j);
      else if (n>3) updated_world(i,j) = 0;
      else if (n==3) updated_world(i,j) = 1;
    }
  }
  return updated_world;
}
