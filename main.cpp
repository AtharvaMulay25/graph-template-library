// =========================================== PROBLEM STATEMENT =============================================================

/*
Given a snake and ladder board, this program finds the minimum number of dice throws required to reach the destination or last cell (n in this program) from the source or 1st cell. Basically, the player has total control over the outcome of the dice throw and wants to find out the minimum number of throws required to reach the last cell.
If the player reaches a cell which is the base of a ladder, the player has to climb up that ladder and if reaches a cell is the mouth of the snake, and has to go down to the tail of the snake without a dice throw.
Condition in the Problem: Note that you only take a snake or ladder at most once per move. If the destination to a snake or ladder is the start of another snake or ladder, you do not follow the subsequent snake or ladder.
This problem is solved using the BFS algorithm(considering the board as a digraph)implemented by using the library "graph.h"
*/

// ================================================ SOLUTION ==================================================================

#include <iostream>
#include <queue>

#include "graph.h"

using namespace std;
int getMinDiceThrows(digraph<int> &, int);

int main() {
    // Making graph of snake & ladders board of n size
    int n = 30;                    // size of the snake & ladders board
    vector<int> moves(n + 1, -1);  // moves stores the entry moves where moves[i] = -1 if there is no snake and no ladder from i, otherwise move[i] contains index of destination cell for the snake or the ladder at i.

    // Ladders on the board
    moves[3] = 21;
    moves[5] = 7;
    moves[11] = 25;
    moves[20] = 28;

    // Snakes on the board
    moves[27] = 0;
    moves[21] = 8;
    moves[17] = 3;
    moves[19] = 6;

    // Constructing the board as a directed graph by creating adjacency list
    digraph<int> board;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= (i + 6) && j <= n; j++) {
            if (moves[j] == -1) {  // if cell j don't have ladder or snake, then just form a edge between cell i and cell j.
                board.add_edge(i, j);
            } else {  // otherwise form a edge from cell i to the destination cell of cell j.
                board.add_edge(i, moves[j]);
            }
        }
    }

    int minimum_moves = getMinDiceThrows(board, n);  // getMinDiceThrows returns the minimum moves to be made to readh the destination.
    cout << "Minimum moves to reach to destination point: " << minimum_moves << "\n";
    return 0;
}

int getMinDiceThrows(digraph<int> &board, int n) {
    vector<bool> visited(n + 1, false);  // stores all the vertices and marks visited vertices as true.

    queue<pair<int, int>> distFromSource;  // distFromSource is the exploration queue used in BFS which stores vertex and its distance from source.

    visited[1] = true;            // marking source vertex as visited.
    distFromSource.push({1, 0});  // then pushing it in the exploration queue.

    int vertex, dist;  // vertex, dist stores the vertex no. and its distance from source of the head of the queue.

    // Implementing BFS algorithm starting at source vertex 1
    while (!distFromSource.empty()) {
        vertex = distFromSource.front().first;
        dist = distFromSource.front().second;
        distFromSource.pop();

        if (vertex == n) {  // If front vertex is the destination vertex, we are done.
            break;
        } else {
            for (auto it : board.adj[vertex]) {  // otherwise we traverse the adjacency list of vertex, and enqueue the non-visited neighbours in the exploration queue.
                if (!visited[it]) {
                    visited[it] = true;
                    int distance = dist + 1;
                    distFromSource.push({it, distance});
                }
            }
        }
    }
    return dist;  // it will return the distance of destination vertex i.e. n from the source vertex 1 which is the minimum no. of moves to win the game.
}

// ============================================ SOLUTION ENDS ===================================================================