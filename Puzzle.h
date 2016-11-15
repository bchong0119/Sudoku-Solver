#ifndef PUZZLE_H
#define PUZZLE_H

#include<iostream> 
#include<vector>
#include<string>
#include<cstring>
#include<fstream>

using namespace std;

template<typename T>
class Puzzle {

   public: 
      Puzzle();       //default constructor
      void disp();    //displays current board
      int validpos(int, int);
      int validvalue(int, int, T);
      int completed();
      int box(int, int);
      void place();
      void play();
      void solver();
      int searchunique(T, vector<T>);
      int searchwithinbox(int, int, int, int);
      void clear3D();

   private: 
      vector<vector<T> > board; 
      vector<vector<T> > origboard;
      vector<vector<vector<T> > > possvals;
};

#endif

template<typename T>
Puzzle<T>::Puzzle() {  //default constructor that takes in a file input and sets up vector array for that puzzle

   string name="";
   T tmp;
   int row=0, col=0;

   cout << "Enter a sudoku puzzle file name: " << endl;
   cin >> name;

   ifstream file (name.c_str());

   while (file.is_open()==0) {
      cout << "Unable to open file, enter a new file name:" << endl;
      cin >> name;
      file.open(name.c_str());
   }
   
   //after checking that file exists and is open
   //set up vectors
   possvals.resize(9);
   for (row=0; row<9; row++) {
      board.push_back(vector<T>());
      origboard.push_back(vector<T>());
      possvals[row].resize(9);
      for (col=0; col<9; col++) {
         file >> tmp;
         board[row].push_back(tmp);
	 origboard[row].push_back(tmp);
	 possvals[row][col].resize(9);
      }
   }
}

template<typename T>
void Puzzle<T>::disp() {

   int row, col;

   cout << "  ------SUDOKU------" << endl;
   cout << "  1 2 3 4 5 6 7 8 9" << endl;
   cout << "  _________________" << endl;

   for (row=0; row<9; row++) {
      for (col=0; col<9; col++) { 
	 if (col==0) {
	    cout << row+1 << "|";
	 }
	 if (col%3==2 && col!=0) {
   	    cout << board[row][col];
	    cout << "|";
	 }
	 else {
  	    cout << board[row][col] << " ";
	 }
      }
      if (row%3==2) {
	 cout << endl << "  ----- ----- -----";
      }
      cout << endl;
   }

}


//returns 1 if win, 0 if not win
template<typename T>
int Puzzle<T>::completed() {

   int row, col;

   for (row=0; row<9; row++) {
      for (col=0; col<9; col++) {
         if (validvalue(row, col, board[row][col])==0) {
	    return 0;
	 }
      }
   }

   return 1;

}

//determines if a certain block is a valid position, 1=valid, 0=invalid
template<typename T> 
int Puzzle<T>::validpos(int r, int c) {

   //check if row and col values are within the correct range
   if (r<0 || r>8) { 
      return 0;
   }
   if (c<0 || c>8) {
      return 0;
   }

   //check if space is part of original or not
   //need a copy of the original board and compare
   if (origboard[r][c]!=0) {
      return 0;
   }
   else {
      return 1;
   }

}

//checks if a certain value can go in that position
//returns 1 if valid, 0 if not valid
template<typename T>
int Puzzle<T>::validvalue(int r, int c, T value) {

   int row, col, b;

   if (value>9 || value<1) {
      return 0;
   }

   //only need to check for that value
   //check within rows
   for (row=0; row<9; row++) {
      if (board[row][c]==value && r!=row) {
	 return 0;
      }
   }

   //check withing cols
   for (col=0; col<9; col++) {
      if (board[r][col]==value && c!=col) {
	 return 0;
      }
   }
   
   //check within 3X3 boxes
   b=box(r, c);
   switch (b) {
      case 1: 
	 for (row=0; row<=2; row++) {
	    for (col=0; col<=2; col++) {
	       if (board[row][col]==value && row!=r && col!=c) {
		  return 0;
	       }
	    }
	 }
	 break;
      case 2:
	 for (row=0; row<=2; row++) {
	    for (col=3; col<=5; col++) {
	       if (board[row][col]==value && row!=r && col!=c) {
		  return 0;
	       }
	    }
	 }
	 break;
      case 3:
	 for (row=0; row<=2; row++) {
	    for (col=6; col<=8; col++) {
	       if (board[row][col]==value && row!=r && col!=c) {
		  return 0;
	       }
	    }
	 }
	 break;
      case 4:
	 for (row=3; row<=5; row++) {
	    for (col=0; col<=2; col++) {
	       if (board[row][col]==value && row!=r && col!=c) {
		  return 0;
	       }
	    }
	 }
	 break;
      case 5: 
         for (row=3; row<=5; row++) {
	    for (col=3; col<=5; col++) {
	       if (board[row][col]==value && row!=r && col!=c) {
		  return 0;
	       }
	    }
	 }
	 break;
      case 6:
         for (row=3; row<=5; row++) {
	    for (col=6; col<=8; col++) {
	       if (board[row][col]==value && row!=r && col!=c) {
		  return 0;
	       }
	    }
	 }
	 break;
      case 7: 
         for (row=6; row<=8; row++) {
	    for (col=0; col<=2; col++) {
	       if (board[row][col]==value && row!=r && col!=c) {
		  return 0;
	       }
	    }
	 }
	 break;
      case 8:
         for (row=6; row<=8; row++) {
	    for (col=3; col<=5; col++) {
	       if (board[row][col]==value && row!=r && col!=c) {
		  return 0;
	       }
	    }
	 }
	 break;
      case 9: 
         for (row=6; row<=8; row++) {
	    for (col=6; col<=8; col++) {
	       if (board[row][col]==value && row!=r && col!=c) {
		  return 0;
	       }
	    }
	 }
	 break;
   }

   return 1;

}

