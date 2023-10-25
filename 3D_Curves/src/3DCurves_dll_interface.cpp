
#include "3DCurves_dll_interface.h"

#include <math.h>



Point3D Circle::GetPoint(double t) const {
	Point3D point;
	point.x = m_Radius * cos(t);
	point.y = m_Radius * sin(t);
	point.z = 0.0;
	return point;
}

Vector3D Circle::GetDerivative(double t) const {
	Vector3D derivative;
	derivative.x = -m_Radius * sin(t);
	derivative.y = m_Radius * cos(t);
	derivative.z = 0.0;
	return derivative;
}

Point3D Ellipse::GetPoint(double t) const {
	Point3D point;
	point.x = m_SemiMajorAxis * cos(t);
	point.y = m_SemiMinorAxis * sin(t);
	point.z = 0.0;
	return point;
}


Vector3D Ellipse::GetDerivative(double t) const {
	Vector3D derivative;
	derivative.x = -m_SemiMajorAxis * sin(t);
	derivative.y = m_SemiMinorAxis * cos(t);
	derivative.z = 0.0;
	return derivative;
}

Point3D Helix3D::GetPoint(double t) const {
	Point3D point;
	point.x = m_Radius * cos(t);
	point.y = m_Radius * sin(t);
	point.z = (m_Step / (2 * PI)) * t;
	return point;
}

Vector3D Helix3D::GetDerivative(double t) const {
	Vector3D derivative;
	derivative.x = -m_Radius * sin(t);
	derivative.y = m_Radius * cos(t);
	derivative.z = m_Step / (2 * PI);
	return derivative;
}
