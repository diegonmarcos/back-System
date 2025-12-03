#!/usr/bin/env python3
"""
Claude Code Usage Report Generator

Reads ccusage data and generates reports with:
- Daily token usage (in, out, cache read)
- Costs per token type
- Percentage of Max5 plan limits (5h window * 3 = daily estimate)

Requirements:
    - ccusage (npm install -g ccusage)
"""

import json
import csv
import sys
import shutil
import subprocess
import argparse
from pathlib import Path
from datetime import datetime

# Claude Max5 plan limits per 5-hour window
# Source: https://docs.anthropic.com/en/docs/about-claude/models
MAX5_INPUT_5H = 300000      # ~300k input tokens per 5h window
MAX5_OUTPUT_5H = 100000     # ~100k output tokens per 5h window
MAX5_CACHE_5H = 1000000     # ~1M cache read per 5h window (estimate)

# Daily limits (3 windows per day as reasonable usage)
WINDOWS_PER_DAY = 3
MAX_INPUT_DAILY = MAX5_INPUT_5H * WINDOWS_PER_DAY      # 900k
MAX_OUTPUT_DAILY = MAX5_OUTPUT_5H * WINDOWS_PER_DAY    # 300k
MAX_CACHE_DAILY = MAX5_CACHE_5H * WINDOWS_PER_DAY      # 3M

# Pricing per 1M tokens (Claude Sonnet 4.5 - most common model)
# Source: https://www.anthropic.com/pricing
PRICE_INPUT = 3.00          # $3.00 per 1M input tokens
PRICE_OUTPUT = 15.00        # $15.00 per 1M output tokens
PRICE_CACHE_READ = 0.30     # $0.30 per 1M cache read tokens
PRICE_CACHE_CREATE = 3.75   # $3.75 per 1M cache creation tokens


def check_ccusage_installed() -> bool:
    """Check if ccusage is installed."""
    return shutil.which("ccusage") is not None


def get_ccusage_data() -> dict:
    """Run ccusage --json and return parsed JSON data."""
    if not check_ccusage_installed():
        print("Error: ccusage is not installed.")
        print("\nInstall it with:")
        print("  npm install -g ccusage")
        print("\nMore info: https://github.com/ryoppippi/ccusage")
        sys.exit(1)

    try:
        result = subprocess.run(
            ["ccusage", "--json"],
            capture_output=True,
            text=True,
            timeout=60
        )
        if result.returncode != 0:
            print(f"Error running ccusage: {result.stderr}")
            sys.exit(1)

        return json.loads(result.stdout)
    except subprocess.TimeoutExpired:
        print("Error: ccusage timed out")
        sys.exit(1)
    except json.JSONDecodeError as e:
        print(f"Error parsing ccusage output: {e}")
        sys.exit(1)


def calculate_cost(tokens: int, price_per_million: float) -> float:
    """Calculate cost for given tokens at price per million."""
    return (tokens / 1_000_000) * price_per_million


def format_number(n: int) -> str:
    """Format number with commas."""
    return f"{n:,}"


def get_usage_rows(data: dict) -> list:
    """Process ccusage data and return list of row dicts."""
    rows = []

    for day in data.get("daily", []):
        date = day["date"]
        tokens_in = day["inputTokens"]
        tokens_out = day["outputTokens"]
        cache_read = day["cacheReadTokens"]
        cache_create = day.get("cacheCreationTokens", 0)
        total_tokens = day["totalTokens"]

        # Calculate costs
        cost_in = calculate_cost(tokens_in, PRICE_INPUT)
        cost_out = calculate_cost(tokens_out, PRICE_OUTPUT)
        cost_cache_read = calculate_cost(cache_read, PRICE_CACHE_READ)
        cost_cache_create = calculate_cost(cache_create, PRICE_CACHE_CREATE)
        total_cost = day["totalCost"]

        # Calculate percentages of daily limits
        pct_in = (tokens_in / MAX_INPUT_DAILY) * 100
        pct_out = (tokens_out / MAX_OUTPUT_DAILY) * 100
        pct_cache = (cache_read / MAX_CACHE_DAILY) * 100

        rows.append({
            "date": date,
            "tokens_in": tokens_in,
            "tokens_out": tokens_out,
            "cache_read": cache_read,
            "cache_create": cache_create,
            "total_tokens": total_tokens,
            "cost_in": round(cost_in, 4),
            "cost_out": round(cost_out, 4),
            "cost_cache_read": round(cost_cache_read, 4),
            "cost_cache_create": round(cost_cache_create, 4),
            "total_cost": round(total_cost, 2),
            "pct_in": round(pct_in, 1),
            "pct_out": round(pct_out, 1),
            "pct_cache": round(pct_cache, 1),
        })

    # Add totals row
    if data.get("total"):
        totals = data["total"]
        rows.append({
            "date": "TOTAL",
            "tokens_in": totals["inputTokens"],
            "tokens_out": totals["outputTokens"],
            "cache_read": totals["cacheReadTokens"],
            "cache_create": totals.get("cacheCreationTokens", 0),
            "total_tokens": totals["totalTokens"],
            "cost_in": round(calculate_cost(totals["inputTokens"], PRICE_INPUT), 4),
            "cost_out": round(calculate_cost(totals["outputTokens"], PRICE_OUTPUT), 4),
            "cost_cache_read": round(calculate_cost(totals["cacheReadTokens"], PRICE_CACHE_READ), 4),
            "cost_cache_create": round(calculate_cost(totals.get("cacheCreationTokens", 0), PRICE_CACHE_CREATE), 4),
            "total_cost": round(totals["totalCost"], 2),
            "pct_in": "-",
            "pct_out": "-",
            "pct_cache": "-",
        })

    return rows


