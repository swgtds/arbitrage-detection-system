from typing import List
from math import log
import yfinance as yf

def get_exchange_rates(currencies: List[str]) -> List[List[float]]:
    #Fetches real-time exchange rates using Yahoo Finance (yfinance) and prints them.
    n = len(currencies)
    rates = [[1.0] * n for _ in range(n)]

    print("\n🔹 Fetching exchange rates...\n")

    for i in range(n):
        for j in range(n):
            if i != j:
                pair = f"{currencies[i]}{currencies[j]}=X"
                try:
                    data = yf.Ticker(pair).history(period="1d")
                    if not data.empty:
                        rate = float(data['Close'].iloc[-1])
                        rates[i][j] = rate
                        print(f"{currencies[i]}/{currencies[j]}: {rate:.6f}")
                    else:
                        print(f"Warning: No data for {currencies[i]}/{currencies[j]}. Using 1.0 as fallback.")
                        rates[i][j] = 1.0
                except Exception as e:
                    print(f"Error fetching {currencies[i]}/{currencies[j]}: {e}")
                    rates[i][j] = 1.0

    return rates


def negate_logarithm_convertor(graph: List[List[float]]) -> List[List[float]]:
    #Log of each rate in graph and negate it.
    return [[-log(edge) for edge in row] for row in graph]


def arbitrage(currencies: List[str], rates: List[List[float]]):
    #Calculates arbitrage situations and prints the details.
    trans_graph = negate_logarithm_convertor(rates)

    n = len(trans_graph)
    min_dist = [float('inf')] * n
    pre = [-1] * n

    source = 0
    min_dist[source] = source

    # Relax edges (n-1) times
    for _ in range(n - 1):
        for source_curr in range(n):
            for dest_curr in range(n):
                if min_dist[dest_curr] > min_dist[source_curr] + trans_graph[source_curr][dest_curr]:
                    min_dist[dest_curr] = min_dist[source_curr] + trans_graph[source_curr][dest_curr]
                    pre[dest_curr] = source_curr

    # Check for negative cycle (arbitrage opportunity)
    arbitrage_found = False
    for source_curr in range(n):
        for dest_curr in range(n):
            if min_dist[dest_curr] > min_dist[source_curr] + trans_graph[source_curr][dest_curr]:
                # Arbitrage cycle detected
                print_cycle = [dest_curr]

                while True:
                    source_curr = pre[source_curr]
                    if source_curr in print_cycle:
                        break
                    print_cycle.append(source_curr)

                print_cycle.append(dest_curr)

                print("\n Arbitrage Opportunity Detected:")
                print(" ->  ".join([currencies[p] for p in print_cycle[::-1]]))
                arbitrage_found = True

    if not arbitrage_found:
        print("\n No arbitrage opportunity found.")


if __name__ == "__main__":
    currencies = input("Enter currency codes separated by space (e.g., USD EUR INR): ").upper().split()

    if len(currencies) < 2:
        print("Please enter at least two currencies.")
    else:
        rates = get_exchange_rates(currencies)
        arbitrage(currencies, rates)
