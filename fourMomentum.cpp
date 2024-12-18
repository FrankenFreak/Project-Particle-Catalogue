// Clive Marvelous, last updated 6/4/24

#include<iostream>
#include<string>
#include<vector>
#include<cmath>

#include "fourMomentum.h"

// Validation function (Check for empty vector)
void fourMomentum::validate() const {if(four_momentum.empty()) throw std::runtime_error("Empty four momentum");}

// Default constructor
fourMomentum::fourMomentum() : four_momentum(4) {}

// Parameterised constructor
fourMomentum::fourMomentum(double E, double px, double py, double pz) : four_momentum{E, px, py, pz}{}

// Destructor
fourMomentum::~fourMomentum() {} 

// Copy constructor 
fourMomentum::fourMomentum(const fourMomentum& fm) : four_momentum(fm.four_momentum) {std::cout<<"Copy constructor called"<<std::endl;}

// Copy assignment
fourMomentum & fourMomentum::operator=(const fourMomentum& fm) 
{
  // Check for self-copy
  if(&fm != this) four_momentum = fm.four_momentum;
  return *this;
}

// Move constructor 
fourMomentum::fourMomentum(fourMomentum&& fm) : four_momentum(std::move(fm.four_momentum)) {std::cout << "Move constructor called\n";}

// Move assignment
fourMomentum & fourMomentum::operator=(fourMomentum&& fm)  
{
  // Prevent self-move
  if (&fm != this) four_momentum = std::move(fm.four_momentum);
  return *this;
}

// Get functions 
const double fourMomentum::get_E() const {return four_momentum[0];}
const double fourMomentum::get_px() const {return four_momentum[1];}
const double fourMomentum::get_py() const {return four_momentum[2];}
const double fourMomentum::get_pz() const {return four_momentum[3];}

// Set functions 
void fourMomentum::set_E(double E) {four_momentum[0]=E;}
void fourMomentum::set_px(double px) {four_momentum[1]=px;}
void fourMomentum::set_py(double py) {four_momentum[2]=py;}
void fourMomentum::set_pz(double pz) {four_momentum[3]=pz;}

// Member functions:
double fourMomentum::momentum_magnitude() // Momentum magnitude
{
  validate();
  double magnitude{magnitude_square(four_momentum[1], four_momentum[1], 
    four_momentum[2], four_momentum[2], four_momentum[3], four_momentum[3])};
  return std::sqrt(magnitude);
}
double fourMomentum::invariant_mass() // Invariant mass function
{
  validate();
  double mass_square{std::pow(four_momentum[0], 2) - std::pow(this->momentum_magnitude(), 2)};
  return std::sqrt(mass_square);
}

// Friend functions:
fourMomentum operator+(const fourMomentum& vector1, const fourMomentum& vector2) // Overload operator+
{
  // Check for empty vectors
  vector1.validate();
  vector2.validate();
  
  double energy_result{vector1.four_momentum[0] + vector2.four_momentum[0]};
  double px_result{vector1.four_momentum[1] + vector2.four_momentum[1]};
  double py_result{vector1.four_momentum[2] + vector2.four_momentum[2]};
  double pz_result{vector1.four_momentum[3] + vector2.four_momentum[3]};
  fourMomentum result(energy_result, px_result, py_result, pz_result);
  return result;
}
fourMomentum operator-(const fourMomentum& vector1, const fourMomentum& vector2) // Overload operator-
{
  // Check for empty vectors
  vector1.validate();
  vector2.validate();

  double energy_result{vector1.four_momentum[0] - vector2.four_momentum[0]};
  double px_result{vector1.four_momentum[1] - vector2.four_momentum[1]};
  double py_result{vector1.four_momentum[2] - vector2.four_momentum[2]};
  double pz_result{vector1.four_momentum[3] - vector2.four_momentum[3]};
  fourMomentum result{energy_result, px_result, py_result, pz_result};
  return result;
}
double dotProduct(const fourMomentum& vector1, const fourMomentum& vector2) // Dot product function
{
  // Check for empty vectors
  vector1.validate();
  vector2.validate();

  // Calculation
  double result{vector1.four_momentum[0]*vector2.four_momentum[0]};
  double magnitude{magnitude_square(vector1.four_momentum[1], vector2.four_momentum[1], 
    vector1.four_momentum[2], vector2.four_momentum[2], vector1.four_momentum[3], vector2.four_momentum[3])};
  return result - magnitude;
}

// Print function
void fourMomentum::print_data()
{
  validate();
  std::cout.precision(4); // Set precision for floating point numbers
  std::cout<<"Energy: "<<four_momentum[0]<<" MeV"<<std::endl;
  std::cout<<"Momentum (px): "<<four_momentum[1]<<" MeV/c"<<std::endl;
  std::cout<<"Momentum (py): "<<four_momentum[2]<<" MeV/c"<<std::endl;
  std::cout<<"Momentum (pz): "<<four_momentum[3]<<" MeV/c"<<std::endl;
  return;
}

