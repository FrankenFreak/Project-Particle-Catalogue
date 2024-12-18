// Clive Marvelous

#ifndef GLUON_H
#define GLUON_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include <memory>

#include "fourMomentum.h"
#include "particle.h"
#include "boson.h"

using std::string;

// Gluon derived class
class gluon : public boson 
{
protected:
  // Data members
  static int gluon_count; 
  ColourCharge colour_charge;
  ColourCharge anti_colour_charge;

public:
  // Constructor and destructor
  gluon();
  gluon(ColourCharge colour_in, ColourCharge anti_colour_in, double E, double px, double py, double pz);
  ~gluon();

  // Copy constructor and assignment
  gluon(const gluon&);
  gluon& operator=(const gluon&);

  // Move constructor and assignment
  gluon(gluon&&);
  gluon& operator=(gluon&&);

  // Clone function
  std::shared_ptr<particle> clone() const override;

  // Get functions
  const ColourCharge get_colour();
  const ColourCharge get_anti_colour();
  static int get_gluon_count();
  
  // Set functions
  void set_colour(ColourCharge colour_in);
  void set_anti_colour(ColourCharge anti_colour_in);

  // Print function
  void print_data() override;
};




#endif