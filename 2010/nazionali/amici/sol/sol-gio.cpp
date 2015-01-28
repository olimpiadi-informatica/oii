
/*

Soluzione di Giovanni Mascellani.

È d'accordo con la soluzione di Matteo su una ventina di
casi di dimensione massima (generati con il generatore).

Ricostruisce i cicli della permutazione, in modo da poterla
calcolare in tempo costante, ordina con counting sort
e cerca l'inizio della sottostringa di true contigui.

*/

#include <cstdio>
#include <cstdlib>

using namespace std;

const int MaxGuestsNum = 1000000;

int guestsNum, friendsNum, transitionsNum;
int transTable[MaxGuestsNum];
bool transSeen[MaxGuestsNum];
int startPos[MaxGuestsNum];
bool stopPos[MaxGuestsNum];
int cycles[MaxGuestsNum];
int cyclesLen[MaxGuestsNum];
int cyclesStart[MaxGuestsNum];
int cyclesPtr[MaxGuestsNum];
int cyclesLenPtr[MaxGuestsNum];
int cycleNum;

inline int calcPos(int x) {

  int cycle = cyclesLenPtr[x];
  int offset = cyclesPtr[x] - cyclesStart[cycle];
  int newOff = (offset + transitionsNum) % cyclesLen[cycle];
  return cycles[cyclesStart[cycle]+newOff];

}

int main() {

  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  scanf("%d %d %d", &guestsNum, &friendsNum, &transitionsNum);
  for (int i = 0; i < guestsNum; i++) {
    scanf("%d", &transTable[i]);
    transTable[i]--;
  }
  for (int i = 0; i < friendsNum; i++) {
    scanf("%d", &startPos[i]);
    startPos[i]--;
  }

  int cyclePos = 0;
  for (int i = 0; i < guestsNum; i++) {
    if (!transSeen[i]) {
      int j = i;
      cyclesStart[cycleNum] = cyclePos;
      while (!transSeen[j]) {
	transSeen[j] = true;
	cycles[cyclePos] = j;
	cyclesLen[cycleNum]++;
	cyclesPtr[j] = cyclePos;
	cyclesLenPtr[j] = cycleNum;
	cyclePos++;
	j = transTable[j];
      }
      cycleNum++;
    }
  }

  for (int i = 0; i < friendsNum; i++) {
    stopPos[calcPos(startPos[i])] = true;
  }

  if (stopPos[0]) {
    int i;
    for (i = guestsNum-1; stopPos[i]; i--);
    printf("%d\n", (i == guestsNum-1 ? guestsNum : i+2));
  } else {
    int i;
    for (i = 0; !stopPos[i]; i++);
    printf("%d\n", i+1);
  }

  return 0;

}
