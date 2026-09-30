/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x | ~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x & ~y) & ~(x & y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    // 符号位相同，且是否为 0 也相同
    return !((x >> 31) ^ (y >> 31)) && !((!x) ^ (!y));
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    // 0xFFFF = (0xFF << 8) | 0xFF
    //
    // 另一种写法：用 (v >> k) > 0 代替和大常量比较，不需要大常量，21 个运算符
    // int result, move;
    // move = ((v >> 16) > 0) << 4; v = v >> move; result = move;
    // move = ((v >> 8) > 0) << 3; v = v >> move; result = result | move;
    // move = ((v >> 4) > 0) << 2; v = v >> move; result = result | move;
    // move = ((v >> 2) > 0) << 1; v = v >> move; result = result | move;
    // return result | (v >> 1);
    int result = 0;
    int move;
    move = (v > 0xFFFF) << 4;  // 最高位 1 在第 16 位以上？是则记 16
    v = v >> move;  // 把已确定的那一半移走
    result = result | move;
    move = (v > 0xFF) << 3;
    v = v >> move;
    result = result | move;
    move = (v > 0xF) << 2;
    v = v >> move;
    result = result | move;
    move = (v > 3) << 1;
    v = v >> move;
    result = result | move;
    return result | (v >> 1);  // 此时 v 只剩 1、2、3
}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int n8 = n << 3;
    int m8 = m << 3;
    int valueofn = (x >> n8) & 0xFF;  // 取出第 n 个字节
    int valueofm = (x >> m8) & 0xFF;  // 取出第 m 个字节
    int mask = ~((0xFF << n8) | (0xFF << m8));  // 把这两个字节的位置挖空
    return (x & mask) | (valueofn << m8) | (valueofm << n8);  // 交叉放回
}

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    // 分治版：
    // t = (0x55 << 8) | 0x55;  m1 = (t << 16) | t  // 0x55555555
    // t = (0x33 << 8) | 0x33;  m2 = (t << 16) | t  // 0x33333333
    // t = (0x0F << 8) | 0x0F;  m3 = (t << 16) | t  // 0x0F0F0F0F
    // m4 = (0xFF << 16) | 0xFF  // 0x00FF00FF
    // v = ((v >> 1) & m1) | ((v & m1) << 1);
    // v = ((v >> 2) & m2) | ((v & m2) << 2);
    // v = ((v >> 4) & m3) | ((v & m3) << 4);
    // v = ((v >> 8) & m4) | ((v & m4) << 8);
    // return (v >> 16) | (v << 16);
    unsigned result = 0;
    int count = 32;
    while (count) {  // 这题没有 <，用 count 是否减到 0 判断
        result = (result << 1) | (v & 1);  // result 腾出最低位，装入 v 的最低位
        v = v >> 1;  // v 丢掉已搬走的那位
        count = count - 1;
    }
    return result;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    // 掩码高 n 位为 0、其余为 1，清掉算术右移补上的符号位
    return (x >> n) & ~(((1 << 31) >> n) << 1);
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    // !(~x >> k) 为 1 表示 x 的高 32-k 位全是 1
    int count;
    int step;
    step = (!(~x >> 16)) << 4;
    count = step;
    x = x << step;  // 成立则记下 16 并把这 16 位移走
    step = (!(~x >> 24)) << 3;
    count = count + step;
    x = x << step;
    step = (!(~x >> 28)) << 2;
    count = count + step;
    x = x << step;
    step = (!(~x >> 30)) << 1;
    count = count + step;
    x = x << step;
    step = !(~x >> 31);
    count = count + step;
    x = x << step;
    return count + (!(~x >> 31));
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    // 0x80000000 = 1 << 31
    // 0x7FFFFF = (0x80 << 16) + ~0
    unsigned sign = 0;
    unsigned frac = x;
    unsigned tail;
    int exp = 158;  // 127 + 31
    if (!x) {
        return 0;
    }
    if (x < 0) {
        sign = 0x80000000;
        frac = ~frac + 1;  // 在无符号域取绝对值，避开 INT_MIN 溢出
    }
    while (!(frac >> 31)) {  // 把最高位的 1 对齐到 bit31
        frac = frac << 1;
        exp = exp - 1;
    }
    tail = frac & 0xFF;  // 23 位尾数之外被移出去的部分
    frac = (frac >> 8) & 0x7FFFFF;
    if (tail > 128) {  // 就近舍入，中间值取偶
        frac = frac + 1;
    } else if (tail == 128) {
        frac = frac + (frac & 1);
    }
    return sign + (exp << 23) + frac;  // 用 + 让尾数进位溢出到阶码
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    // 0x80000000 = 1 << 31
    // 0x7FFFFF = (0x80 << 16) + ~0
    // 0x7F800000 = 0xFF << 23
    // 0x800000 = 0x80 << 16
    unsigned exp = (uf >> 23) & 0xFF;
    unsigned sign = uf & 0x80000000;
    if (exp == 0xFF) {
        return uf;  // Inf / NaN
    }
    if (exp == 0) {
        return sign | ((uf & 0x7FFFFF) << 1);  // 非规格化数，尾数左移一位
    }
    if (exp == 0xFE) {
        return sign | 0x7F800000;  // 翻倍后溢出成 Inf
    }
    return uf + 0x800000;  // 阶码加一
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    // 0x7FF = (0x07 << 8) | 0xFF
    // 0xFFFFF = (0x0F << 16) | (0xFF << 8) | 0xFF
    // 0x100000 = 1 << 20
    // 0x80000000 = 1 << 31
    int exp = ((uf2 >> 20) & 0x7FF) - 1023;
    unsigned frac = (uf2 & 0xFFFFF) | 0x100000;  // 高字的 20 位尾数补上隐含的 1
    unsigned result;
    if (exp < 0) {
        return 0;
    }
    if (exp > 30) {
        return 0x80000000;  // 溢出，Inf / NaN 也落在这里
    }
    if (exp > 20) {
        result = (frac << (exp - 20)) | (uf1 >> (52 - exp));  // 整数部分跨到低字
    } else {
        result = frac >> (20 - exp);
    }
    if (uf2 >> 31) {
        result = ~result + 1;
    }
    return result;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    // 0x7F800000 = 0xFF << 23
    if (x < -149) {
        return 0;
    }
    if (x < -126) {
        return 1 << (x + 149);  // 非规格化区
    }
    if (x < 128) {
        return (x + 127) << 23;  // 规格化数
    }
    return 0x7F800000;  // +INF
}
