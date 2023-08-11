const std = @import("std");

const operation = @import("./operation.zig");

const Stack = struct {
    data: []i32,
    len: usize,

    fn push(self: *Stack, value: i32) void {
        if (self.len < self.data.len) {
            self.data[self.len] = value;
            self.len += 1;
        } else {
            @panic("Stack overflow!\n");
        }
    }

    fn pop(self: *Stack) i32 {
        if (self.len > 0) {
            var value: i32 = self.data[self.len - 1];
            self.len -= 1;
            return value;
        } else {
            @panic("Stack underflow!\n");
        }
    }
};

fn is_operator(char: u8) bool {
    return switch (char) {
        '+' => true,
        '-' => true,
        '*' => true,
        '/' => true,
        '^' => true,
        else => false,
    };
}

fn is_number(char: u8) bool {
    return switch (char) {
        '0' => true,
        '1' => true,
        '2' => true,
        '3' => true,
        '4' => true,
        '5' => true,
        '6' => true,
        '7' => true,
        '8' => true,
        '9' => true,
        else => false,
    };
}

pub fn main() !void {
    const stdin = std.io.getStdIn().reader();
    const stdout = std.io.getStdOut().writer();

    try stdout.print("Klak-klak-klakulator...\n", .{});
    try stdout.print("Only integer calculations are valid!\n\n", .{});
    try stdout.print("Please enter an expression, or type \"exit\" to quit.\n\n", .{});
    try stdout.print("An expression must be placed between two numbers seperated by a space\n", .{});
    try stdout.print("Valid expressions include: (+) (-) (*) (/) (^)\n\n", .{});
    try stdout.print("Examples of valid expressions:\n", .{});
    try stdout.print("- 5 + 3\n", .{});
    try stdout.print("- 10 - 7\n", .{});
    try stdout.print("- 4 * 6\n", .{});
    try stdout.print("- 18 / 3\n", .{});
    try stdout.print("- 2 ^ 4\n\n", .{});
    try stdout.print("Enter your expression: ", .{});

    var buffer: [128]u8 = undefined;

    var arena = std.heap.ArenaAllocator.init(std.heap.page_allocator);
    defer arena.deinit();

    const allocator = arena.allocator();

    var number: Stack = Stack{ .data = try allocator.alloc(i32, 128), .len = 0 };

    if (try stdin.readUntilDelimiterOrEof(buffer[0..], '\n')) |_| {
        var value: i32 = 0;

        var operator: u8 = ' ';
        for (0..128) |i| {
            if (number.len == 2) {
                var a: i32 = number.pop();
                var b: i32 = number.pop();

                try stdout.print("Trying to calculate {d} {c} {d}\n", .{ b, operator, a });

                var temp: i32 = switch (operator) {
                    '+' => operation.add(b, a),
                    '-' => operation.sub(b, a),
                    '*' => operation.mul(b, a),
                    '/' => operation.div(b, a),
                    '^' => operation.pow(b, a),
                    else => @panic("Unknown input!\n"),
                };

                number.push(temp);
            }

            if (buffer[i] == '\x0a') {
                break;
            } else if (is_operator(buffer[i])) {
                operator = buffer[i];
            } else if (is_number(buffer[i])) {
                value = value * 10 + (buffer[i] - 0x30);

                if (!is_number(buffer[i + 1])) {
                    number.push(value);
                    value = 0;
                }
            }
        }

        std.debug.assert(number.len == 1);

        try stdout.print("Result: {d}\n", .{number.pop()});
    }
}
