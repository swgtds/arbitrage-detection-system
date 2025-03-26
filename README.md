# 💱 Currency Arbitrage Detection

This Project detects **Arbitrage opportunities** in currency exchange rates using **Yahoo Finance (yfinance)**. It fetches real-time exchange rates, constructs a graph, and applies the **Bellman-Ford algorithm** to detect negative cycles, indicating potential arbitrage opportunities.

---

## Features

- ✅ **Real-time Exchange Rates:** Fetches current exchange rates using Yahoo Finance API.
- 🔁 **Graph-based Algorithm:** Constructs a currency graph and uses the Bellman-Ford algorithm to detect arbitrage cycles.
- 🔥 **Optimized Calculation:** Converts rates to their **negative logarithmic values** for accurate cycle detection.
- 📊 **User-Friendly Output:** Displays detected arbitrage cycles or confirms no arbitrage opportunity.

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/swgtds/arbitrage-detection-system
   cd arbitrage-detection-system

2. Create a virtual environment (optional but recommended):
    ```bash
    python3 -m venv venv
    source venv/bin/activate   # Linux/macOS
    venv\Scripts\activate      # Windows

3. Install yfinance:
    ```bash
    pip install yfinance

## Usage

1. Run the script:
    ```bash
    python arbitrage.py

2. Enter currency codes separated by spaces (e.g., USD EUR INR).

3. The program fetches exchange rates, constructs the graph, and detects arbitrage opportunities.

## How It Works

1. **Fetching Exchange Rates:**
   - Uses the `yfinance` library to fetch exchange rates for currency pairs.
   - Builds a matrix of exchange rates.

2. **Graph Construction:**
   - Converts exchange rates to their **negative logarithmic values**.
   - This makes the arbitrage detection equivalent to finding a **negative-weight cycle**.

3. **Arbitrage Detection:**
   - Applies the **Bellman-Ford algorithm** to detect negative cycles.
   - Prints the arbitrage cycle if found or indicates no arbitrage opportunity.

---

## Dependencies

- Python 3.x
- `yfinance`
- `math` and `typing` (standard Python libraries)

## License

This project is licensed under the [MIT License](LICENSE).

## 🤝 Contributing

Contributions are welcome! If you find issues or have suggestions, feel free to open an issue or submit a pull request.
