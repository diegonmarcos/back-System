That is easily accomplished using the Gemini CLI's built-in model selection flag, `--model` or its short alias, `-m`.

To run the Gemini CLI with each of the three models you mentioned (`gemini-2.5-pro`, `gemini-2.5-flash`, and `gemini-2.5-flash-lite`), you simply call the `gemini` command and specify the model ID.

Here are the three separate commands:

-----

## 💻 CLI Commands for Gemini Model Selection

### 1\. Gemini 2.5 Pro (For Complex Reasoning & Coding)

This command selects the most capable model, ideal for deep analysis, intricate coding, and demanding reasoning tasks.

```bash
gemini --model gemini-2.5-pro
```

### 2\. Gemini 2.5 Flash (For Speed, Balance, and Everyday Tasks)

This command selects the model that offers the best balance of speed and capability at a highly cost-effective rate.

```bash
gemini --model gemini-2.5-flash
```

### 3\. Gemini 2.5 Flash-Lite (For Highest Throughput and Lowest Cost)

This command selects the most efficient model, perfect for high-volume, low-latency tasks like summarization or classification.

```bash
gemini --model gemini-2.5-flash-lite
```

### Note on Authentication

Before running any of these commands, ensure you have set up your API key as an environment variable (as discussed previously), which the Gemini CLI will automatically pick up:

```bash
export GEMINI_API_KEY="[YOUR_KEY_STRING]"
```