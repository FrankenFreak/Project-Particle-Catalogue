// Clive Marvelous

#ifndef HIGGS_H
#define HIGGS_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<memory>

#include "fourMomentum.h"
#include "particle.h"
#include "quark.h"
#include "boson.h"
#include "photon.h"
#include "Z.h"
#include "W.h"

using std::string;

// Higgs derived class
class higgs : public boson 
{
protected:
  // Data members
  static int higgs_count; 

  // Update functions
  void update_boson_decay(BosonParticle boson_decay_product_in);
  void update_quark_decay(QuarkParticle quark_decay_product_in);

public:
  // Constructor and destructor
  higgs();
  higgs(QuarkParticle quark_decay_product_in, double E, double px, double py, double pz); // For decay to quark
  higgs(BosonParticle boson_decay_product_in, double E, double px, double py, double pz); // For decay to boson
  ~higgs();

  // Copy constructor and assignment
  higgs(const higgs&);
  higgs& operator=(const higgs& );

  // Move constructor and assignment
  higgs(higgs&&);
  higgs& operator=(higgs&&);

  // Clone function
  std::shared_ptr<particle> clone() const override;

  // Get function
  static int get_higgs_count();

  // Set function
  void set_boson_decay(BosonParticle boson_decay_product_in) override; // Set decay to boson
  void set_boson_decay(QuarkParticle quark_decay_product_in) override; // Set decay to quark

  // Print function
  void print_data() override;
};

#endif