use crate::fileutil;

pub fn process() {
    let input = fileutil::read_char_grid("./input/day04.txt");
    part1(&input);
    part2(&input);
}
const DIRECTIONS: [(i32, i32); 8] = [
    (0, -1),  // 上
    (1, 0),   // 右
    (0, 1),   // 下
    (-1, 0),  // 左
    (1, -1),  // 右上
    (1, 1),   // 右下
    (-1, 1),  // 左下
    (-1, -1), // 左上
];
const TARGET: &str = "XMAS";

fn part1(input: &[Vec<char>]) {
    let rows = input.len();
    let cols = input[0].len();

    // 从每个位置出发，检查所有方向
    let count: usize = input
        .iter()
        .enumerate()
        .flat_map(|(i, row)| {
            row.iter().enumerate().filter_map(move |(j, &c)| {
                if c == 'X' {
                    // 只检查以 'X' 开头的位置
                    Some((i, j))
                } else {
                    None
                }
            })
        })
        .map(|(i, j)| check_all_directions(input, i, j, rows, cols))
        .sum();

    println!("Day 04 Part 1: {}", count);
}

/// 检查从某个位置出发的所有方向
fn check_all_directions(
    input: &[Vec<char>],
    i: usize,
    j: usize,
    rows: usize,
    cols: usize,
) -> usize {
    DIRECTIONS
        .iter()
        .filter(|&&(dx, dy)| {
            // 检查是否可以在这个方向上形成 "XMAS"
            check_direction(input, i, j, dx, dy, rows, cols)
        })
        .count()
}

/// 检查单一方向是否能形成 "XMAS"
fn check_direction(
    input: &[Vec<char>],
    i: usize,
    j: usize,
    dx: i32,
    dy: i32,
    rows: usize,
    cols: usize,
) -> bool {
    // 第一个字符已经检查过是 'X'，只需检查后面三个字符
    let mut chars = Vec::with_capacity(4);
    chars.push('X'); // 起始位置已确认是 'X'

    let mut x = i as i32;
    let mut y = j as i32;

    // 检查接下来的3个位置
    for _ in 0..3 {
        x += dx;
        y += dy;

        if x < 0 || x >= rows as i32 || y < 0 || y >= cols as i32 {
            return false; // 超出边界
        }

        chars.push(input[x as usize][y as usize]);
    }

    // 检查是否形成 "XMAS"
    chars.iter().collect::<String>() == TARGET
}

fn part2(input: &[Vec<char>]) {
    let rows = input.len();
    let cols = input[0].len();

    let mut count = 0;
    for i in 1..rows - 1 {
        for j in 1..cols - 1 {
            if input[i][j] == 'A' && valid_mas(input, i, j) {
                count += 1;
            }
        }
    }
    println!("Day 04 Part 1: {}", count);
}

fn valid_mas(input: &[Vec<char>], i: usize, j: usize) -> bool {
    let mut b1 = false;
    let mut b2 = false;
    if input[i - 1][j - 1] == 'M' && input[i + 1][j + 1] == 'S' {
        b1 = true;
    }
    if input[i - 1][j - 1] == 'S' && input[i + 1][j + 1] == 'M' {
        b1 = true;
    }
    if input[i - 1][j + 1] == 'M' && input[i + 1][j - 1] == 'S' {
        b2 = true;
    }
    if input[i - 1][j + 1] == 'S' && input[i + 1][j - 1] == 'M' {
        b2 = true;
    }

    b1 && b2
}
