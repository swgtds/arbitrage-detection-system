#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <unistd.h>

#define C 6

const double rates[C][C] = {
    {1, 0.23, 0.25, 16.43, 18.21, 4.94},
    {4.34, 1, 1.11, 71.40, 79.09, 21.44},
    {3.93, 0.90, 1, 64.52, 71.48, 19.37},
    {0.061, 0.014, 0.015, 1, 1.11, 0.30},
    {0.055, 0.013, 0.014, 0.90, 1, 0.27},
    {0.20, 0.047, 0.052, 3.33, 3.69, 1}
};


const char* currencies[C] = {"PLN", "EUR", "USD", "RUB", "INR", "MXN"};


void graph_logarithmic_convertion(const double graph[C][C], double result[C][C]) {
    for (int i = 0; i < C; i++) {
        for (int j = 0; j < C; j++) {
            result[i][j] = -(log(graph[i][j]));
        }
    }
}

void print_arbitrage_opportunity(int* print_cycle, int cycle_length) {
    printf("Arbitrage Detected! \n");
    for (int i = cycle_length - 1; i >= 0; i--) {
        printf("%s", currencies[print_cycle[i]]);
        if (i > 0) {
            printf(" --> ");
        }
    }
    printf("\n");
    printf("\n");
    printf("\n");
}
void arbitrage() {
    double modified_graph[C][C];
    graph_logarithmic_convertion(rates, modified_graph);

    int source = 0;
    double min_dist[C];
    int pre[C];

    for (int i = 0; i < C; i++) {
        min_dist[i] = INFINITY;
        pre[i] = -1;
    }
    min_dist[source] = source;

    for (int k = 0; k < C - 1; k++) {
        for (int i = 0; i < C; i++) {
            for (int j = 0; j < C; j++) {
                if (min_dist[j] > min_dist[i] + modified_graph[i][j]) {
                    min_dist[j] = min_dist[i] + modified_graph[i][j];
                    pre[j] = i;
                }
            }
        }
    }

    for (int i = 0; i < C; i++) {
        for (int j = 0; j < C; j++) {
            if (min_dist[j] > min_dist[i] + modified_graph[i][j]) {
                int print_cycle[C];
                int cycle_length = 0;
                print_cycle[cycle_length++] = j;
                print_cycle[cycle_length++] = i;

                int current = i;
               while (pre[i]!=print_cycle[j]) {
                    current = pre[current];
                    for (int k = 0; k < cycle_length; k++) {
                        if (print_cycle[k] == current) {
                            print_cycle[cycle_length++] = current;
                            print_arbitrage_opportunity(print_cycle, cycle_length);
                            return;
                        }
                  }
                    print_cycle[cycle_length++] = current;
               }
            }
        }
    }
}

int main() {
    char str[50];
    printf("Here are the list of Currencies:\n");
    printf("PLN: Polish Zloty\nEUR: Euro\nUSD: United States Dollar\nRUB: Russian Ruble\nMXN: Mexican Peso\n");
    sleep(3);
    printf("\nPress any key to continue:");
    scanf("%s", &str);
    printf("\n");
    printf("\n");
    arbitrage();
    return 0;
}
