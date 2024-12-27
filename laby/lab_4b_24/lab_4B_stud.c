#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define FINISH_LINE 20
#define MAX_STEPS 4

// ETAP 1 - definicje struktur:

typedef struct reindeer {
  int id;
  int position;
} reindeer;

typedef struct race {
  reindeer **reindeers;
  int size;
} race;

typedef struct ranking {
  int firstPlace, secondPlace, thirdPlace, others;
} ranking;

void sort(race* T);

// ETAP 2
int init_reindeer(race *T, int n);
void print_reindeer(race T);

// ETAP 3
void add_to_ranking(ranking *R, int i, race T);
int remove_reindeer(race *T, int i);
void move_reindeer(race *T, int i, int steps);

// ETAP 4
void simulate(race *T, ranking *R);

int main() {
  srand(42);
  int N = 8;
  int result;

  // ETAP 2 (2 pkt)
  
  printf("======= ETAP 2 =======\n");
  race reindeerRace;
  result = init_reindeer(&reindeerRace, N);
  if (result != 0) {
    printf("Error!\n");
  }
  print_reindeer(reindeerRace);

  race temporaryRace;
  result = init_reindeer(&temporaryRace, 2);
  if (result != 0) {
    printf("Error!\n");
  }
  print_reindeer(temporaryRace);
  free(temporaryRace.reindeers);
  

  // ETAP 3 (2 pkt)
  printf("\n======= ETAP 3 =======\n");
  ranking reindeerRanking = { -1, -1, -1, 0 };
  add_to_ranking(&reindeerRanking, 3, reindeerRace);
  add_to_ranking(&reindeerRanking, 5, reindeerRace);
  add_to_ranking(&reindeerRanking, 2, reindeerRace);
  add_to_ranking(&reindeerRanking, 1, reindeerRace);
  add_to_ranking(&reindeerRanking, 6, reindeerRace);

  printf("Pierwsze miejsce: %d\n", reindeerRanking.firstPlace);
  printf("Drugie miejsce: %d\n", reindeerRanking.secondPlace);
  printf("Trzecie miejsce: %d\n", reindeerRanking.thirdPlace);
  printf("Pozostale renifery w rankingu: %d\n\n", reindeerRanking.others);

  print_reindeer(reindeerRace);
  printf("\nUsuwam renifera o indeksie 3\n\n");
  result = remove_reindeer(&reindeerRace, 3);
  if (result != 0) {
    printf("Error!\n");
  }

  print_reindeer(reindeerRace);
  printf("\nUsuwam renifera o indeksie 6\n\n");
  result = remove_reindeer(&reindeerRace, 6);
  if (result != 0) {
    printf("Error!\n");
  }
  print_reindeer(reindeerRace);

  printf("\nRuch reniferow:\n");
  move_reindeer(&reindeerRace, 3, 5);
  move_reindeer(&reindeerRace, 2, 3);
  move_reindeer(&reindeerRace, 5, 2);
  print_reindeer(reindeerRace);

  // ETAP 4 (2 pkt)
  
  printf("\n======= ETAP 4 =======\n");
  race finalreindeerRace;
  ranking finalRindeerRanking = { -1, -1, -1, 0 };
  init_reindeer(&finalreindeerRace, 7);

  simulate(&finalreindeerRace, &finalRindeerRanking);
  
  printf("Pierwsze miejsce: %d\n", finalRindeerRanking.firstPlace);
  printf("Drugie miejsce: %d\n", finalRindeerRanking.secondPlace);
  printf("Trzecie miejsce: %d\n", finalRindeerRanking.thirdPlace);
  printf("Pozostale renifery w rankingu: %d\n", finalRindeerRanking.others);

  free(reindeerRace.reindeers);
  free(finalreindeerRace.reindeers);
  
  return 0;
}

