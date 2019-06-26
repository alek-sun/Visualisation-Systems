#pragma once
#include <math.h>


class Math
{
public:

	/**
	* @brief Clamps value by interval [min, max].
	* @param [in] number Number to be clamped.
	* @param [in] number If number is less than min then return min.
	* @param [in] number If number is greater than max then return max.
	*/
	static float Clamp(float number, float min, float max)
	{
		number = (number < min) ? min : number;
		number = (number > max) ? max : number;

		return number;
	}

	/**
	* @brief Clamps value by interval [min, max].
	* @param [in] number Number to be clamped.
	* @param [in] number If number is less than min then return min.
	* @param [in] number If number is greater than max then return max.
	*/
	static double Clamp(double number, double min, double max)
	{
		number = (number < min) ? min : number;
		number = (number > max) ? max : number;

		return number;
	}

	/**
	* @brief Clamps value by interval [min, max].
	* @param [in] number Number to be clamped.
	* @param [in] number If number is less than min then return min.
	* @param [in] number If number is greater than max then return max.
	*/
	static int Clamp(int number, int min, int max)
	{
		number = (number < min) ? min : number;
		number = (number > max) ? max : number;

		return number;
	}

	/**
	* @brief Return square root.
	* @param [in] number Number to take square root of.
	*/
	static double Sqrt(double number)
	{
		return sqrt( number );
	}

	/**
	* @brief Return absolute value of the number.
	* @param [in] number Number to take absolute value of.
	*/
	static double Abs(double number)
	{
		return fabs( number );
	}

	/**
	* @brief Return absolute value of the number.
	* @param [in] number Number to take absolute value of.
	*/
	static float Abs(float number)
	{
		return fabs( number );
	}
};
