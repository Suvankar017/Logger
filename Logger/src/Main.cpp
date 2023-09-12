#include "Debug.h"

struct Vector3
{
	float x, y, z;

	Vector3() : x(0.0f), y(0.0), z(0.0f) {  }
	Vector3(float x, float y) : x(x), y(y), z(0.0f) {  }
	Vector3(float x, float y, float z) : x(x), y(y), z(z) {  }

	friend std::ostream& operator<<(std::ostream& os, const Vector3& v)
	{
		os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
		return os;
	}
};

int main()
{
	Vector3 v(1.0f, 2.0f, 3.0f);

	Debug::Info("# # # # # #", 1, 5.0f, 3.141, 'A', "Suvankar", v);
	Debug::Success("# # # # # #", 1, 5.0f, 3.141, 'A', "Suvankar", v);
	Debug::Warning("# # # # # #", 1, 5.0f, 3.141, 'A', "Suvankar", v);
	Debug::Error("# # # # # #", 1, 5.0f, 3.141, 'A', "Suvankar", v);

	ASSERT(false, "Test assertion");

	return 0;
}