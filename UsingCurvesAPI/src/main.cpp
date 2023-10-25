#include <vector>
#include <random>
#include <iostream>
#include <memory>
#include <omp.h>
#include <iomanip>


#include "3DCurves_dll_interface.h"
#include "LogDuration.h"


namespace solution {
	using CurveShrPtr = std::shared_ptr<Curve3D>;
	using CircleShrPtr = std::shared_ptr<Circle>;
	using EllipseShrPtr = std::shared_ptr<Ellipse>;	
	using HelixShrPtr = std::shared_ptr<Helix3D>;

	std::ostream& operator << (std::ostream& os, Point3D point) {
		os << std::fixed << std::setprecision(6) << "("  << point.x << ", " << point.y << ", " << point.z << ")";
		return os;
	}

	std::ostream& operator << (std::ostream& os, Vector3D vector) {
		os << std::fixed << std::setprecision(6) << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
		return os;
	}


	enum class CurveTypes {
		Circle,
		Ellipse,
		Helix3D
	};

	std::vector<CurveShrPtr> PopulateCurves(std::mt19937& gen) {
		std::uniform_real_distribution<double> parameter(1.0, 100.0);
		std::uniform_int_distribution<int> num_of_curves(10, 1000);
		std::uniform_int_distribution<int> curve_type(0, 2); // 3 types
		// Generate a random number of curves
		int numCurves = num_of_curves(gen);

		double radius, a, b, step; // parameters

		// Create a container of 3D curves with random parameters
		std::vector<CurveShrPtr> curves;

		for (int i = 0; i < numCurves; i++) {
			CurveTypes type = static_cast<CurveTypes>(curve_type(gen));
			switch (type) {
			case CurveTypes::Circle:
				radius = parameter(gen);
				curves.push_back(std::make_shared<Circle>(radius));
				break;
			case CurveTypes::Ellipse:
				a = parameter(gen);
				b = parameter(gen);
				curves.push_back(std::make_shared<Ellipse>(a, b));
				break;
			case CurveTypes::Helix3D:
				radius = parameter(gen);
				step = parameter(gen);
				curves.push_back(std::make_shared<Helix3D>(radius, step));
				break;
			}
		}

		return curves;
	}

	std::vector<CircleShrPtr> PopulateCirclesSortedByRadius(const std::vector<CurveShrPtr>& curves) {
		std::vector<CircleShrPtr> circles;
		for (const auto& curve : curves) {
			if (CircleShrPtr circle = std::dynamic_pointer_cast<Circle>(curve)) {
				circles.push_back(circle);
			}
		}
		std::sort(circles.begin(), circles.end(), [](const CircleShrPtr& lhs, const CircleShrPtr& rhs) {
			return lhs->GetRadius() < rhs->GetRadius();
			});

		return circles;
	}

	// Print coordinates of points and derivatives at t = PI/4
	void PrintPointAndDerivative(const std::vector<CurveShrPtr>& curves) {
		static const double t = PI / 4;

		for (const auto& curve : curves) {
			if (CircleShrPtr circle = std::dynamic_pointer_cast<Circle>(curve)) {
				std::cout << "Circle" << std::endl;
			}
			else if (EllipseShrPtr ellipse = std::dynamic_pointer_cast<Ellipse>(curve))  {
				std::cout << "Ellipse" << std::endl;
			} 
			else {
				std::cout << "Helix3D" << std::endl;
			}

			Point3D point = curve->GetPoint(t);
			Vector3D derivative = curve->GetDerivative(t);
			std::cout << "Point: " << point << std::endl;
			std::cout << "Derivative: " << derivative << std::endl;
		}
	}

	void PrintCirclesRadiiTotalSum(const std::vector<CircleShrPtr>& circles) {
		using namespace std::string_literals;
		double total_sum = 0.0;

		#pragma omp parallel for reduction(+:total_sum)
		for (const auto& circle : circles) {
			total_sum += circle->GetRadius();
		}

		std::cout << "Total Radius: " << total_sum << std::endl;
	}
}


int main() {
	// Initialize random number generator
	std::random_device rd;
	std::mt19937 gen(rd());

	auto curves = solution::PopulateCurves(gen);
	auto circles = solution::PopulateCirclesSortedByRadius(curves);

	solution::PrintPointAndDerivative(curves);
	solution::PrintCirclesRadiiTotalSum(circles);

	return 0;
}