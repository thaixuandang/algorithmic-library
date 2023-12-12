#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>

#define GENERATOR       "generator"
#define TEST_SOLUTION   "test"
#define NAIVE_SOLUTION  "naive"
#define DEFAULT_N       100

bool compile(const char* filename) {
  static char command[FILENAME_MAX];
  sprintf(command,
    "g++.exe -static -DLOCAL -Wl,--stack=268435456 -O2 -std=c++14 -o %s %s.cpp",
    filename, filename);
  return !system(command);
}

int test(int index) {
  system("generator > input");
  system("test < input > output");
  system("naive < input > answer");
  
  int result = system("fc output answer");
  printf("Test %d is %s.\n\n", index, result ? "incorrect" : "correct");
  return result;
}

void destroy_builds() {
  system("del generator.exe");
  system("del test.exe");
  system("del naive.exe");
}

int main(int argc, char* argv[]) {
  assert(compile(GENERATOR));
  assert(compile(TEST_SOLUTION));
  assert(compile(NAIVE_SOLUTION));

  int n = argc == 1 ? DEFAULT_N : atoi(argv[1]);
  for (int i = 0; i < n; ++i) {
    if (test(i)) {
      break;
    }
  }

  destroy_builds();
  return 0;
}