//return what box piece is in            box order:
template<typename T>			// 1  2  3  
int Puzzle<T>::box(int r, int c) {      // 4  5  6
   					// 7  8  9
   if (r<=2 && c<=2) {
      return 1;
   }
   if (r<=2 && c<=5 && c>=3) {
      return 2;
   }
   if (r<=2 && c<=8 && c>=6) {
      return 3;
   }
   if (r<=5 && r>=3 && c<=2) {
      return 4;
   }
   if (r<=5 && r>=3 && c<=5 && c>=3) {
      return 5;
   }
   if (r<=5 && r>=3 && c<=8 && c>=6) {
      return 6;
   }
   if (r>=6 && c<=2) {
      return 7;
   }
   if (r>=6 && c<=5 && c>=3) {
      return 8;
   }
   if (r>=6 && c<=8 && c>=6) {
      return 9;
   }

}

//places value onto board and redisplays board
template<typename T>
void Puzzle<T>::place() {

   int row, col;
   T piece;

   //ask for user input row and col
   cout << "Enter a row and column to enter a new value: " << endl;
   cout << "Row: ";
   cin >> row;
   cout << "Col: ";
   cin >> col;
   row-=1;
   col-=1;

   //check if position is valid
   while (validpos(row, col)==0) {
      cout << "This space is invalid. Try again:" << endl;
      cout << "Row: ";
      cin >> row;
      cout << "Col: ";
      cin >> col;
      row-=1;
      col-=1;

   }

   //place piece and check if input is valid
   cout << "What value would you like to enter here?" << endl;
   cin >> piece;
   while (validvalue(row, col, piece)==0) {
      cout << "Invalid value. Try again: " << endl; 
      cin >> piece; 
   }

   board[row][col]=piece;

}

template<typename T>
void Puzzle<T>::play() {

   //initial display
   disp();

   while (completed()==0) {
      //place piece
      place();
      //display board after placing piece
      disp();
   }

}

