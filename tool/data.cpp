#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>
int random(int n){
  return (long long)rand()*(long long)rand()%n;
}
