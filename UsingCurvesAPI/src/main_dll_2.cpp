#include <vector>
#include <random>
#include <iostream>
#include <memory>
#include <omp.h>

//#include "3DCurves.h"
#include "3DCurves_dll_interface.h"
#include "LogDuration.h"


namespace solution {
	enum class CurveTypes {
		Circle,
		Ellipse,
		Helix3D
	};

	std::vector<std::shared_ptr<Curve3D>> PopulateCurves(std::mt19937& gen) {
		std::uniform_real_distribution<double> parameter(1.0, 10.0);
		std::uniform_int_distribution<int> num_of_curves(500000, 500000);
		std::uniform_int_distribution<int> curve_type(0, 0); // 3 types
			// Generate a random number of curves
		int numCurves = num_of_curves(gen);

		double radius, a, b, helix_radius, step; // parameters

		// Create a container of 3D curves with random parameters
		std::vector<std::shared_ptr<Curve3D>> curves;

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
				helix_radius = parameter(gen);
				step = parameter(gen);
				curves.push_back(std::make_shared<Helix3D>(helix_radius, step));
				break;
			}
		}

		return curves;
	}

	std::vector<std::shared_ptr<Circle>> PopulateCirclesSortedByRadius(const std::vector<std::shared_ptr<Curve3D>>& curves) {
		std::vector<std::shared_ptr<Circle>> circles;
		for (const auto& curve : curves) {
			if (Circle* circle = dynamic_cast<Circle*>(curve.get())) {
				circles.push_back(std::make_shared<Circle>(*circle));
			}
		}
		std::sort(circles.begin(), circles.end(), [](const std::shared_ptr<Circle>& lhs, const std::shared_ptr<Circle>& rhs) {
			return lhs->GetRadius() < rhs->GetRadius();
			});

		return circles;
	}

	// Print coordinates of points and derivatives at t = PI/4
	void PrintPointAndDerivative(const std::vector<std::shared_ptr<Curve3D>>& curves) {
		static const double t = PI / 4;
		for (const auto& curve : curves) {
			Point3D point = curve->GetPoint(t);
			Point3D derivative = curve->GetDerivative(t);
			std::cout << "Point: " << point << std::endl;
			std::cout << "Derivative: " << derivative << std::endl;
		}
	}

	void PrintCirclesRadiiTotalSum(const std::vector<std::shared_ptr<Circle>>& circles) {
		double total_sum = 0.0;
		using namespace std::string_literals;
		LOG_DURATION("parallel"s);
		{
			#pragma omp parallel for reduction(+:total_sum)
			for (const auto& circle : circles) {
				total_sum += circle->GetRadius();
			}
		}

		LOG_DURATION("non_parallel"s);
		{
			for (const auto& circle : circles) {
				total_sum += circle->GetRadius();
			}
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

	//solution::PrintPointAndDerivative(curves);
	solution::PrintCirclesRadiiTotalSum(circles);

	return 0;
}