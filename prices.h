//
// Created by snowb on 22/02/2022.
//

#ifndef AssetPrice_h
#define AssetPrice_h

#include <cmath>
#include <fstream>
#include <iostream>
#include <list>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

//*********************
//	Asset Parent Class
//*********************
// Our basic virtual class
class Asset
{
public:
    Asset( void ) {};
    virtual ~Asset( void ) {};

    virtual double getValue( void )=0;
};

//*********************
//	Stock
//*********************
class Stock: public Asset
{
public:
    Stock( void );
    ~Stock( void );

    double getValue(void);
    void setValue(double price);
private:
    double StockPrice;
};


//****************************
//	Option
//****************************
class Option: public Asset
{
public:
    // Constructors/destructors
    Option( double strike0, double spot0, double sigma, double Time, double rate );
    virtual ~Option( );

    //  Black-Scholes Values
    /*double calc_d1(double S, double K, double r, double vix, double T);
    double calc_d2(double S, double K, double r, double vix, double T);*/
    double calc_d1(Stock& S, double K, double r, double vix, double T);
    double calc_d2(Stock& S, double K, double r, double vix, double T);
    double calc_CumNorm(double x);
    double calc_NormDens(double x);

    //  Data access
    double getStrike();
    double getSpot();
    double getVolatility();
    double getTime();
    double getRate();
    string getType();

    //  Values spots function
    void ValueSpots( double lowerSpotPrice, double upperSpotPrice, int numberOfSpots, string Name );

    //  virtual function to be used by each option.
    virtual double BlackScholesValue()=0;
    virtual double getValue()=0;
    virtual double getPayout(double, double )=0;

protected:
    //  protected variables
    Stock nowStock;
    double strike, spot, volatility, T, r;
    double d1, d2;
    string OptionType;
};





//**********************************
//	American Put
//**********************************
class AmericanPut: public Option
{
public:
    //  American call constructors
    AmericanPut( double strike0, double spot0, double sigma, double Time, double rate );
    ~AmericanPut( );

    //  Data access
    double BlackScholesValue( );
    double getValue();
    double getPayout( double S, double t );

private:
    //  Private varaibles
    double BSValue;
    double Value;
};

//****************************************
//	Binomial Tree
//****************************************
class binomialtree
{
public:
    //  Binomial Tree constructors
    binomialtree( void ) {};
    binomialtree( Option& nowOption );
    ~binomialtree( void );

    //  Data access
    void setstock( void );
    void setoption( Option& nowOption );
    double findval( void );
    vector<double> ExerciseBoundary( void );
    void setDelta( void );
    double finddelta( void );
    void setGamma( void );
    double findgamma( void );

private:

    double n, u, d, a, q, P0;
    double val;
    double delta, gamma;
    int size;
    vector<double> stockprices;
    vector<double> optionvalues;
    vector<double> boundary;
};




bool nextToken(const string& line, int& offset, string& token);


void ValueOptions( string inName, string outName );
void ValueDelta( string inName, string outName );



#endif
