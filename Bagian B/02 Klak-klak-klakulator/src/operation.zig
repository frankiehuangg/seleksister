const std = @import("std");

pub fn add(a: i32, b: i32) i32 {
    var sum: i32 = (a ^ b);
    var carry: i32 = (a & b) << 1;

    while (carry != 0) {
        var sum_temp = sum ^ carry;
        var carry_temp = (sum & carry) << 1;

        sum = sum_temp;
        carry = carry_temp;
    }

    return sum;
}

pub fn sub(a: i32, b: i32) i32 {
    return add(a, add(~(b), 1));
}

pub fn mul(a: i32, b: i32) i32 {
    var result: i32 = 0;

    var x: i32 = if (a < 0) (add(~(a), 1)) else a;
    var y: i32 = if (b < 0) (add(~(b), 1)) else b;

    var negative: bool = ((a < 0 and b >= 0) or (a >= 0 and b < 0));

    while (y > 0) {
        if (y & 1 == 1)
            result = add(result, x);

        x <<= 1;
        y >>= 1;
    }

    if (negative) {
        return add(~(result), 1);
    }

    return result;
}

pub fn div(a: i32, b: i32) i32 {
    if (b == 0) {
        std.process.exit(1);
    }

    var result: i32 = 0;

    var x: i64 = if (a < 0) (add(~(a), 1)) else a;
    var y: i64 = if (b < 0) (add(~(b), 1)) else b;

    var negative: bool = (a < 0 or b < 0);

    var i: u5 = 31;
    while (true) {
        if ((y << i) <= x) {
            x = sub(@intCast(x), @intCast((y << i)));
            result = add(result, (@as(i32, 1) << i));
        }
        i -%= 1;

        if (i == 31) {
            break;
        }
    }

    if (negative) {
        return add(~(result), 1);
    }

    return result;
}

pub fn pow(a: i32, b: i32) i32 {
    var result: i32 = 1;

    var i: i32 = b;
    while (i > 0) {
        result = mul(result, a);
        i = sub(i, 1);
    }

    return result;
}