void sort(race* T) {
  size_t n = T->size;
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (T->reindeers[j]->position < T->reindeers[j + 1]->position) {
        reindeer *temp = T->reindeers[j];
        T->reindeers[j] = T->reindeers[j + 1];
        T->reindeers[j + 1] = temp;
      }
    }
  }
}

int init_reindeer(race *T, int n) {
  static int ID = 0;
  T->reindeers = (reindeer**)malloc(n*sizeof(reindeer*));
  if (T->reindeers == NULL) {
    return -1;
  }
  T->size = n;

  for (int i = 0; i < n; i++) {
    T->reindeers[i] = (reindeer*)malloc(sizeof(reindeer));
        if (T->reindeers[i] == NULL) {
            return -1;
        }
    T->reindeers[i]->id = ID++;
    T->reindeers[i]->position = 0;
  }

  return 0;
}

void print_reindeer(race T) {
  for (int i = 0; i < T.size; i++)
    printf("Renifer %d: pozycja %d\n", T.reindeers[i]->id, T.reindeers[i]->position);
}

void add_to_ranking(ranking *R, int i, race T) {
  int searched = -1, k;
  
  // Search for the reindeer by ID
  for (k = 0; k < T.size; k++) {
    if (T.reindeers[k]->id == i) {
      searched = k;
      break;  // Exit the loop early if found
    }
  }

  // If reindeer was not found, do nothing
  if (searched == -1) {
    printf("Renifer o ID %d nie znaleziony.\n", i);
    return;
  }

  // Update ranking
  if (R->firstPlace == -1) {
    R->firstPlace = searched;
  } else if (R->secondPlace == -1) {
    R->secondPlace = searched;
  } else if (R->thirdPlace == -1) {
    R->thirdPlace = searched;
  } else {
    R->others++;
  }
}

int remove_reindeer(race *T, int i) {
    int searched = -1;
    for (int k = 0; k < T->size; k++) {
        if (T->reindeers[k]->id == i) {
            searched = k;
            break;
        }
    }

    if (searched == -1) {
        printf("Renifer o indeksie %d nie znaleziony.\n", i);
        return -1;
    }

    // Zwolnij pamięć dla usuwanego renifera
    free(T->reindeers[searched]);

    // Przesuń wskaźniki w tablicy
    for (int l = searched; l < T->size - 1; l++) {
        T->reindeers[l] = T->reindeers[l + 1];
    }

    T->size--;

    // Realokacja pamięci dla nowego rozmiaru
    if (T->size > 0) {
        reindeer **temp = (reindeer **)realloc(T->reindeers, T->size * sizeof(reindeer *));
        if (temp == NULL) {
            printf("Błąd realokacji pamięci.\n");
            return -1;
        }
        T->reindeers = temp;
    } else {
        free(T->reindeers);
        T->reindeers = NULL;
    }

    return 0;
}

void move_reindeer(race *T, int i, int steps) {
  int k, searched = -1;
  for (k = 0; k < T->size; k++)
    if ((*T).reindeers[k]->id == i) {
      searched = k;
      break;
    }

  if (searched == -1) {
    printf("Renifer o ID %d nie znaleziony.\n", i);
    return;
  }
    
  T->reindeers[searched]->position = T->reindeers[searched]->position + steps;
}

void simulate(race *T, ranking *R) {
  srand( time( NULL ) );

  while (T->size > 0) {
    for (int k = T->size - 1; k >= 0; k--) {
      int steps = (rand() % (MAX_STEPS - 1 + 1)) + 1; // Losowanie ruchu
      T->reindeers[k]->position += steps;

      if (T->reindeers[k]->position >= FINISH_LINE) {
        printf("Renifer %d dotarł do mety!\n", T->reindeers[k]->id);
        add_to_ranking(R, T->reindeers[k]->id, *T);
        remove_reindeer(T, T->reindeers[k]->id);
      }
    }
  }

  printf("\nKONIEC WYŚCIGU\n");

}
