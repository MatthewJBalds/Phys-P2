#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "cmath"

namespace physics {
	class MyVector{
		public:
			float x, y, z;
			MyVector(const float x = 0, const float y = 0, const float z = 0) : x(x), y(y), z(z) {}
			
			explicit operator glm::vec3() const { return glm::vec3(x, y, z); }

			float Magnitude() const;

			float SquareMagnitude() const;

			MyVector direction() const;

			MyVector operator+(const MyVector v);

			MyVector operator-(const MyVector v);
			
			MyVector operator*(const MyVector v);

			MyVector operator/(const MyVector v);

			void operator+= (const MyVector v);

			void operator-= (const MyVector v);

			MyVector ScalarMultiplication(const float toScale) const;

			void operator*= (const MyVector v);

			float DotProd(const MyVector v) const;

			MyVector crossProd(const MyVector v) const;



	};
}


