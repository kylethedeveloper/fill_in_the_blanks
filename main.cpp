// Boyer-Moore-Horspool algorithm is used to search through text and find the searched pattern.

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

using namespace std;
using namespace std::chrono;

#define CHARS 256

int max(int a, int b) // get max function
{
  return (a > b) ? a : b;
}

// bad character heuristic function
void badCharHeuristic(string str, int size, int badchar[CHARS])
{
  // Initialize all characters as -1
  for (int i = 0; i < CHARS; i++)
    badchar[i] = -1;

  // Fill last occurrence of a character in string
  for (int i = 0; i < size; i++)
    badchar[(int) str[i]] = i;
}

int afterShift(int shift, string txt, string a)
{
  int m = a.size();
  int n = txt.size();

  int badchar[CHARS];

  badCharHeuristic(a, m, badchar);

  int s = shift; // start checking from 'before'
  while (s <= (n - m))
  {
    int j = m - 2; // if there is ? at the end, make -3

    while (j >= 0 && a[j] == txt[s + j])
      j--;

    if (j < 0)  // if found
      return s; // return the location of 'after'
    else
      s += max(1, j - badchar[txt[s + j]]);
  }
  return 0; // if NOT found return 0
}

string search(string txt, string b, string a)
{
  if(a == "")
    return "Statement NOT found.";  // if ___ is not found

  int m = b.size();
  int n = txt.size();

  int badchar[CHARS]; // ascii array

  badCharHeuristic(b, m, badchar);

  int s = 0; // shift of the pattern with respect to text
  while (s <= (n - m))
  {
    int j = m - 1;

    while (j >= 0 && b[j] == txt[s + j])
      j--;

    if (j < 0)  // if 'before' is found at text
    {
      string answer = "";
      int until = afterShift(s, txt, a);  // get the location of 'after'
      if(until - s < 100) {   // if char number 'before' and 'after' text is smaller than 150
        for (int x = (s+m); x < until; x++) { // loop until 'after' from 'before'
          answer += txt[x]; // add the middle part as answer
        }
      }

      if (answer.size() > 0 && answer.size() < 100) { // appropriate size of answer
        string result;
        //result.append(b); // result = before
        result.append(answer); // result = before + answer
        //result.append(a); // result = before + answer + after
        return result;
      }
      else{
        s += (s + m < n) ? m - badchar[txt[s + m]] : 1; // increase shift
      }
    }

    else
      s += max(1, j - badchar[txt[s + j]]); // increase shift
  }

  return "Statement NOT found.";  // if nothing is returned at the end
}

void getBeforeAfter(string pattern, string underscore, string *before, string *after)
{
  int u = underscore.size();  // 3
  bool found = false;

  for (int i = 0; i < pattern.size(); i++) {  // loop until end of statement
    int j = u - 1;

    while (underscore[j] == pattern[i + j]) { // if underscore is found
      j--;

    if (j<0) {  // if ___ is found
      found = true;
      *before = pattern.substr(0,i);  // before = <here> ___
      *after = pattern.substr(i+3, pattern.size()); // after = ___ <here>
      }
    }
  }
  if (!found) { // if ___ is NOT found
    *before = pattern;  // before is pattern (but not important)
    *after = "";  // after is empty string
  }
}

int main()
{
  auto start = high_resolution_clock::now();  // start the timer

  string statement;
  string before, after;
  string underscore = "___";
  int res = 1;

  ifstream mainFile("the_truman_show_script.txt"); // open the main text
  string mainText((std::istreambuf_iterator<char>(mainFile) ), (std::istreambuf_iterator<char>())); // save to mainText string
  if (!(mainFile.is_open())) {  // if fail to open
    cerr << "Unable to open the main text file.\n";
  }
  mainFile.close();

  ifstream statementsFile("statements_3.txt"); // open the statements text
  if (statementsFile.is_open()) {  // if file is open
    while (getline(statementsFile, statement)) {  // read line by line
      if (!(statement.size() == 0)) { // ignore new lines
        cout << res << ") " << statement << endl;  // print original statement with missing part
        getBeforeAfter(statement, underscore, &before, &after); // save before __ and after __
        cout << search(mainText, before, after) << endl;  // search and print the result
        cout << endl;
        res++;
      }
    }
    statementsFile.close();  // close the file
  }
  else {  // if fail to open
    cerr << "Unable to open the statements file.\n";
  }

  // end the timer
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);
  cout << "Time: " << duration.count() << " milliseconds" << endl;

  return 0;
}


/*bool checkAfter(string before, string answer, string after, string txt)
{
  string result;
  result.append(before);
  result.append(answer);
  after.erase(after.size() - 1);
  result.append(after);
  int m = result.size();
  int n = txt.size();

  int badchar[CHARS];

  badCharHeuristic(result, m, badchar);

  int s = 0; // s is shift of the pattern with respect to text
  while (s <= (n - m))
  {
      int j = m - 1;

      while (j >= 0 && result[j] == txt[s + j])
          j--;

      if (j < 0)
      {
          return true;
      }

      else
          s += max(1, j - badchar[txt[s + j]]);
  }

    return false;
}*/