def output_table(rows: list):
    """Print table to stdout."""
    print()
    print("=" * 105)
    print(f"{'Date':<12} {'Tokens In':>12} {'Tokens Out':>12} {'Cache Read':>14} {'Cost':>10} {'%In':>7} {'%Out':>7} {'%Cache':>8}")
    print("-" * 105)

    for row in rows:
        if row["date"] == "TOTAL":
            print("-" * 105)

        pct_in = str(row['pct_in']) + "%" if row['pct_in'] != "-" else "-"
        pct_out = str(row['pct_out']) + "%" if row['pct_out'] != "-" else "-"
        pct_cache = str(row['pct_cache']) + "%" if row['pct_cache'] != "-" else "-"

        print(f"{row['date']:<12} {row['tokens_in']:>12,} {row['tokens_out']:>12,} {row['cache_read']:>14,} ${row['total_cost']:>8.2f} {pct_in:>7} {pct_out:>7} {pct_cache:>8}")

    print("=" * 105)
    print()
    print(f"Max5 Plan Daily Limits (3x 5h windows):")
    print(f"  Input:  {MAX_INPUT_DAILY:>12,} tokens/day")
    print(f"  Output: {MAX_OUTPUT_DAILY:>12,} tokens/day")
    print(f"  Cache:  {MAX_CACHE_DAILY:>12,} tokens/day")
    print()


def output_csv(rows: list, output_file: Path):
    """Write CSV file."""
    fieldnames = [
        "date", "tokens_in", "tokens_out", "cache_read", "cache_create",
        "total_tokens", "cost_in", "cost_out", "cost_cache_read",
        "cost_cache_create", "total_cost", "pct_in", "pct_out", "pct_cache"
    ]

    with open(output_file, 'w', newline='') as f:
        writer = csv.DictWriter(f, fieldnames=fieldnames)
        writer.writeheader()
        writer.writerows(rows)

    print(f"CSV report saved: {output_file}")
    total_row = rows[-1] if rows and rows[-1]["date"] == "TOTAL" else None
    if total_row:
        print(f"  Days: {len(rows) - 1}")
        print(f"  Total cost: ${total_row['total_cost']:.2f}")


