#pragma once
#include "NumptyBehavior.h"

namespace Shape
{
	class SHAPEARRAYS
	{
	public:
		GLfloat VERT_SQUARE[16]{
				-0.5f, -0.5f,	0.0f, 0.0f,
				 0.5f, -0.5f,	1.0f, 0.0f,
				 0.5f,  0.5f,	1.0f, 1.0f,
				-0.5f,  0.5f,	0.0f, 1.0f
		};
		GLfloat VERT_CUBE[120 + 120 + 72] = {
				-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  0.0f,
				 0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  0.0f,
				 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  1.0f,
				 0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	1.0f,  1.0f,
				-0.5f,  0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  1.0f,
				-0.5f, -0.5f, -0.5f,	 0.0f,  0.0f, -1.0f,	0.0f,  0.0f,

				-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  0.0f,
				 0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  1.0f,
				 0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	1.0f,  1.0f,
				-0.5f,  0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  1.0f,
				-0.5f, -0.5f,  0.5f,	 0.0f,  0.0f,  1.0f,	0.0f,  0.0f,

				-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f,  0.0f,
				-0.5f,  0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	1.0f,  1.0f,
				-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  1.0f,
				-0.5f, -0.5f, -0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  1.0f,
				-0.5f, -0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	0.0f,  0.0f,
				-0.5f,  0.5f,  0.5f,	-1.0f,  0.0f,  0.0f,	1.0f,  0.0f,

				 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	1.0f,  0.0f,
				 0.5f,  0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	1.0f,  1.0f,
				 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  1.0f,
				 0.5f, -0.5f, -0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  1.0f,
				 0.5f, -0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	0.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,	 1.0f,  0.0f,  0.0f,	1.0f,  0.0f,

				-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  1.0f,
				 0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  1.0f,
				 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  0.0f,
				 0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	1.0f,  0.0f,
				-0.5f, -0.5f,  0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  0.0f,
				-0.5f, -0.5f, -0.5f,	 0.0f, -1.0f,  0.0f,	0.0f,  1.0f,

				-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  1.0f,
				 0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  1.0f,
				 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  0.0f,
				 0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	1.0f,  0.0f,
				-0.5f,  0.5f,  0.5f,	 0.0f,  1.0f,  0.0f,	0.0f,  0.0f,
				-0.5f,  0.5f, -0.5f,	 0.0f,  1.0f,  0.0f, 	0.0f,  1.0f
		};
		GLfloat VERT_TRIANGLE[12]{
					 0.5f,  0.5f,	0.0f, 0.0f,
					 0.5f, -0.5f,	1.0f, 0.0f,
					-0.5f, -0.5f,	1.0f, 1.0f,
		};

		GLuint INDEX_SQUARE[6]{
				0, 1, 2, // Lower left triangle
				2, 3, 0, // Lower right triangle
		};
		GLuint INDEX_CUBE[36]{
				0, 1, 2, // Lower left triangle
				2, 3, 0, // Lower right triangle

				0, 4, 5, // Lower left triangle
				5, 1, 0,

				5, 1, 2, // Lower left triangle
				2, 6, 5,

				6, 2, 3, // Lower left triangle
				3, 7, 6,

				5, 6, 7, // Lower left triangle
				7, 4, 5,

				7, 3, 0, // Lower left triangle
				0, 4, 7,
		};
		GLuint INDEX_TRIANGLE[3]{
		0, 1, 2, // Lower left triangle
		};
	};
	
}


