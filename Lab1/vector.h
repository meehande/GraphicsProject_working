#include "math.h"
namespace Mathematics {
/****************************************************************************************
*****************************************************************************************

	Creation Date: 01/06/2013

	Vector in 3-space Class
		-This quaternion class is generic and may be non-unit, however most anticipated 
		uses of quaternions are typically unit cases representing a rotation 2*acos(w) about 
		the axis (x,y,z).

		-The classes Vector4 and Vector2 are not fully implemented, as we are generally only
		using them as helpers for assignment, i.e when OpenGL is expecting a vec4

*****************************************************************************************
****************************************************************************************/
class Vector3 {

public:

    // default constructor.
    Vector3() {}

    // construct vector from x,y,z components.
    Vector3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // set vector to zero.
    void zero() {
        x = 0;
        y = 0;
        z = 0;
    }

    // negate vector.
	void negate() {
		x = -x;
		y = -y;
		z = -z;
	}

    // add another vector to this vector.
    void add(const Vector3 &v) {
        x += v.x;
        y += v.y;
        z += v.z;
    }

    // subtract another vector from this vector.
    void subtract(const Vector3 &v) {
        x -= v.x;
        y -= v.y;
        z -= v.z;
    }

    // multiply this vector by a scalar.
    void multiply(float scalar) {
        x *= scalar;
        y *= scalar;
        z *= scalar;
    }

    // divide this vector by a scalar.
	void divide(float scalar) {
		assert(scalar!=0);
		const float inv = 1.0f / scalar;
		x *= inv;
		y *= inv;
		z *= inv;
	}

    /// calculate dot product of this vector with another vector.

    float dot(const Vector3 &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    // calculate cross product of this vector with another vector.
	Vector3 cross(const Vector3 &v) const {
        return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    // calculate cross product of this vector with another vector, store result in parameter.
	void cross(const Vector3 &v, Vector3 &result) const {
        result.x = y * v.z - z * v.y;
        result.y = z * v.x - x * v.z;
        result.z = x * v.y - y * v.x;
    }

    // calculate length of vector squared
    float lengthSquared() const {
        return x*x + y*y + z*z;
    }

    // calculate length of vector.
    float length() const {
		return sqrt(x*x + y*y + z*z);
    }

    // normalize vector and return reference to normalized self.
    Vector3& normalize() {
        const float magnitude = sqrt(x*x + y*y + z*z);
        if (magnitude>epsilon) {
            const float scale = 1.0f / magnitude;
            x *= scale;
            y *= scale;
            z *= scale;
        }
		return *this;
    }

    // return unit length vector
    Vector3 unit() const
    {
        Vector3 v(*this);
        v.normalize();
        return v;
    }

    // test if vector is normalized.
	bool normalized() const {
		return equal(length(),1);
	}

    // equals operator
	bool operator ==(const Vector3 &other) const {
		if (equal(x,other.x) && equal(y,other.y) && equal(z,other.z)) 
			return true;
		else 
			return false;
	}

    // not equals operator
	bool operator !=(const Vector3 &other) const {
		return !(*this==other);
	}

    // element access
    float& operator [](int i) {
        assert(i>=0);
        assert(i<=2);
        return *(&x+i);
    }

    /// element access (const)
    const float& operator [](int i) const {
        assert(i>=0);
        assert(i<=2);
        return *(&x+i);
    }

	friend inline Vector3 operator-(const Vector3 &a);
	friend inline Vector3 operator+(const Vector3 &a, const Vector3 &b);
	friend inline Vector3 operator-(const Vector3 &a, const Vector3 &b);
	friend inline Vector3 operator*(const Vector3 &a, const Vector3 &b);
	friend inline Vector3& operator+=(Vector3 &a, const Vector3 &b);
	friend inline Vector3& operator-=(Vector3 &a, const Vector3 &b);
	friend inline Vector3& operator*=(Vector3 &a, const Vector3 &b);

	friend inline Vector3 operator*(const Vector3 &a, float s);
	friend inline Vector3 operator/(const Vector3 &a, float s);
	friend inline Vector3& operator*=(Vector3 &a, float s);
	friend inline Vector3& operator/=(Vector3 &a, float s);
	friend inline Vector3 operator*(float s, const Vector3 &a);
	friend inline Vector3& operator*=(float s, Vector3 &a);

    float x;        ///< x component of vector
    float y;        ///< y component of vector
    float z;        ///< z component of vector
};


inline Vector3 operator-(const Vector3 &a) {
	return Vector3(-a.x, -a.y, -a.z);
}

inline Vector3 operator+(const Vector3 &a, const Vector3 &b) {
	return Vector3(a.x+b.x, a.y+b.y, a.z+b.z);
}

inline Vector3 operator-(const Vector3 &a, const Vector3 &b) {
	return Vector3(a.x-b.x, a.y-b.y, a.z-b.z);
}

inline Vector3 operator*(const Vector3 &a, const Vector3 &b) {
	return Vector3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}

inline Vector3& operator+=(Vector3 &a, const Vector3 &b) {
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return a;
}

inline Vector3& operator-=(Vector3 &a, const Vector3 &b) {
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return a;
}

inline Vector3& operator*=(Vector3 &a, const Vector3 &b) {
    const float cx = a.y * b.z - a.z * b.y;
    const float cy = a.z * b.x - a.x * b.z;
    const float cz = a.x * b.y - a.y * b.x;
	a.x = cx;
	a.y = cy;
	a.z = cz;
	return a;
}

inline Vector3 operator*(const Vector3 &a, float s) {
	return Vector3(a.x*s, a.y*s, a.z*s);
}

inline Vector3 operator/(const Vector3 &a, float s) {
	assert(s!=0);
	return Vector3(a.x/s, a.y/s, a.z/s);
}

inline Vector3& operator*=(Vector3 &a, float s) {
	a.x *= s;
	a.y *= s;
	a.z *= s;
	return a;
}

inline Vector3& operator/=(Vector3 &a, float s) {
	assert(s!=0);
	a.x /= s;
	a.y /= s;
	a.z /= s;
	return a;
}

inline Vector3 operator*(float s, const Vector3 &a) {
	return Vector3(a.x*s, a.y*s, a.z*s);
}

inline Vector3& operator*=(float s, Vector3 &a) {
	a.x *= s;
	a.y *= s;
	a.z *= s;
	return a;
}

//Vector class, used primarily for interfacing with openGL
class Vector4 {

public:

    // default constructor.
    Vector4() {}

    // construct vector from x,y,z components.
    Vector4(float x, float y, float z, float w) {
        this->x = x;
        this->y = y;
        this->z = z;
		this->w = w;
    }

	// construct vector from x,y,z components.
    Vector4(Vector3 &v, float w) {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
		this->w = w;
    }

	float x;        // x component of vector
    float y;        // y component of vector
    float z;        // z component of vector
	float w;		// w component of vector
};

//Vector2 Class, should be extended for 2D applications
class Vector2 {

public:

    // default constructor.
    Vector2() {}

    // construct vector from x,y,z components.
    Vector2(float x, float y) {
        this->x = x;
        this->y = y;
    }

	float x;        // x component of vector
    float y;        // y component of vector
};
}