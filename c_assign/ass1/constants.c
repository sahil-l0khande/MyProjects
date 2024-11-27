#include <stdio.h>

#define MY_PI 3.1415926535897932

#define AMC_STRING "AstroMediComp RTR"

enum
{
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY,
};

enum
{
	JANUARY = 1,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	OCTOMBER,
	NOVEMBER,
	DECEMBER
};

enum Numbers
{
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE = 5,
	SIX,
	SEVEN,
	EIGHT,
	NINE,
	TEN
};

enum boolean
{
	TRUE = 1,
	FALSE = 0
};

int main(void)
{
	// loacal constant declarations
	const double epsilon = 0.000001;

	// code
	printf("\n\n");
	printf("Local constant epsilon = %lf\n\n", epsilon);

	printf("Sunday is day number = %d\n", SUNDAY);
	printf("Monday is day number = %d\n", MONDAY);
	printf("Tuesday is day number = %d\n", TUESDAY );
	printf("WEDNESDAY is day number = %d\n", WEDNESDAY);
	printf("THURSDAY is day number = %d\n", THURSDAY);
	printf("FRIDAY is day number = %d\n", FRIDAY);
	printf("Saturday is day number = %d\n\n", SATURDAY);

	printf("ONE is enum number = %d\n",ONE); 
	printf("TWO is enum number = %d\n",TWO);
	printf("THREE is enum number = %d\n",THREE);
	printf("FOUR is enum number = %d\n",FOUR);
	printf("FIVE is enum number = %d\n",FIVE);
	printf("SIX is enum number = %d\n",SIX);
	printf("SEVEN is enum number = %d\n",SEVEN);
	printf("EIGHT is enum number = %d\n",EIGHT);
	printf("NINE is enum number = %d\n",NINE);
	printf("TEN is enum number = %d\n\n",TEN);
	
	printf("JANUARY is month number = %d\n", JANUARY);  
	printf("FEBRUARY is month number = %d\n", FEBRUARY); 
	printf("MARCH is month number = %d\n", MARCH); 
	printf("APRIL is month number = %d\n", APRIL); 
	printf("MAY is month number = %d\n", MAY); 
	printf("JUNE is month number = %d\n", JUNE); 
	printf("JULY is month number = %d\n", JULY); 
	printf("AUGUST is month number = %d\n", AUGUST); 
	printf("SEPTEMBER is month number = %d\n", SEPTEMBER); 
	printf("OCTOMBER is month number = %d\n", OCTOMBER); 
	printf("NOVEMBER is month number = %d\n", NOVEMBER); 
	printf("DECEMBER is month number = %d\n\n", DECEMBER); 
	
	printf("Value of TURE is = %d\n", TRUE);
	printf("Value of FALSE is = %d\n\n", FALSE);
	
	printf("MY_PI Macro value = %.10lf\n\n", MY_PI);
	printf("Area of circle of radius 2 units = %f\n\n", (MY_PI * 2.0f * 2.0f)); // pi * r * r = area of circle of radius 'r'
	
	printf("\n\n");
	
	printf(AMC_STRING);
	printf("\n\n");
	
	printf("AMC_STRING is = %s\n", AMC_STRING);
	printf("\n\n");
	
	return (0);
}