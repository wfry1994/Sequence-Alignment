
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>
using namespace std;
int max(int num1,int num2);
int min(int num1,int num2);
void sequenceAlign(int numRows,int numColumn,vector<string>& stringInputVector);
string getUserInput();
bool checkMisMatchCase(char letter1,char letter2);
bool checkVowelCase(char letter1,char letter2);
int main()
{
vector<string> stringInputVector;
stringInputVector.push_back(getUserInput());
stringInputVector.push_back(getUserInput());
int numRows = max(stringInputVector[0].length(),stringInputVector[1].length());
int numColumn = min(stringInputVector[0].length(),stringInputVector[1].length());
sequenceAlign(numRows,numColumn,stringInputVector);


return 0;
}

void sequenceAlign(int numRows,int numColumn,vector<string>& stringInputVector)
{
  int sequenceMatrix[numRows+1][numColumn+1];
  int indexOfLargestString;  
  int indexOfSmallestString;
  int row = 1;
  int column = 1;
  vector<char> alignedString1;
  vector<char> alignedString2;
 if(stringInputVector[0].length() == stringInputVector[1].length())
  {
      indexOfLargestString  = 0;
      indexOfSmallestString = 1;
  }else
  {
    indexOfLargestString = (stringInputVector[0].length() > stringInputVector[1].length()) ? 0 : 1;
    indexOfSmallestString = (stringInputVector[0].length() > stringInputVector[1].length()) ? 1 : 0;
  }

 for(int i = 0; i <= numRows; i++)
  {
    for(int j = 0; j <=  numColumn; j++)
    {
      //init zeroth row/column
      if(i == 0 && j == 0)
      {
        sequenceMatrix[i][j] = 0;
      }
      else if(i == 0 && j > 0)
      {
          sequenceMatrix[i][j] = sequenceMatrix[i][j-1] - 2;
      }
      
      else if(i > 0 && j == 0)
      {
        sequenceMatrix[i][j] = sequenceMatrix[i-1][j] - 2;
      }
     
      //Perfect match case
      else if(stringInputVector[indexOfSmallestString].at(j-1) == stringInputVector[indexOfLargestString].at(i-1))
     {
       sequenceMatrix[i][j] = max(sequenceMatrix[i-1][j-1] + 2,max(sequenceMatrix[i-1][j]-2,sequenceMatrix[i][j-1]-2));
     }

       //check if both vowels
     else if(checkVowelCase(stringInputVector[indexOfSmallestString].at(j-1), stringInputVector[indexOfLargestString].at(i-1)))
     {
       sequenceMatrix[i][j] = max(sequenceMatrix[i-1][j-1] + 1,max(sequenceMatrix[i-1][j]-2,sequenceMatrix[i][j-1]-2));
     }

     //check misMatchCase
     else if (checkMisMatchCase(stringInputVector[indexOfSmallestString].at(j-1), stringInputVector[indexOfLargestString].at(i-1)))
     {
       sequenceMatrix[i][j] = max(sequenceMatrix[i-1][j-1] + 1,max(sequenceMatrix[i-1][j]-2,sequenceMatrix[i][j-1]-2));
     }

     else
     {
       //else check dissimlar vs gap penalties
       sequenceMatrix[i][j] = max(sequenceMatrix[i-1][j-1] - 1,max(sequenceMatrix[i-1][j]-2,sequenceMatrix[i][j-1]-2));
     }

    } 
  }


 cout << "Total Alignment Score: " << sequenceMatrix[numRows][numColumn] << endl;
cout << "Aligned Strings: " << endl;


while(row <= numRows && column <= numColumn)
{
  //check perfect match diagonal case
  if(sequenceMatrix[row][column] == sequenceMatrix[row-1][column-1] + 2 || sequenceMatrix[row][column] == sequenceMatrix[row-1][column-1] + 1)
  {
    alignedString1.push_back(stringInputVector[indexOfLargestString].at(row-1));
    alignedString2.push_back(stringInputVector[indexOfSmallestString].at(column-1));
    row++;
    column++;
  }
  else{
      alignedString1.push_back('_');
      alignedString1.push_back(stringInputVector[indexOfLargestString].at(row-1));
      alignedString2.push_back(stringInputVector[indexOfSmallestString].at(column-1));
      alignedString2.push_back('_');
      row++;
      column++;
     }
}
if(numColumn < stringInputVector[indexOfLargestString].size())
{

  for(int i = numColumn; i < stringInputVector[indexOfLargestString].size();i++)
  {
    alignedString1.push_back(stringInputVector[indexOfLargestString].at(i));  
    alignedString2.push_back('_');
  }
}

for(int i = 0; i < alignedString1.size();i++)
{
  cout << alignedString1[i];
}
cout << endl;

for(int i = 0; i < alignedString2.size();i++){
  cout << alignedString2[i];
}
cout << endl;

}//END sequenceAlign


