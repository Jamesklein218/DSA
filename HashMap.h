//
// Created by Khoa on 20/12/2022.
//

#ifndef DSALAB_HASHMAP_H
#define DSALAB_HASHMAP_H

/*
 * Implementation of Hash Map
 *
 *      1) Hash function=:
 *          - Direct hashing (
 *          - Modulo division: hash(k) = (k + c) % M
 *              If M is a prime number, the chance of collision is low
 *          - Digit extraction: Pre-known key design
 *          - Mid-square: hash(k) = mid(k^2)
 *          - Folding: hash(123 | 456 | 789) = (123 + 456 + 987) % M -> side folding
 *          - Rotation: hash(123456) -> hash(234561)
 *          - Pseudo-random: hash(k) -> (k * a + b) % m (a, b, m are prime number)
 *      2) Resolve collision:
 *          - Open addressing
 *              - p: probe number from 0 to M
 *              - hashProbe: hp(k, p) = (h(k) + p) % M
 *              - linear Probing
 *              - quadratic probing: hp(k,p) = (h(k) + p*p) % M
 *              - double hasing: hp(k, p) = (h1(k) + p * h2(k)) % M
 *              - Offset hashing: hp(k, p) = (h1(k) + p * (k / M)) % M
 *          - Closed addressing (Linked-List)
 *      3) Cuckoo hashing function O(1) worst case:
 *          - 2 hash table: h1(k) = k % M; h2(k) = (k / M) % M
 *      4) Secure hashing function (e.g. MD5)
 */
class HashMap {

};

#endif //DSALAB_HASHMAP_H
