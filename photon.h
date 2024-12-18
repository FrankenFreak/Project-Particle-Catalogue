// Clive Marvelous

#ifndef PHOTON_H
#define PHOTON_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include <memory>

#include "fourMomentum.h"
#include "particle.h"
#include "boson.h"

using std::string;

class photon : public boson 
{
protected:
  // Data members
  static int photon_count; 

public:
  // Constructors and destructor
  photon();
  photon(double E, double px, double py, double pz);
  ~photon();

  // Copy constructor and assignment
  photon(const photon&);
  photon& operator=(const photon&);

  // Move constructor and assignment
  photon(photon&&);
  photon& operator=(photon&&);

  // Clone function
  std::shared_ptr<particle> clone() const override;
  
  // Get function
  static int get_photon_count();

  // Print data function
  void print_data() override;
};

#endif