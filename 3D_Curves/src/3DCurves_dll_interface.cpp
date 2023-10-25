
#include "3DCurves_dll_interface.h"

#include <math.h>

std::ostream& operator << (std::ostream& os, Point3D point) {
	os << "(" << point.x << ", " << point.y << ", " << point.z << ")";
	return os;
}



Point3D Circle::GetPoint(double t) const {
	Point3D point;
	point.x = m_Radius * cos(t);
	point.y = m_Radius * sin(t);
	point.z = 0.0;
	return point;
}

Point3D Circle::GetDerivative(double t) const {
	Point3D deriviative;
	deriviative.x = -m_Radius * sin(t);
	deriviative.y = m_Radius * cos(t);
	deriviative.z = 0.0;
	return deriviative;
}

Point3D Ellipse::GetPoint(double t) const {
	Point3D point;
	point.x = m_SemiMajorAxis * cos(t);
	point.y = m_SemiMinorAxis * sin(t);
	point.z = 0.0;
	return point;
}


Point3D Ellipse::GetDerivative(double t) const {
	Point3D deriviative;
	deriviative.x = -m_SemiMajorAxis * sin(t);
	deriviative.y = m_SemiMinorAxis * cos(t);
	deriviative.z = 0.0;
	return deriviative;
}

Point3D Helix3D::GetPoint(double t) const {
	Point3D point;
	point.x = m_Radius * cos(t);
	point.y = m_Radius * sin(t);
	point.z = (m_Step / (2 * PI)) * t;
	return point;
}

Point3D Helix3D::GetDerivative(double t) const {
	Point3D deriviative;
	deriviative.x = -m_Radius * sin(t);
	deriviative.y = m_Radius * cos(t);
	deriviative.z = m_Step / (2 * PI);
	return deriviative;
}




//struct curvesCurve3D {
//	curves::Curve3D curve;
//};
//
//struct curvesCircle {
//	curves::Circle circle;
//};
//
//struct curvesEllipse {
//	curves::Ellipse ellipse;
//};
//
//struct curvesHelix3D {
//	curves::Helix3D helix3d;
//};
//
//
//// Functions to create and destroy a Circle
//curvesCurve3D* CreateCircle(double radius) {
//	curves::Circle circle(radius);
//	return new curvesCurve3D{circle};
//}
//
//// Function to create an Ellipse
//curvesCurve3D* CreateEllipse(double a, double b) {
//	curves::Ellipse ellipse (a,b);
//	return new curvesCurve3D{ ellipse };
//}
//
//// Function to create a Helix
//curvesCurve3D* CreateHelix(double radius, double step) {
//	curves::Helix3D helix3d(radius,step);
//	return new curvesCurve3D{ helix3d };
//}
//double GetRadius(curvesCircle* circle) {
//	return circle->circle.GetRadius();
//}
//// Function to destroy a Curve3D object
//void DestroyCurve(curvesCurve3D* curve) {
//	delete curve;
//}
//
//// Function to get the point
//curvesPoint3D GetPoint(curvesCurve3D* curve, double t) {
//	curves::Point3D val = curve->curve.GetPoint(t);
//	curvesPoint3D& dll_val = reinterpret_cast<curvesPoint3D&>(val);
//	return dll_val;
//}
//
//// Function to get the derivative
//curvesPoint3D GetDerivative(curvesCurve3D* curve, double t) {
//	curves::Point3D val = curve->curve.GetDerivative(t);
//	curvesPoint3D& dll_val = reinterpret_cast<curvesPoint3D&>(val);
//	return dll_val;
//}

