#include <iostream>
#include <fstream>  // ifstream, ofstream
#include <vector>  // storing the positional vectors and magnitudes
#include <algorithm>  // std::sort
#include <chrono> // NOLINT (build/c++11)
#include <cmath>  // std::sqrt and std::pow
#include <string>  // file names

class Vector {
 private:
  double x_, y_;
  int magnitude_;

 public:
  // default constructor calculating the vector's magnitude
  Vector(double x, double y) : x_(x), y_(y) {
    magnitude_ = std::sqrt(std::pow(x_, 2) + std::pow(y_, 2));
  }
  int Magnitude() {
    return magnitude_;
  }

  // operator overload < for std::sort
  bool operator< (const Vector& v) const {
    return magnitude_ < v.magnitude_;
  }

  // operator overload <<
  friend std::ostream& operator<< (std::ostream& os, const Vector& v) {
    os << v.x_ << " " << v.y_ << std::endl;
    return os;
  }
};

// processing time measurements
class CountTime {
 private:
  std::chrono::_V2::system_clock::time_point start;
 public:
  // intializing private data member start_point_ with the time point
  CountTime() {
    std::chrono::high_resolution_clock::time_point start_point;
    start = start_point;
  }
  // resetting time
  void Reset() {
    start = std::chrono::high_resolution_clock::now();
  }

  // printing the current time
  void CurrentTime() {
    double time;
    auto end = std::chrono::high_resolution_clock::now();
    time = std::chrono::duration<double, std::micro>(end - start).count();
    std::cout << "CPU time: " << time << " microseconds" << std::endl;
  }
};

// referenced from the lecture
int LSearch(std::vector<Vector>& calc_mag_vec, std::vector<int>& gvn_mag_vec) {
  int count = 0;
  std::vector<Vector>::iterator it;
  // traversing the given magnitude vector
  for (unsigned int i = 0; i < gvn_mag_vec.size(); ++i) {
    // comparing the given magnitudes to the calculated magnitudes
    for (unsigned j = 0; j < calc_mag_vec.size(); ++j) {
      if (gvn_mag_vec[i] == calc_mag_vec[j].Magnitude()) {
        ++count;
        // avoiding duplicate comparisons
        break;
      }
    }
  }
  return count;
}

// referenced from the lecture slides
int BSearch(std::vector<Vector>& calc_mag_vec, std::vector<int>& gvn_mag_vec) {
  int count = 0;
  // sorting and performing a binary search on the list of calculated magnitudes
  std::sort(calc_mag_vec.begin(), calc_mag_vec.end());
  for (unsigned int i = 0; i < gvn_mag_vec.size(); ++i) {
  int low = 0, high = calc_mag_vec.size() - 1;
    while (low <= high) {
      int mid = low + (high - low) / 2;

      if (calc_mag_vec[mid].Magnitude() == gvn_mag_vec[i]) {
        ++count;
        break;
      }

      if (calc_mag_vec[mid].Magnitude() < gvn_mag_vec[i])
        low = mid + 1;
      else
        high = mid - 1;
    }
  }
  return count;
}

void CannotOpenInputFile(std::ifstream &file, std::string file_name) {
  if (!file.is_open()) {
    std::cerr << "Error: cannot open file " << file_name << std::endl;
    exit(0);
  }
}

void CannotOpenOutputFile(std::ofstream& file, std::string file_name) {
  if (!file.is_open()) {
    std::cerr << "Error: cannot open file " << file_name << std::endl;
    exit(0);
  }
}

int main(int argc, char *argv[]) {
  // error management for command lines arguments
  if (argc != 4) {
    std::cerr << "Usage: /autograder/source/tests/vector_search ";
    std::cerr << "<vector_file.dat> <magnitude_file.dat> <result_file.dat>";
    std::cerr << std::endl;
    exit(0);
  }

  std::ifstream positional_vector_file(argv[1]);
  CannotOpenInputFile(positional_vector_file, argv[1]);

  std::ifstream magnitude_file(argv[2]);
  CannotOpenInputFile(magnitude_file, argv[2]);

  std::ofstream result_file(argv[3]);
  CannotOpenOutputFile(result_file, argv[3]);

  std::vector<Vector> positional_vector;
  std::vector<int> magnitude_vector;
  int x, y, magnitude;

  // storing the vectors from the positional vector file
  while (positional_vector_file >> x >> y) {
    positional_vector.push_back(Vector(x, y));
  }

  // storing the magnitudes from the magnitude file
  while (magnitude_file >> magnitude)
    magnitude_vector.push_back(magnitude);

  positional_vector_file.close();
  magnitude_file.close();

  int count = 0;
  char choice;
  bool repeat;
  CountTime ct;

  std::cout << "Choice of search method ([l]inear, [b]inary)?" << std::endl;

  // search method runtime mangagement
  do {
    std::cin >> choice;
    ct.Reset();
    switch (choice) {
      case 'l':
        // using linear search to find the number of matches
        count = LSearch(positional_vector, magnitude_vector);
        repeat = false;
        break;
      case 'b':
        // using binary search to find the number of matches
        count = BSearch(positional_vector, magnitude_vector);
        repeat = false;
        break;
      // error handling
      default:
        // getting the user's choice again
        std::cerr << "Incorrect choice" << std::endl;
        repeat = true;
    }
  } while (repeat);
  ct.CurrentTime();
  result_file << count << std::endl;
  result_file.close();
  return 0;
}
