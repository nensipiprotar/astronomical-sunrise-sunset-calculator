#include <stdio.h>
#include <math.h>

/* ---------- CONSTANTS ---------- */
#define PI 3.141592653589793
#define DEG2RAD(x) ((x) * PI / 180.0)
#define RAD2DEG(x) ((x) * 180.0 / PI)

/* Astronomical constants */
#define SUN_ALTITUDE   (-0.83)   // Refraction + Sun radius (degrees)
#define STD_MERIDIAN   (82.5)    // India Standard Meridian (degrees)

/* ---------- LEAP YEAR CHECK ---------- */
int isLeapYear(int year)
{
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

/* ---------- DAY OF YEAR ---------- */
int dayOfYear(int d, int m, int y)
{
    int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
    int i, N = d;

    if (isLeapYear(y))
        daysInMonth[1] = 29;

    for (i = 0; i < m - 1; i++)
        N += daysInMonth[i];

    return N;
}

/* ---------- SUNRISE / SUNSET CALCULATION ---------- */
void calculateSunriseSunset(double latitude, double longitude,
                            int day, int month, int year)
{
    int N = dayOfYear(day, month, year);

    /* Step 1: Solar Declination */
    double declination =
        23.45 * sin(DEG2RAD((360.0 / 365.0) * (N - 81)));

    /* Step 2: Hour Angle */
    double latRad = DEG2RAD(latitude);
    double decRad = DEG2RAD(declination);
    double h0Rad  = DEG2RAD(SUN_ALTITUDE);

    double cosH =
        (sin(h0Rad) - sin(latRad) * sin(decRad)) /
        (cos(latRad) * cos(decRad));

    if (cosH > 1.0 || cosH < -1.0)
    {
        printf("\nSun does not rise or set on this date at this location.\n");
        return;
    }

    double H = RAD2DEG(acos(cosH));

    /* Step 3: Hour Angle → Time */
    double deltaT = H / 15.0;

    /* Step 4: Solar Times */
    double solarSunrise = 12.0 - deltaT;
    double solarSunset  = 12.0 + deltaT;

    /* Step 5: Longitude Correction (IST already included) */
    double longitudeCorrection =
        (STD_MERIDIAN - longitude) / 15.0;

    /* Step 6: Equation of Time */
    double B = DEG2RAD((360.0 / 365.0) * (N - 81));
    double EoT =
        9.87 * sin(2 * B) -
        7.53 * cos(B) -
        1.5  * sin(B);   // minutes

    /* Step 7: FINAL IST TIMES (NO extra timezone add) */
    double sunriseIST =
        solarSunrise + longitudeCorrection - (EoT / 60.0);

    double sunsetIST =
        solarSunset  + longitudeCorrection - (EoT / 60.0);

    /* Normalize to 0–24 hours */
    if (sunriseIST < 0) sunriseIST += 24;
    if (sunsetIST  < 0) sunsetIST  += 24;
    if (sunriseIST >= 24) sunriseIST -= 24;
    if (sunsetIST  >= 24) sunsetIST  -= 24;

    /* Convert to HH:MM */
    int srHour = (int)sunriseIST;
    int srMin  = (int)((sunriseIST - srHour) * 60);

    int ssHour = (int)sunsetIST;
    int ssMin  = (int)((sunsetIST - ssHour) * 60);

    /* OUTPUT */
    printf("\nSunrise : %02d:%02d IST", srHour, srMin);
    printf("\nSunset  : %02d:%02d IST\n", ssHour, ssMin);
}

/* ---------- MAIN ---------- */
int main()
{
    double latitude, longitude;
    int day, month, year;

    printf("Enter Latitude  (degrees) : ");
    scanf("%lf", &latitude);

    printf("Enter Longitude (degrees) : ");
    scanf("%lf", &longitude);

    printf("Enter Date (DD MM YYYY)   : ");
    scanf("%d %d %d", &day, &month, &year);

    calculateSunriseSunset(latitude, longitude, day, month, year);

    return 0;
}