int max(int num1,int num2)
{
  return (num1 > num2) ? num1 : num2;
}//END max

int min(int num1,int num2)
{
  return (num1 < num2) ? num1 : num2;
}//END min

bool checkMisMatchCase(char letter1,char letter2)
{
  
  //very ugly...but it works.
  if(letter1 == 'b' || letter1 == 'p'){if(letter2 == 'b' || letter2 == 'p'){return true;}}
  else if(letter1 == 'c'){if(letter2 == 's' || letter2 == 'k'){return true;}}
  else if(letter1 == 'd' || letter1 == 't'){if(letter2 == 't' || letter2 == 'd'){return true;}}
  else if(letter1 == 'e'){if(letter2 == 'y'){return true;}}
  else if(letter1 == 'y' && letter2 == 'e'){return true;}
  else if(letter1 == 'g'){if(letter2 == 'j' || letter2 == 'k'){return true;}} 
  else if(letter1 == 'j' && letter2 == 'g'){return true;}
  else if(letter1 == 'k'){if(letter2 == 'q' || letter2 == 'c' || letter2 == 'g'){return true;}}
  else if(letter1 == 'w' || letter1 == 'v'){if(letter2 == 'w' || letter2 == 'v'){return true;}}
  else if(letter1 == 'z' && letter2 == 's'){return true;}
  else if(letter1 == 'i' && letter2 == 'y'){return true;}
  else if(letter1 == 'y' && letter2 == 'i'){return true;} 
  else if(letter1 == 'q' && letter2 == 'k'){return true;}
  else if(letter1 == 'm' || letter1 == 'n'){if(letter2 == 'm' || letter2 == 'n'){return true;}}
  else if(letter1 == 's' || letter1 == 'z'){if(letter2 == 's' || letter2 == 's'){return true;}}

  return false;

}

bool checkVowelCase(char letter1,char letter2)
{
 

  //Don't have to worry about fallthrough here because all letters being considered are vowels.
  switch(letter1)
  {
    case 'a':
      if(letter2 == 'e' || letter2 == 'i' || letter2 == 'o' || letter2 == 'u'){return true;}
    case 'e':
      if(letter2 == 'a' || letter2 == 'i' || letter2 == 'o' || letter2 == 'u'){return true;}
    case 'i':
      if(letter2 == 'a' || letter2 == 'e' || letter2 == 'o' || letter2 == 'u'){return true;}
    case 'o':
      if(letter2 == 'a' || letter2 == 'e' || letter2 == 'i' || letter2 == 'u'){return true;}
    case 'u':
      if(letter2 == 'a' || letter2 == 'e' || letter2 == 'i' || letter2 == 'o'){return true;}
    default:
      return false;
  }
     
}

string getUserInput()
{
string userInput;

 cout << "Input a string that you wish to perform a sequence alignment on: "; 
 cin >> userInput;

 for(int i = 0; i < userInput.length();i++)
 {
   userInput[i] = tolower(userInput[i]);
 }


return userInput;

}//END getUserInput



