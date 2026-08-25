import numpy as np
import pandas as pd

rng = np.random.default_rng(42)

def generate_synthetic_data(num_rows: int, output_path: str) -> None:
    mock_tickers = [chr(65 + i) for i in range(26)]

    df = pd.DataFrame({
        'timestamp': [1_000_000_000 + i for i in range(num_rows)],
        'symbol': rng.choice(a=mock_tickers, size=num_rows),
        'side': rng.choice(a=['BUY', 'SELL'], size=num_rows),
        'price': rng.normal(loc=100, scale=10, size=num_rows).clip(min=0),
        'quantity': rng.integers(low=50, high=1000, size=num_rows)
    })

    df.to_csv(output_path, index=False)

if __name__ == '__main__':
    generate_synthetic_data(1_000, '../data/sample.csv')
    # generate_synthetic_data(1_000_000, '../data/large.csv')