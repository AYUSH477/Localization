#pragma once
#include "Ray.h"
class Prim{
	public:
			Prim(void) = default;
			Prim(const Prim&) = delete;
			virtual ~Prim(void) = default;
			const Prim& operator=(const Prim&) = delete;
			virtual bool Intersect(Ray& ray) = 0;
	
	
	
	
	};