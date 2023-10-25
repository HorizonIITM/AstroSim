#pragma once
/*
 * UTILS.H
 */
#ifndef UTILS_H_
#define UTILS_H_


long double Q_rsqrt(long double);
double      Q_rsqrt(double);

valtype distSquare(vector<valtype> p1, vector<valtype> p2);

vector<valtype> cross_product(vector<valtype>v1, vector<valtype>v2);

#endif