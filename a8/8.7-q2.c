#include <stdio.h>
#include <stdlib.h>

int q2 (int arg0, int arg1, int arg2) {
  switch (arg0) {
    case 10:  arg2=arg1+arg2; break;
    case 11:  arg2=0; break;
    case 12:  arg2=arg1-arg2; break;
    case 13:  arg2=0; break;
    case 14:  
        if (arg1 > arg2) {
            arg2 = 1;
        } else {
            arg2 = 0;
        }
        break;
    case 15:  arg2=0; break;
    //break;
        if (arg1 < arg2) {
            arg2 = 1;
        } else {
            arg2 = 0;
        }
        break;
    case 17:  arg2=0; break;
    case 18:  
        if (arg1 == arg2) {
            return 1;
        } else {
            return 0;
        }
        break;
    default:  arg2 = 0; break;
  }
  return arg2;
}

int main (int argc, char** argv) {
    char* nul;
    printf ("%d\n", q2(strtol(argv[1], &nul, 10), strtol(argv[2], &nul, 10), strtol(argv[3], &nul, 10)));
}