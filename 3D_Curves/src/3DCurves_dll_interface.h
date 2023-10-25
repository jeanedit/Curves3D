#pragma once

#ifdef CURVES_DLL
#define CURVES3D_API __declspec(dllexport)
#else
#define CURVES3D_API __declspec(dllimport)
#endif

#define CURVES3D_EXPORT extern "C" CURVES3D_API

static const double PI = 3.14159265359;


struct Point3D {
	double x, y, z;
};

class CURVES3D_API Curve3D {
public:
	virtual Point3D GetPoint(double t) const = 0;
	virtual Point3D GetDerivative(double t) const = 0;
	virtual ~Curve3D() { }
};


class CURVES3D_API Circle : public Curve3D {
public:
	Circle(double radius)
		: m_Radius(radius) {}

	Point3D GetPoint(double t) const override;
	Point3D GetDerivative(double t) const override;
	inline double GetRadius() const {
		return m_Radius;
	}

private:
	double m_Radius;
};

class CURVES3D_API Ellipse :public Curve3D {
public:
	Ellipse(double a, double b)
		: m_SemiMajorAxis(a),
		m_SemiMinorAxis(b) {}

	Point3D GetPoint(double t) const override;
	Point3D GetDerivative(double t) const override;
private:
	double m_SemiMajorAxis;
	double m_SemiMinorAxis;
};

class CURVES3D_API Helix3D : public Curve3D {
public:
	Helix3D(double radius, double step)
		: m_Radius(radius),
		m_Step(step) {}

	Point3D GetPoint(double t) const override;
	Point3D GetDerivative(double t) const override;
private:
	double m_Radius;
	double m_Step;
};


