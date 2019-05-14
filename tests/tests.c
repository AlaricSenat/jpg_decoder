/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asenat <asenat@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 10:23:19 by asenat            #+#    #+#             */
/*   Updated: 2019/06/04 10:23:19 by asenat           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "jpg_decode.h"

#include <stdio.h>
int main() {
    // int16_t b[] = {0, 1,  2,  3,  4,   5,  6,  7,  8,  9,  10, 11, 12,
    //                13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
    //                26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
    //                39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,
    //                52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63};
    // int16_t b[] = {-26, -3, 0, -3, -2, -6, 2, -4, 1,  -3, 1, 1, 5, 1, 2, -1,
    //               1,   -1, 2, 0,  0,  0,  0, 0,  -1, -1, 0, 0, 0, 0, 0, 0,
    //               0,   0,  0, 0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0, 0,
    //               0,   0,  0, 0,  0,  0,  0, 0,  0,  0,  0, 0, 0, 0, 0, 0};
    // zigzag(b);
       int16_t b[] = {
           -416, -33, -60, 32,  48,  -40, 0, 0, 0,   -24, -56, 19,  26, 0, 0,
           0, -42,  13,  80,  -24, -40, 0,   0, 0, -42, 17,  44,  -29, 0,  0,
           0, 0, 18,   0,   0,   0,   0,   0,   0, 0, 0,   0,   0,   0,   0,
           0, 0, 0, 0,    0,   0,   0,   0,   0,   0, 0, 0,   0,   0,   0, 0,
           0, 0,
       };
    apply_inv_dct(b);
    print_block(b);
    //   unsigned w, h;
    //   uint8_t * a = jpg_decode("test.jpg", &w, &h);
    //	printf("img:\n");
    //   for (unsigned i = 0; i < w * h * 3; i += 3) {
    //	   printf("(%u, %u, %u) ", a[i], a[i + 1], a[i + 2]);
    //	   if (!(((i / 3) + 1) % w))
    //		   printf("\n");
    //   }
    //   return (0);
}