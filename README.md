# DEEPCRAFT™ Studio Accelerators

## 📖 Overview

This repository contains **DEEPCRAFT™ Studio Accelerators** — deep learning based projects for various use-cases designed as starting points for building custom applications. These projects contain data and a project file that is ready to be used with [DEEPCRAFT™ Studio](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio) for simplified Edge AI model development.

This repository is automatically pulled and content is generated in DEEPCRAFT™ Studio. For the best experience, access these models through DEEPCRAFT™ Studio.

For commercial use, our standard terms and conditions apply: https://developer.imagimob.com/legal/studio-terms-and-conditions.

## 🚀 Usage

These projects are designed to be used through [DEEPCRAFT™ Studio](https://www.imagimob.com/studio) and should be accessed through that platform. See also Studio's [online documentation](https://developer.imagimob.com/) for more details.

When bringing your project into DEEPCRAFT™ Studio, consider the following:

1. **Supported algorithms** — Classification, Regression, and Object Detection
2. **Data and labels** — ensure they match the format Studio supports:
   - Classification and Regression — [more info](https://developer.imagimob.com/deepcraft-studio/data-preparation/data-collection/bring-your-data/bring-your-own-data)
   - Object Detection — [more info](https://developer.imagimob.com/deepcraft-studio/data-preparation/data-collection/bring-your-data/bring-your-own-data-object-detection)
3. **Data preprocessing** — configure preprocessing in Studio:
   - Use available Studio layers — [more info](https://developer.imagimob.com/deepcraft-studio/preprocessing)
   - Add your custom preprocessing layers — [more info](https://developer.imagimob.com/deepcraft-studio/deployment/custom-layers-functions)
4. **Neural networks, layers, and functions** — use only supported building blocks:
   - Classification and Regression — [more info](https://developer.imagimob.com/deepcraft-studio/deployment/supported-layers)
   - Object Detection — [more info](https://developer.imagimob.com/deepcraft-studio/model-training/training-object-detection)

## 🤝 Contribution

All users are welcome to submit new models/projects, subject to the Infineon DEEPCRAFT™ Studio Accelerators review process.

### How it works

1. 📁 **Prepare your project** — build your DEEPCRAFT™ Studio Accelerator locally. We recommend starting from [`_PROJECT_TEMPLATE`](_PROJECT_TEMPLATE), but you can also bring your own project. Complete your project files, `README.md`, and `metadata.json`. See [Step 1](#step-1--prepare-your-project) and [Step 2](#step-2--prepare-metadatajson) below for details.

---

2. 📤 **Submit your project** — use the [PR tool](https://github.com/Infineon/deepcraft-studio-accelerators-pr-tool) to open a pull request against this repository. The tool validates your project layout and metadata, pushes your files to your fork, and opens the PR in your browser. See [Step 3](#step-3--get-the-pr-tool) and [Step 4](#step-4--run-the-pr-tool-and-submit) below.

---

3. 🔍 **Review** — the Infineon team reviews your pull request. Automated pipelines may run to generate pre-processing, model predictions, and training outputs. Reviewers may request changes — address feedback by updating your project locally and re-running the PR tool to update the same pull request.

---

4. 🌐 **Publication** — once approved, your pull request is merged into `main`. The project is then published and becomes available through DEEPCRAFT™ Studio and the [DEEPCRAFT™ AI Hub](https://deepcraft.infineon.com).

### Submission requirements

Before opening a pull request, make sure you have the following tools and software:

- **[DEEPCRAFT™ Studio](https://softwaretools.infineon.com/assets/com.ifx.tb.tool.deepcraftstudio)** — to build and export your Accelerator project (`.improj` file and local `Data/` folder)
- **[GitHub account](https://github.com/join)** — required to fork this repository and manage your pull request
- **[PR tool](https://github.com/Infineon/deepcraft-studio-accelerators-pr-tool)** — the latest version from [deepcraft-studio-accelerators-pr-tool](https://github.com/Infineon/deepcraft-studio-accelerators-pr-tool); validates your project, pushes files, and opens the pull request
- **Python 3.10+** — to run the PR tool (no extra packages required)
- **Git** — version 2.43 or newer (the PR tool uses it to manage your submission)
- **GitHub CLI (`gh`)** *(optional)* — for authentication; bundled with the PR tool on Windows. Install from [cli.github.com](https://cli.github.com/) only if you need it on other platforms or prefer a system-wide copy

## 📝 Submission Process

Follow the steps below to prepare and submit your project. For a high-level overview, see [How it works](#how-it-works) in the Contribution section.

### 📁 Step 1 — Prepare your project

You can bring your own DEEPCRAFT™ Studio project, but we **recommend using [`_PROJECT_TEMPLATE`](_PROJECT_TEMPLATE)** as a starting point — it provides the expected folder layout and files for submission.

If you use the template:

1. **Rename** your Accelerator project folder. The name can describe the use case and sensor used. Check existing project names and pick one that is not already in use.
2. **Add content** to the relevant folders and delete those that do not apply. The `Data/` folder is mandatory and will not appear in this repository. Add custom folder(s) if needed.
3. **Set up** the provided project file example or replace it with your own `.improj` file.
4. **Write** the project `README.md`, including:
   - Use-case description
   - Sensor settings, specifications, and data description
   - Guidelines for collecting and expanding the dataset
   - Recommended path to production, including steps to make the model production-ready, with focus on reducing False Positives and/or False Negatives
5. **Clean up** — remove all `README.md` files from subfolders of `_PROJECT_TEMPLATE` if you used the template.

If you bring your own project instead, make sure it includes the required files (`README.md`, `metadata.json`, `.improj`, `Data/`) and follows the expected layout. Use [`_PROJECT_TEMPLATE`](_PROJECT_TEMPLATE) as a reference.

---

### 📋 Step 2 — Prepare `metadata.json`

Choose one of the following options:

1. **Guided (recommended)** — when you run the PR tool (Step 4), it walks you through metadata collection interactively and writes `metadata.json` for you.
2. **Manual** — fill in `metadata.json` yourself using [`_PROJECT_TEMPLATE/metadata.json`](_PROJECT_TEMPLATE/metadata.json) as a reference for the required fields and structure. The PR tool will validate your file when you run it.

---

### 🛠️ Step 3 — Get the PR tool

Get the pull request automation tool (PR tool) from the [deepcraft-studio-accelerators-pr-tool](https://github.com/Infineon/deepcraft-studio-accelerators-pr-tool) repository.

**Before submitting any project, make sure you are using the latest version of the PR tool** — if you already have a copy, update it first (for example, run `git pull` in an existing clone, or download/clone the repository again).

You can obtain the tool in one of the following ways:

**Option A — Download as ZIP**

1. Open [deepcraft-studio-accelerators-pr-tool](https://github.com/Infineon/deepcraft-studio-accelerators-pr-tool) on GitHub.
2. Click **Code → Download ZIP**, extract the archive, and use the `pr_tool` folder inside.

**Option B — Clone the repository**

```bash
git clone https://github.com/Infineon/deepcraft-studio-accelerators-pr-tool.git
cd deepcraft-studio-accelerators-pr-tool\pr_tool
```

**Option C — Clone only the `pr_tool` folder (sparse checkout)**

```bash
git clone --filter=blob:none --sparse https://github.com/Infineon/deepcraft-studio-accelerators-pr-tool.git
cd deepcraft-studio-accelerators-pr-tool
git sparse-checkout set pr_tool
cd pr_tool
```

---

### 🚀 Step 4 — Run the PR tool and submit

From the `pr_tool` folder, run:

```bash
python .\pr_tool.py --repo accelerators --path <project-path>
```

Replace `<project-path>` with the root path of your Studio Accelerator project. For more information, review the tool's [README.md](https://github.com/Infineon/deepcraft-studio-accelerators-pr-tool/blob/main/pr_tool/README.md).

What happens next:

1. You will be prompted to authenticate with your **GitHub account** (required).
2. The tool forks this repository and prepares the pull request.
3. Your browser opens the pull request page — add the relevant details to aid the review process, then submit.

**Updating an existing pull request** — every time you change your project, re-run the same command above. Your existing pull request will be updated automatically.

> **Note:** The pipeline will automatically generate pre-processing, model predictions, and train some models based on the default best model selection from DEEPCRAFT™ Studio. If you would not like this, specify in the pull request that it should not be published.