template<typename T> 
void Puzzle<T>::solver() {

   int row, col, val, u, i, j, change;
   
   while (completed()==0) {

      //if this value is still 0 at the end, then no value has been changed and solver cannot solve
      change=0;

      //fill in possvals 3D array with possible values
      for (row=0; row<9; row++) {
	 for (col=0; col<9; col++) {
	    j=0;
	    for (val=1; val<=9; val++) {
	       if (validpos(row, col)==1 && validvalue(row, col, val)==1 && board[row][col]==0) {
		  possvals[row][col][j]=val;
		  j++;
	       }
	    }
	 }
      }

      //if only one possible value for the space, change value
      for (row=0; row<9; row++) {
	 for (col=0; col<9; col++) {
	    if (possvals[row][col][1]==0 && possvals[row][col][0]!=0) {
	       board[row][col]=possvals[row][col][0];
	       change=1;
	       col=10; row=10;
	    }
	 }
      }

      if (change==1) {
	 clear3D();
	 continue;
      }

      //singleton method
      //for a row
      vector<T> Row;
      for (row=0; row<9; row++) {
	 for (col=0; col<9; col++) {
	    for (val=0; val<possvals[row][col].size(); val++) {
	       Row.push_back(possvals[row][col][val]);
	    }
	 }
	 //iterate through Row vector to search for unique values
	 for (i=0; i<Row.size(); i++) {
	    //if val is unique, find which col it is in and place on board
	    u=searchunique(Row[i], Row);
	    if (u==1) {
	       for (col=0; col<9; col++) {
		  for (val=0; val<possvals[row][col].size(); val++) {
		     if (possvals[row][col][val]==Row[i]) {
			board[row][col]=possvals[row][col][val];
			change=1;
			val=10; row=10; col=10; i=10;
			Row.clear();
		     }
		  }
	       }
	    }
	 }
	 //clear current row for next row
	 Row.clear();
      }

      if (change==1) {
	 clear3D();
	 continue;
      }

      //for a col
      vector<T> Col;
      for (col=0; col<9; col++) {
	 for (row=0; row<9; row++) {
	    for (val=0; val<possvals[row][col].size(); val++) {
	       Col.push_back(possvals[row][col][val]);
	    }
	 }
	 //iterate through Col vector to search for unique values
	 for (i=0; i<Col.size(); i++) {
	    //if val is unique, find which row it is in and place on board
	    u=searchunique(Col[i], Col);
	    if (u==1) {
	       for (row=0; row<9; row++) {
		  for (val=0; val<possvals[row][col].size(); val++) {
		     if (possvals[row][col][val]==Col[i]) {
			board[row][col]=possvals[row][col][val];
			change=1;
			val=10; row=10; col=10; i=10;
			Col.clear();
		     }
		  }
	       }
	    }
	 }
	 //clear current row for next row
	 Col.clear();
      }

      if (change==1) {
	 clear3D();
	 continue;
      }

      //for each 3x3 box
      if (searchwithinbox(0,2,0,2)==1) {
	 clear3D();
	 continue;
      }
      if (searchwithinbox(3,5,0,2)==1) {
	 clear3D();
	 continue;
      }

      if (searchwithinbox(6,8,0,2)==1) {
	 clear3D();
	 continue;
      }

      if (searchwithinbox(0,2,3,5)==1) {
	 clear3D();
	 continue;
      }

      if (searchwithinbox(3,5,3,5)==1) {
	 clear3D();
	 continue;
      }

      if (searchwithinbox(6,8,3,5)==1) {
	 clear3D();
	 continue;
      }

      if (searchwithinbox(0,2,6,8)==1) {
	 clear3D();
	 continue;
      }

      if (searchwithinbox(3,5,6,8)==1) {
	 clear3D();
	 continue;
      }

      if (searchwithinbox(6,8,6,8)==1) {
	 clear3D();
	 continue;
      }

      //if nothing has been changed, no more possible moves, break
      if (change==0) {
	 break;
      }

   }
   //after finishing, display board
   if (completed()==0) {
      cout << "Puzzle could not be completed" << endl;
   }
   else {
      cout << "Puzzle has been completed!" << endl;
   }

   disp();

}

//returns 1 if value has been changed, else returns 0
template <typename T>
int Puzzle<T>::searchwithinbox(int minr, int maxr, int minc, int maxc) { 

   int row, col, i, u, val;
   int change=0;
   vector<T> box;

   for (row=minr; row<=maxr; row++) {
      for (col=minc; col<=maxc; col++) {
	 for (val=0; val<possvals[row][col].size(); val++) {
	    box.push_back(possvals[row][col][val]);
	 }
      }
   }
   //iterate through Col vector to search for unique values
   for (i=0; i<box.size(); i++) {
      //if val is unique, find which position it is in and place on board
      u=searchunique(box[i], box);
      if (u==1) {
	 for (row=minr; row<=maxr; row++) {
	    for (col=minc; col<=maxc; col++) {
	       for (val=0; val<possvals[row][col].size(); val++) {
		  if (possvals[row][col][val]==box[i]) {
		     board[row][col]=possvals[row][col][val];
		     change=1;
		     row=10; col=10; val=10; i=10;
		  }
	       }
	    }
	 }
      }
   }
   //clear current box for next box
   box.clear();

   return change;
}


template <typename T>
int Puzzle<T>::searchunique(T value, vector<T> vect) {
   //this function goes through a vector to check if a value is unique
   //0 means not unique, 1 means unique
   int val;
   int uniq=0;

   for(val=0; val<vect.size(); val++) {
      if (vect[val]==value) {
	 uniq++;
      }
      if (uniq>1) {
	 return 0;
      }
   }

   return 1;

}

template <typename T>
void Puzzle<T>::clear3D() {

   int row, col;

   //clear possvals array for next iteration
   for (row=0; row<9; row++) {
      for (col=0; col<9; col++) {
	 possvals[row][col].clear();
      }
   }

   //remake possvals array for next iteration
   possvals.resize(9);
   for (row=0; row<9; row++) {
      possvals[row].resize(9);
      for (col=0; col<9; col++) {
	 possvals[row][col].resize(9);
      }
   }

}

