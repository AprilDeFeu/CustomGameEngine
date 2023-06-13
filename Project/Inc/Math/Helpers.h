#pragma once
#include <iostream>
#include <string>
#include <cfloat>
#include <cmath>

using namespace std;

#define PI 3.141592653589793

/*!
 * @brief Prints a message to the console. Several overrides available
 *        to print native data types
 * @param s The string to print
 */
inline void Print(string s) {cout << s << endl;}
/*!
 * @brief Prints a message to the console. Several overrides available
 *        to print native data types
 * @param f The float to print
 */
inline void Print(float f) {Print(to_string(f));}
/*!
 * @brief Prints a message to the console. Several overrides available
 *        to print native data types
 * @param f The double to print
 */
inline void Print(double f) {Print(to_string(f));}
/*!
 * @brief Prints a message to the console. Several overrides available
 *        to print native data types
 * @param i The integer to print
 */
inline void Print(int i) {Print(to_string(i));}
/*!
 * @brief Prints a message to the console. Several overrides available
 *        to print native data types
 * @param i The long to print
 */
inline void Print(long i) {Print(to_string(i));}
/*!
 * @brief Prints a message to the console. Several overrides available
 *        to print native data types
 * @param i The long long to print
 */
inline void Print(long long i) {Print(to_string(i));}
/*!
 * @brief Prints a message to the console. Several overrides available
 *        to print native data types
 * @param i The unsigned integer to print
 */
inline void Print(unsigned int i) {Print(to_string(i));}
/*!
 * @brief Prints a message to the console. Several overrides available
 *        to print native data types
 * @param i The unsigned long to print
 */
inline void Print(unsigned long i) {Print(to_string(i));}
/*!
 * @brief Prints a message to the console. Several overrides available
 *        to print native data types
 * @param i The unsigned long long to print
 */
inline void Print(unsigned long long i) {Print(to_string(i));}
/*!
 * @brief Prints a message to the console. Several overrides available
 *        to print native data types
 * @param c The character to print
 */
inline void Print(char c) {Print(to_string(c));}

/*!
 * @brief Due to float precision issues, this function will replace
 *        float equality checks in Vectors. As we are building a
 *        game engine, we can afford to lose precision for the sake
 *        of mathematical accuracy and consistency.
 * @param a Float to compare
 * @param b Float to compare
 * @return [bool] Boolean indicating if the two floats are less than
 *        0.00001f away from each other
 */
inline bool CloseFloat(float a, float b) {return (fabs(a - b) <= 0.00001f);}

/*!
 * @brief Backend wrapper for tail-recursion based power function
 * @param base The base value to exponentiate
 * @param exponent The exponent
 * @param accumulator Accumulator for tail recursion
 * @return [double] base^exponent : base to the power of exponent
 */
double Power(double base, int exponent, double accumulator);