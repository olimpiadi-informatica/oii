use std::collections::VecDeque;
use std::io::stdin;

fn parse_vec_usize() -> Vec<usize> {
    let mut buffer = String::new();
    stdin().read_line(&mut buffer).unwrap();
    buffer
        .trim()
        .split(" ")
        .map(|x| x.parse().unwrap())
        .collect()
}

fn main() {
    let mut buffer = String::new();
    stdin().read_line(&mut buffer).unwrap();
    let t: usize = buffer.trim().parse().unwrap();
    for c in 0..t {
        stdin().read_line(&mut buffer).unwrap();
        let params = parse_vec_usize();
        let mut values = vec![0; params[0] * params[1]];
        let mut graph = vec![Vec::new(); params[0] * params[1]];
        for i in 0..params[0] {
            let row = parse_vec_usize();
            for j in 0..params[1] {
                let node = |i, j| i * params[1] + j;
                values[node(i, j)] = row[j];
                if i != 0 {
                    graph[node(i, j)].push(node(i - 1, j));
                }
                if i != params[0] - 1 {
                    graph[node(i, j)].push(node(i + 1, j));
                }
                if j != 0 {
                    graph[node(i, j)].push(node(i, j - 1));
                }
                if j != params[1] - 1 {
                    graph[node(i, j)].push(node(i, j + 1));
                }
            }
        }
        println!("Case #{}: {}", c + 1, solve(&values, &graph));
    }
}

fn solve(value: &Vec<usize>, graph: &Vec<Vec<usize>>) -> usize {
    let mut hi = 1;
    while !reachable(hi, value, graph) {
        hi <<= 1;
    }
    let mut lo = 0;
    hi += 1;
    while lo < hi {
        let mid = (lo + hi) / 2;
        if reachable(mid, value, graph) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }
    lo
}

fn abs_diff(a: usize, b: usize) -> usize {
    if a > b {
        a - b
    } else {
        b - a
    }
}

fn reachable(max_difference: usize, value: &Vec<usize>, graph: &Vec<Vec<usize>>) -> bool {
    let mut visited = vec![false; value.len()];
    let mut q = VecDeque::new();
    q.push_back(0);
    while let Some(front) = q.pop_front() {
        if front == value.len() - 1 {
            return true;
        }
        if visited[front] {
            continue;
        }
        visited[front] = true;
        for adj in &graph[front] {
            if abs_diff(value[front], value[*adj]) <= max_difference {
                q.push_back(*adj);
            }
        }
    }
    false
}
