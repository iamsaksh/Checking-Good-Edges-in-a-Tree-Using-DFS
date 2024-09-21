#include <stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void dfs(int node, bool *visited, int *P, int N) {
    visited[node] = true;
    for (int i = 0; i < N; i++) {
        if (P[i] == node && !visited[i]) {
            dfs(i, visited, P, N);
        }
    }
}

bool isGoodEdge(int *A, int *P, int N, int u, int v) {
    bool visited[N];
    int subtreeU[N];
    int subtreeV[N];
    int countU = 0, countV = 0;

    // First DFS to find nodes in the subtree of 'u' after removing edge u-v
    for (int i = 0; i < N; i++) visited[i] = false;
    dfs(u, visited, P, N);
    for (int i = 0; i < N; i++) if (visited[i]) subtreeU[countU++] = A[i];

    // Second DFS to find nodes in the subtree of 'v' after removing edge u-v
    for (int i = 0; i < N; i++) visited[i] = false;
    dfs(v, visited, P, N);
    for (int i = 0; i < N; i++) if (visited[i]) subtreeV[countV++] = A[i];

    // Check for duplicates between subtreeU and subtreeV
    for (int i = 0; i < countU; i++) {
        for (int j = 0; j < countV; j++) {
            if (subtreeU[i] == subtreeV[j]) return false;
        }
    }
    return true;
}

int main() {
    int N;
    
    // User input for number of nodes
    printf("Enter number of nodes: ");
    scanf("%d", &N);
    
    int A[N], P[N];
    
    // User input for node values
    printf("Enter values of nodes: ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &A[i]);
    }
    
    // User input for parent array
    printf("Enter parent array (use -1 for root): ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &P[i]);
    }

    // Count the number of good edges
    int goodEdgeCount = 0;

    // Checking each edge
    for (int i = 1; i < N; i++) {
        int u = P[i];
        int v = i;

        if (isGoodEdge(A, P, N, u, v)) {
            printf("Edge (%d-%d) is a good edge.\n", u, v);
            goodEdgeCount++;
        } else {
            printf("Edge (%d-%d) is not a good edge.\n", u, v);
        }
    }

    printf("Number of good edges: %d\n", goodEdgeCount);

    return 0;
}

