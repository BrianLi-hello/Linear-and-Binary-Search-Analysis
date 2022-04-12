#include <fstream>
#include <iostream>
#include <random>

int main(int argc, char *argv[]) {
  if (argc < 4) {
    std::cerr << "Usage: " << argv[0]
        << " <num_vectors> <num_magnitudes> <suffix> [seed]"
        << std::endl;
    exit(1);
  }

  int nvecs = std::stoi(argv[1]);
  int nmags = std::stoi(argv[2]);
  if (nvecs <= 0 || nmags <= 0) {
    std::cerr << "Error: wrong arguments" << std::endl;
    exit(1);
  }

  std::ofstream vects, mags;
  vects.open(std::string("vectors_") + argv[3] + ".dat",
             std::ofstream::trunc);
  mags.open(std::string("magnitudes_") + argv[3] + ".dat",
            std::ofstream::trunc);
  if (!vects.good() || !mags.good()) {
    std::cerr << "Error: cannot open output file(s)" << std::endl;
    exit(1);
  }

  /* random generator */
  std::random_device rd;
  std::mt19937 mt(rd());

  if (argc == 5) {
    int seed = std::stoi(argv[4]);
    if (seed < 0) {
      std::cerr << "Error: wrong seed" << std::endl;
      exit(1);
    }
    mt.seed(seed);
  }

  /* random number distribution for vectors */
  std::uniform_int_distribution<int> vect_dist(-nvecs, nvecs);
  for (int i = 0; i < nvecs; i++)
    vects << vect_dist(mt) << " " << vect_dist(mt) << "\n";

  /* random number distribution for magnitudes */
  std::uniform_int_distribution<int> mag_dist(0, 2 * nvecs);
  for (int i = 0; i < nmags; i++)
    mags << mag_dist(mt) << "\n";

  vects.close();
  mags.close();

  return 0;
}
