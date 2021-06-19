// Бирюков М8О-207Б-19 вариант 11

#include <cmath>
#include <cstdio>

using namespace std;

class vector3D {
public:
	int x;
	int y;
	int z;

	vector3D(int _x, int _y, int _z) {
		x = _x;
		y = _y;
		z = _z;
	}

	vector3D(): vector3D(0, 0, 0) {};

	vector3D(const vector3D &v): vector3D(v.x, v.y, v.z) {};

	vector3D add(vector3D a) {
		return vector3D(x + a.x, y + a.y, z + a.z);
	}

	vector3D sub(vector3D a) {
		return vector3D(x - a.x, y - a.y, z - a.z);
	}

	vector3D mul(int n) {
		return vector3D(x * n, y * n, z * n);
	}

	int dot(vector3D a) {
		return x*a.x + y*a.y + z*a.z;
	}

	vector3D cross(vector3D a) {
		return vector3D(y*a.z - z*a.y, z*a.x - x*a.z, x*a.y - y*a.x);
	}

	bool equal(vector3D a) {
		return x == a.x && y == a.y && z == a.z;
	}

	double len() {
		return sqrt(this->dot(*this));
	}

	bool len_eq(vector3D a) {
		return this->len() == a.len();
	}

	double angle(vector3D a) {
		if (this->len() == 0 || a.len() == 0) return 0;
		return acos(this->dot(a) / (this->len() * a.len()));
	}
};

int main() {
	vector3D a;
	printf("a = ");
	scanf("%d %d %d", &a.x, &a.y, &a.z);

	int x, y, z;
	printf("b = ");
	scanf("%d %d %d", &x, &y, &z);
	vector3D b(x, y, z);

	int n;
	printf("n = ");
	scanf("%d", &n);

	vector3D c(a.add(b));
	printf("a + b = (%d, %d, %d)\n", c.x, c.y, c.z);
	c = a.sub(b);
	printf("a - b = (%d, %d, %d)\n", c.x, c.y, c.z);

	c = b.mul(n);
	printf("b * n = (%d, %d, %d)\n", c.x, c.y, c.z);

	printf("(a, b) = %d\n", a.dot(b));

	c = a.cross(b);
	printf("[a, b] = (%d, %d, %d)\n", c.x, c.y, c.z);

	printf("(a == b) = %d\n", a.equal(b));

	printf("|a| = %lf\n", a.len());
	printf("|b| = %lf\n", b.len());

	printf("(|a| == |b|) = %d\n", a.len_eq(b));

	printf("angle(a, b) = %lf rad\n", a.angle(b));


}