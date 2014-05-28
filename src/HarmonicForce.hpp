/*
  Copyright (C) 2014 The ESPResSo project

  This file is part of ESPResSo.

  ESPResSo is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  ESPResSo is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#ifndef _HARMONICFORCE_HPP
#define _HARMONICFORCE_HPP

#include "config.hpp"

#ifdef CUDA

#include "SystemInterface.hpp"
#include <iostream>

void HarmonicForce_kernel_wrapper(float x, float y, float z, float k,
		     int n, float *pos, float *f);

class HarmonicForce {
public:
  HarmonicForce(float x1, float x2, float x3, float _k, SystemInterface &s) {
    x = x1;
    y = x2;
    z = x3;
    k = _k;

    if(!s.requestFGpu())
      std::cerr << "HarmonicForce needs access to forces on GPU!" << std::endl;

    if(!s.requestRGpu())
      std::cerr << "HarmonicForce needs access to positions on GPU!" << std::endl;

  }; 
  void calc(SystemInterface &s) {
    HarmonicForce_kernel_wrapper(x,y,z,k,s.npart_gpu(),
					 s.rGpuBegin(), s.fGpuBegin());
  };
protected:
  float x,y,z;
  float k;
};

extern HarmonicForce *harmonicForce;

#endif
#endif
