#include <stack>
#include <cstdlib>

long long percorri(int N, long long L, long long D[], long long P[]) {

    // stack_next is a stack containing the couples (P+D, P-D)
    std::stack<std::pair<long long, long long>> stack_next;
    
    // Dummy beach at the end of the waterfront (D = L, P = 0)
    stack_next.push(std::make_pair(L, -L));
    
    for (int u = N-1; u >= 0; u--) {
        while (true) {
            if (P[u] - D[u] <= stack_next.top().second)
                stack_next.pop();
            else {
                if (P[u] + D[u] < stack_next.top().first)
                    stack_next.push(std::make_pair(P[u] + D[u], P[u] - D[u]));
                break;
            }
        }
    }
    
    // Dummy beach at the beginning of the waterfront (D = 0, P = 0)
    while (stack_next.top().second >= 0) stack_next.pop();
    stack_next.push(std::make_pair(0,0));
    
    long long res = 0;
    std::pair <long long, long long> prec = stack_next.top();
    std::pair <long long, long long> at;
    stack_next.pop();
    
    while (!stack_next.empty()) {
        at = stack_next.top();
        stack_next.pop();
        // at.first + prec.second is the distance between the current and
        // the previous beach: (P[u_{i-1}]-D[u_{i-1}]) + (P[u_i]+D[u_i])
        res = std::max(res, at.first + prec.second);
        prec = at;
    }
    
    return res;
}