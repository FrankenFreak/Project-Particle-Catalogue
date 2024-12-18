// Clive Marvelous

#ifndef FOUR_MOMENTUM_H
#define FOUR_MOMENTUM_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>

using std::string;

// Template function to calculate magnitude square
template<class c_type> c_type magnitude_square(c_type x1, c_type x2, c_type y1, c_type y2, c_type z1, c_type z2) 
  {return x1*x2 + y1*y2 + z1*z2;}

// Beginning of 4-momentum class (Taking h=c=1)
class fourMomentum
{
private: 
  // Data members
  std::vector<double> four_momentum; // All values in MeV

  // Validation function (Check for empty vector)
  void validate() const;

public: 
  // Constructor and destructor 
  fourMomentum();
  fourMomentum(double E, double px, double py, double pz);
  ~fourMomentum();

  // Copy constructor and assignment
  fourMomentum(const fourMomentum&);
  fourMomentum& operator=(const fourMomentum&);

  // Move constructor
  fourMomentum(fourMomentum&&);
  fourMomentum& operator=(fourMomentum&&);

  // Get functions 
  const double get_E() const;
  const double get_px() const;
  const double get_py() const;
  const double get_pz() const;

  // Set functions 
  void set_E(double E);
  void set_px(double px);
  void set_py(double py);
  void set_pz(double pz);

  // 3 momentum magnitude functions
  double momentum_magnitude();

  // Invariant mass functions
  double invariant_mass();

  // Friend functions
  friend fourMomentum operator+(const fourMomentum& vector1, const fourMomentum& vector2);
  friend fourMomentum operator-(const fourMomentum& vector1, const fourMomentum& vector2);
  friend double dotProduct(const fourMomentum& vector1, const fourMomentum& vector2);

  // Print function
  void print_data();
};



#endif