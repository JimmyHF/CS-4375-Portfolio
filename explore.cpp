#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

double sum(vector<double> vec) {
  double sum = 0;
  for (double i : vec) {
    sum+= i;
  }
  return sum;
}

double mean(vector<double> vec) {
  return sum(vec) / vec.size();
}

double median(vector<double> vec) {
  sort(vec.begin(), vec.end());
  if (vec.size() % 2 == 1) {
    return vec.at((int)((double)vec.size() / 2.0 - 0.5));
  } else {
    return (double)(vec.at(vec.size() / 2) + vec.at((vec.size() / 2) - 1)) / 2.0;
  }
}

double range(vector<double> vec) {
  sort(vec.begin(), vec.end());
  return vec.back() - vec.front();
}

void print_stats(vector<double> vec) {
  cout << "Sum: " << sum(vec) << endl;
  cout << "Mean: " << mean(vec) << endl;
  cout << "Median: " << median(vec) << endl;
  cout << "Range: " << range(vec) << endl;
  return;
}

double stddev(vector<double> vec) {
  vector<double> stddev_num = {};
  double vec_mean = mean(vec);
  for (double i : vec) {
    stddev_num.push_back(pow(i - vec_mean, 2));
  }
  return sqrt(sum(stddev_num) / (vec.size() - 1));
}

double covar(vector<double> vec1, vector<double> vec2) {
  vector<double> covar_num = {};
  double vec1_mean = mean(vec1);
  double vec2_mean = mean(vec2);
  if (vec1.size() == vec2.size()) {
    for (size_t i = 0; i < vec1.size(); i++) {
      covar_num.push_back((vec1.at(i) - vec1_mean) * (vec2.at(i) - vec2_mean));
    }
    return sum(covar_num) / (vec1.size() - 1);
  }
  return -1;
}

double cor(vector<double> vec1, vector<double> vec2) {
  return covar(vec1, vec2) / (stddev(vec1) * stddev(vec2));
}

int main(int argc, char** argv) {
  ifstream inFS;
  string line;
  string rm_in, medv_in;
  const int MAX_LEN = 1000;
  vector<double> rm(MAX_LEN);
  vector<double> medv(MAX_LEN);
  
  cout << "Opening file Boston.csv" << endl;
  
  inFS.open("Boston.csv");
  if (!inFS.is_open()) {
    cout << "Could not open file Boston.csv" << endl;
    return -1;
  }
  
  cout << "Reading line 1" << endl;
  getline(inFS, line);
  cout << "Heading: " << line << endl;
  
  int numObservations = 0;
  while (inFS.good()) {
    getline(inFS, rm_in, ',');
    getline(inFS, medv_in, '\n');
    
    rm.at(numObservations) = stof(rm_in);
    medv.at(numObservations) = stof(medv_in);
    
    numObservations++;
  }
  
  rm.resize(numObservations);
  medv.resize(numObservations);
  
  cout << "New length " << rm.size() << endl;
  cout << "Closing file Boston.csv" << endl;
  inFS.close();
  
  cout << "Number of records: " << numObservations << endl;
  cout << "\nStats for rm" << endl;
  print_stats(rm);
  cout << "\nStats for medv" << endl;
  print_stats(medv);
  
  cout << "\n Covariance = " << covar(rm, medv) << endl;
  cout << "\n Correlation = " << cor(rm, medv) << endl;
  
  cout << "\nProgram terminated";
  return 0;
}