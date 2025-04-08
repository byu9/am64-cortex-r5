/*
 * park_clarke.h
 *
 *  Created on: Dec 2, 2023
 *      Author: JohnYu
 */

#ifndef HC2116D89_F19E_4803_AD6B_A8DC87EC430E
#define HC2116D89_F19E_4803_AD6B_A8DC87EC430E

struct abc_vector
{
    float a;
    float b;
    float c;
};

struct clarke_vector
{
    float alpha;
    float beta;
    float gamma;
};

struct park_vector
{
    float d;
    float q;
    float z;
};

void abc_to_clarke(const struct abc_vector *abc, struct clarke_vector *clarke);

void clarke_to_abc(const struct clarke_vector *clarke, struct abc_vector *abc);

void clarke_to_park(const struct clarke_vector *clarke,
                    struct park_vector *park, const float radians);

void park_to_clarke(const struct park_vector *park,
                    struct clarke_vector *clarke, const float radians);

void abc_to_park(const struct abc_vector *abc, struct park_vector *park,
                 const float radians);

#endif /* HC2116D89_F19E_4803_AD6B_A8DC87EC430E */
