/*
 * park_clarke.c
 *
 *  Created on: Dec 2, 2023
 *      Author: JohnYu
 */

#include "inverter_control/park_clarke.h"
#include <assert.h>
#include <stddef.h>
#include <math.h>

static const float sqrt3 = 1.732050807568877e+00;

void abc_to_clarke(const struct abc_vector *abc, struct clarke_vector *clarke)
{
    assert(abc != NULL);
    assert(clarke != NULL);

    clarke->alpha = (2.0 * abc->a - abc->b - abc->c) / 3.0;
    clarke->beta = (abc->b - abc->c) / sqrt3;
    clarke->gamma = (abc->a + abc->b + abc->c) / 3.0;
}

void clarke_to_abc(const struct clarke_vector *clarke, struct abc_vector *abc)
{
    assert(abc != NULL);
    assert(clarke != NULL);

    abc->a = clarke->alpha + clarke->gamma;
    abc->b = (-clarke->alpha + sqrt3 * clarke->beta) / 2.0 + clarke->gamma;
    abc->c = (-clarke->alpha - sqrt3 * clarke->beta) / 2.0 + clarke->gamma;
}

void clarke_to_park(const struct clarke_vector *clarke,
                    struct park_vector *park, const float radians)
{
    assert(clarke != NULL);
    assert(park != NULL);

    const float cos_val = cosf(radians);
    const float sin_val = sinf(radians);

    park->d = cos_val * clarke->alpha + sin_val * clarke->beta;
    park->q = -sin_val * clarke->alpha + cos_val * clarke->beta;
    park->z = clarke->gamma;
}

void park_to_clarke(const struct park_vector *park,
                    struct clarke_vector *clarke, const float radians)
{
    assert(clarke != NULL);
    assert(park != NULL);

    const float cos_val = cosf(radians);
    const float sin_val = sinf(radians);

    clarke->alpha = cos_val * park->d - sin_val * park->q;
    clarke->beta = sin_val * park->d + cos_val * park->q;
    clarke->gamma = park->z;
}

void abc_to_park(const struct abc_vector *abc, struct park_vector *park,
                 const float radians)
{
    struct clarke_vector clarke;

    abc_to_clarke(abc, &clarke);
    clarke_to_park(&clarke, park, radians);
}

