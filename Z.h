// Clive Marvelous

#ifndef Z_H
#define Z_H

#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include <memory>

#include "fourMomentum.h"
#include "particle.h"
#include "boson.h"
#include "quark.h"
#include "electron.h"
#include "muon.h"
#include "tau.h"

using std::string;

// Z derived class
class Z : public boson 
{
protected:
  // Data members
  static int Z_count; 

  // Update functions
  void update_lepton_decay(LeptonParticle lepton_decay_product_in); // For decay to lepton (Other than neutrino)
  void update_neutrino_decay(Flavour neutrino_product_flavour_in); // For decay to neutrino
  void update_quark_decay(QuarkParticle quark_decay_product_in); // For decay to quark
  
public:
  // Constructors and destructors
  Z();
  Z(LeptonParticle lepton_decay_product_in, double E, double px, double py, double pz); // For decay to lepton (Other than neutrino)
  Z(QuarkParticle quark_decay_product_in, double E, double px, double py, double pz); // For decay to quark 
  Z(Flavour neutrino_decay_product_in, double E, double px, double py, double pz); // For decay to neutrino
  ~Z();

  // Copy constructor and assignment
  Z(const Z&);
  Z& operator=(const Z&);

  // Move constructor and assignment
  Z(Z&&);
  Z& operator=(Z&&);

  // Clone function
  std::shared_ptr<particle> clone() const override;

  // Get function
  static int get_Z_count();

  // Set functions
  void set_boson_decay(LeptonParticle lepton_decay_product_in) override; // For decay to lepton (Other than neutrino)
  void set_boson_decay(Flavour neutrino_product_flavour_in) override; // For decay to neutrino
  void set_boson_decay(QuarkParticle quark_decay_product_in) override; // For decay to quark

  // Print function
  void print_data() override;
};

#endif