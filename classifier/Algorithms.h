#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include <vector>
#include <string>
#include <map>

// Vector utility functions

/**
 * the '-' operator.
 * @param v a vector
 * @return the vector reversed
 */
const std::vector<double> operator-(const std::vector<double>& v);

/**
 * the '+' operator.
 * @param v a vector
 * @param u another vector
 * @return the sum of the two vectors (u + v)
 */
const std::vector<double> operator+(const std::vector<double>& v, const std::vector<double>& u);

/**
 * the '-' operator.
 * @param v a vector
 * @param u another vector
 * @return the vector's subtraction (u - v)
 */
const std::vector<double> operator-(const std::vector<double>& u, const std::vector<double>& v);

/**
 * the '*' operator.
 * @param t a scalar
 * @param v a vector
 * @return the product of the scalar t and v (t * v)
 */
const std::vector<double> operator*(double t, const std::vector<double>& v);

/**
 * the '*' operator.
 * @param v a vector
 * @param t a scalar
 * @return the product of the scalar t and v (v * t)
 */
const std::vector<double> operator*(const std::vector<double>& v, double t);

/**
 * the '/' operator.
 * @param t a scalar
 * @param v a vector
 * @return the vector, multiplied by the inverse of the scalar t (t^-1 * v)
 */
const std::vector<double> operator/(const std::vector<double>& v, double t);

/**
 * @return the length of the vector
 */
double len(const std::vector<double>& v);

// Other utility functions

/**
 * @param str a string
 * @return whether the string is a valid double
 */
bool isDouble(const std::string& str);

/**
 * find the key of the maximum value of a map
 * @param map a map between strings and integers
 * @return the key with the maximum value
 */
std::string maxKey(const std::map<std::string, int>& map);

/**
 * split the line into the substrings that are divided by the delimiter, ignoring
 * end of line characters.
 * @param line a line
 * @param delim a delimiter to split by
 * @return the resulting substrings
 */
std::vector<std::string> split(const std::string& str, char delim);

/**
 * @param a a lower bound
 * @param b an upper bound
 * @return a random real number in [a,b]
 */
int random(int a, int b);

/**
 * swap two pairs of double and integer.
 * @param p1 a reference to a pair
 * @param p2 a reference to another pair
 */
void swap(std::pair<double,int>& p1, std::pair<double,int>& p2);

// Algorithms

/**
 * group v[left...right] into two parts: those smaller than v[pivot] and those bigger than v[pivot].
 * @param v a vector of real numbers, paired with their original indices
 * @param left a lower bound on the indices
 * @param right an upper bound on the indices
 * @param pivot a pivot
 * @return the new index of v[pivot]
 */
static int partition(std::vector<std::pair<double,int>>& v, int left, int right, int pivot);

/**
 * @param v a vector of real numbers, paired with their original indices
 * @param left a lower bound on the indices
 * @param right an upper bound on the indices
 * @param k an integer s.t left <= k <= right
 * @return the k-th smallest element of v[left...right]
 */
static double quickSelect(std::vector<std::pair<double,int>>& v, int left, int right, int k);

/**
 * @param k an integer
 * @return the indices of the k-th smallest elements of the array
 */
std::vector<int> kSmallestElements(const std::vector<double>& v, int k);

/**
 * splits a given string to lines.
 * @return vector of the lines
 */
std::vector<std::string> fromParagraphToLines(std::string& str);

#endif