def output_markdown(rows: list, output_file: Path):
    """Write Markdown file with table."""
    lines = []
    lines.append("# Claude Code Usage Report")
    lines.append("")
    lines.append(f"Generated: {datetime.now().strftime('%Y-%m-%d %H:%M:%S')}")
    lines.append("")
    lines.append("## Daily Usage")
    lines.append("")
    lines.append("| Date | Tokens In | Tokens Out | Cache Read | Cost | %In | %Out | %Cache |")
    lines.append("|------|----------:|----------:|-----------:|-----:|----:|-----:|-------:|")

    for row in rows:
        pct_in = f"{row['pct_in']}%" if row['pct_in'] != "-" else "-"
        pct_out = f"{row['pct_out']}%" if row['pct_out'] != "-" else "-"
        pct_cache = f"{row['pct_cache']}%" if row['pct_cache'] != "-" else "-"

        date_str = f"**{row['date']}**" if row['date'] == "TOTAL" else row['date']
        cost_str = f"**${row['total_cost']:.2f}**" if row['date'] == "TOTAL" else f"${row['total_cost']:.2f}"

        lines.append(f"| {date_str} | {row['tokens_in']:,} | {row['tokens_out']:,} | {row['cache_read']:,} | {cost_str} | {pct_in} | {pct_out} | {pct_cache} |")

    lines.append("")
    lines.append("## Plan Limits")
    lines.append("")
    lines.append("Max5 Plan Daily Limits (3x 5h windows):")
    lines.append("")
    lines.append(f"- **Input:** {MAX_INPUT_DAILY:,} tokens/day")
    lines.append(f"- **Output:** {MAX_OUTPUT_DAILY:,} tokens/day")
    lines.append(f"- **Cache:** {MAX_CACHE_DAILY:,} tokens/day")
    lines.append("")
    lines.append("## Pricing")
    lines.append("")
    lines.append("| Token Type | Price per 1M |")
    lines.append("|------------|-------------:|")
    lines.append(f"| Input | ${PRICE_INPUT:.2f} |")
    lines.append(f"| Output | ${PRICE_OUTPUT:.2f} |")
    lines.append(f"| Cache Read | ${PRICE_CACHE_READ:.2f} |")
    lines.append(f"| Cache Create | ${PRICE_CACHE_CREATE:.2f} |")
    lines.append("")

    with open(output_file, 'w') as f:
        f.write("\n".join(lines))

    print(f"Markdown report saved: {output_file}")
    total_row = rows[-1] if rows and rows[-1]["date"] == "TOTAL" else None
    if total_row:
        print(f"  Days: {len(rows) - 1}")
        print(f"  Total cost: ${total_row['total_cost']:.2f}")


def show_help():
    """Show help message."""
    help_text = """
╔═══════════════════════════════════════════════════════════════════════════════╗
║                      Claude Code Usage Report Generator                        ║
╠═══════════════════════════════════════════════════════════════════════════════╣
║                                                                               ║
║  USAGE:                                                                       ║
║    python ccusage_report.py [OPTIONS]                                         ║
║                                                                               ║
║  OPTIONS:                                                                     ║
║    --cat              Display usage table in terminal                         ║
║    --csv [FILE]       Export to CSV file (default: ccusage_report.csv)        ║
║    --md  [FILE]       Export to Markdown file (default: ccusage_report.md)    ║
║    -h, --help         Show this help message                                  ║
║                                                                               ║
║  EXAMPLES:                                                                    ║
║    python ccusage_report.py --cat                                             ║
║    python ccusage_report.py --csv                                             ║
║    python ccusage_report.py --csv my_report.csv                               ║
║    python ccusage_report.py --md                                              ║
║    python ccusage_report.py --md my_report.md                                 ║
║    python ccusage_report.py --cat --csv --md    (all outputs)                 ║
║                                                                               ║
║  REQUIREMENTS:                                                                ║
║    ccusage - Install with: npm install -g ccusage                             ║
║    More info: https://github.com/ryoppippi/ccusage                            ║
║                                                                               ║
║  DATA SOURCE:                                                                 ║
║    Reads from ~/.claude/projects/ local JSONL files                           ║
║                                                                               ║
╚═══════════════════════════════════════════════════════════════════════════════╝
"""
    print(help_text)


def main():
    script_dir = Path(__file__).parent

    # Custom argument parsing to handle optional file arguments
    args = sys.argv[1:]

    # Check for help
    if not args or "-h" in args or "--help" in args:
        show_help()
        sys.exit(0)

    do_cat = False
    do_csv = False
    do_md = False
    csv_file = script_dir / "ccusage_report.csv"
    md_file = script_dir / "ccusage_report.md"

    i = 0
    while i < len(args):
        arg = args[i]
        if arg == "--cat":
            do_cat = True
        elif arg == "--csv":
            do_csv = True
            # Check if next arg is a filename (not another flag)
            if i + 1 < len(args) and not args[i + 1].startswith("-"):
                csv_file = Path(args[i + 1])
                i += 1
        elif arg == "--md":
            do_md = True
            # Check if next arg is a filename (not another flag)
            if i + 1 < len(args) and not args[i + 1].startswith("-"):
                md_file = Path(args[i + 1])
                i += 1
        else:
            print(f"Unknown option: {arg}")
            print("Use --help for usage information")
            sys.exit(1)
        i += 1

    # Fetch data
    print("Fetching usage data from ccusage...")
    data = get_ccusage_data()
    rows = get_usage_rows(data)

    if not rows:
        print("No usage data found.")
        sys.exit(1)

    # Output based on flags
    if do_cat:
        output_table(rows)

    if do_csv:
        output_csv(rows, csv_file)

    if do_md:
        output_markdown(rows, md_file)

    if not (do_cat or do_csv or do_md):
        show_help()


if __name__ == "__main__":
    main()
