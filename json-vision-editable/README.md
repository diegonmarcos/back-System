# JSON Vision 🎯

<div align="center">

![JSON Vision Banner](https://img.shields.io/badge/JSON-Vision-blue?style=for-the-badge&logo=json&logoColor=white)

**A powerful, interactive JSON visualization tool with multiple view modes, real-time validation, and advanced querying capabilities.**

[![Next.js](https://img.shields.io/badge/Next.js-14-black?style=flat-square&logo=next.js)](https://nextjs.org/)
[![TypeScript](https://img.shields.io/badge/TypeScript-5.5-blue?style=flat-square&logo=typescript)](https://www.typescriptlang.org/)
[![Tailwind CSS](https://img.shields.io/badge/Tailwind-3.4-38bdf8?style=flat-square&logo=tailwind-css)](https://tailwindcss.com/)
[![License](https://img.shields.io/badge/License-MIT-green?style=flat-square)](LICENSE)

[Live Demo](https://jsonvision.dev) • [Report Bug](https://github.com/yourusername/json-vision/issues) • [Request Feature](https://github.com/yourusername/json-vision/issues)

</div>

---

## 📸 Screenshots

### Graph View with Interactive Nodes
> Visualize complex JSON structures with draggable, interconnected nodes

### Tree View with Syntax Highlighting
> Browse through nested JSON data with collapsible tree structure

### JSONPath Query Interface
> Query specific data points using JSONPath expressions

---

## ✨ Features

### 🎨 **Multiple Visualization Modes**
- **📝 Raw Editor**: Edit JSON directly with real-time validation
- **📊 Split View**: See editor and visualization side-by-side
- **🌳 Tree View**: Interactive collapsible JSON tree with syntax highlighting
- **🔄 Graph View**: Visual node-based diagram with drag-and-drop functionality

### 🔥 **Advanced Capabilities**
- **📁 File Operations**: Drag & drop JSON files or browse from your system
- **🎯 JSONPath Queries**: Query data using JSONPath expressions (e.g., `$.users[0].name`)
- **✂️ Path Extraction**: Click any node to instantly copy its JSON path
- **🔍 Real-time Search**: Filter and find nodes as you type
- **💾 Export Options**: Download formatted or minified JSON

### ⚡ **Developer Experience**
- **🚀 Lightning Fast**: Built with Next.js 14 and React 18
- **🎨 Beautiful UI**: Modern dark theme with smooth animations
- **📱 Fully Responsive**: Works perfectly on desktop, tablet, and mobile
- **♿ Accessible**: WCAG compliant with keyboard navigation
- **🔒 Privacy First**: All processing happens locally in your browser

## 🚀 Quick Start

### Prerequisites

- **Node.js** 18.x or higher
- **npm** 9.x or higher (or yarn/pnpm)
- Modern web browser (Chrome, Firefox, Safari, Edge)

### Installation

#### Option 1: Clone from GitHub (Recommended)

```bash
# Clone the repository
git clone https://github.com/yourusername/json-vision.git

# Navigate to the project directory
cd json-vision

# Install dependencies
npm install

# Start development server
npm run dev

# Open http://localhost:3000 in your browser
```

#### Option 2: Local Setup

```bash
# Navigate to the project directory
cd "c:\Users\hardi\OneDrive\Desktop\JSON Visualizer"

# Install dependencies
npm install

# Run the development server
npm run dev
```

### 🌐 Access the Application

Once the server is running, open your browser and navigate to:
- **Local**: [http://localhost:3000](http://localhost:3000)
- **Network**: Your local IP address (shown in terminal)

---

## 📖 User Guide

### Getting Started

1. **Paste or Upload JSON**
   - Paste JSON directly into the editor, OR
   - Drag & drop a `.json` file onto the editor, OR
   - Click "Browse" to select a file from your system

2. **Choose Your View Mode**
   - **Raw**: Edit JSON text directly
   - **Split**: See editor and visualization together
   - **Tree**: Explore nested structure
   - **Graph**: Visualize relationships

3. **Explore Your Data**
   - Click nodes to expand/collapse
   - Hover for copy-path tooltips
   - Use search to filter nodes
   - Query with JSONPath

### 🎯 JSONPath Queries

Query specific data from your JSON using JSONPath syntax:

```bash
# Get root project name
$.project

# Access nested values
$.stats.visitors

# Array indexing
$.team.leads[0]

# Nested array access
$.features[2].details.complexity
```

**Supported Syntax:**
- `$.key` - Root level key
- `$.key.subkey` - Nested access
- `$[0]` - Array index
- `$.array[0].key` - Array with nested keys

### 🛠️ Editor Tools

| Action | Shortcut | Description |
|--------|----------|-------------|
| Format | Click ▶️ | Beautify JSON with indentation |
| Minify | Click ⊟ | Compress to single line |
| Copy | Click 📋 | Copy raw JSON to clipboard |
| Clear | Click 🗑️ | Reset the editor |
| Export | Click 💾 | Download as `.json` file |

## 🏗️ Project Structure

```
json-vision/
├── app/
│   ├── globals.css              # Global styles, Tailwind directives, animations
│   ├── layout.tsx               # Root layout with metadata and font config
│   ├── page.tsx                 # Main application component (1000+ lines)
│   └── favicon.ico              # App icon
├── public/                      # Static assets (images, fonts, etc.)
├── node_modules/                # Dependencies (auto-generated)
├── .next/                       # Next.js build output (auto-generated)
├── .eslintrc.json              # ESLint rules and configuration
├── .gitignore                  # Git ignore patterns
├── next.config.js              # Next.js configuration
├── package.json                # Project dependencies and scripts
├── postcss.config.js           # PostCSS plugins (Tailwind, Autoprefixer)
├── tailwind.config.js          # Tailwind theme and customization
├── tsconfig.json               # TypeScript compiler options
└── README.md                   # This file
```

### Key Files Explained

- **`app/page.tsx`**: Core application logic including:
  - JSON parsing and validation
  - Graph layout algorithm
  - Tree rendering components
  - Drag & drop functionality
  - JSONPath query evaluation
  - State management

- **`app/globals.css`**: Custom styles, animations, and scrollbar theming

- **`tailwind.config.js`**: Custom animations and theme extensions

---

## 🛠️ Tech Stack

### Frontend Framework
- **[Next.js 14](https://nextjs.org/)** - React framework with App Router
- **[React 18](https://react.dev/)** - UI library with hooks
- **[TypeScript 5.5](https://www.typescriptlang.org/)** - Type-safe JavaScript

### Styling & UI
- **[Tailwind CSS 3.4](https://tailwindcss.com/)** - Utility-first CSS framework
- **[Lucide React](https://lucide.dev/)** - Beautiful icon library
- **PostCSS** - CSS processing with Autoprefixer

### Development Tools
- **ESLint** - Code linting and quality
- **TypeScript** - Static type checking
- **Next.js Fast Refresh** - Instant feedback during development

---

## 📜 Available Scripts

```bash
# Development
npm run dev          # Start development server on localhost:3000
npm run dev -- -p 3001   # Start on custom port

# Production
npm run build        # Create optimized production build
npm start            # Start production server
npm run lint         # Run ESLint to check code quality

# Maintenance
npm install          # Install/update dependencies
npm audit            # Check for vulnerabilities
npm audit fix        # Fix vulnerabilities automatically
```

### Build Output

Production build creates:
- Optimized JavaScript bundles
- Static HTML pages
- CSS files with purged unused styles
- Compressed assets with gzip/brotli

---

## 🎨 Customization Guide

### Change Theme Colors

Edit `tailwind.config.js`:

```js
module.exports = {
  theme: {
    extend: {
      colors: {
        // Add your custom colors
        primary: '#your-color',
        secondary: '#your-color',
      }
    }
  }
}
```

### Modify Default JSON

Edit `app/page.tsx` (line ~400):

```typescript
const defaultJson = {
  // Your custom default JSON structure
  "yourKey": "yourValue"
};
```

### Adjust Layout Spacing

In `app/page.tsx`, modify graph layout constants:

```typescript
// Horizontal spacing between depth levels
x: depth * 500 + 80

// Vertical spacing between nodes
y: startY * 120 + 80
```

### Custom Animations

Add to `tailwind.config.js`:

```js
animation: {
  'your-animation': 'your-keyframes 1s ease-in-out',
},
keyframes: {
  'your-keyframes': {
    '0%': { /* start state */ },
    '100%': { /* end state */ }
  }
}
```

---

## 🐛 Troubleshooting

### Common Issues

#### Port Already in Use
```bash
# Solution 1: Use different port
npm run dev -- -p 3001

# Solution 2: Kill process on port 3000
# Windows
netstat -ano | findstr :3000
taskkill /PID <PID> /F

# Mac/Linux
lsof -ti:3000 | xargs kill -9
```

#### Build Errors
```bash
# Clear cache and rebuild
rm -rf node_modules .next
npm install
npm run build
```

#### TypeScript Errors
```bash
# Regenerate types
npm run build

# Check for errors
npx tsc --noEmit
```

#### Styling Not Applied
```bash
# Ensure Tailwind is running
# Check tailwind.config.js paths are correct
# Restart dev server
```

### Performance Issues

**Large JSON Files (>1MB):**
- Use minified view initially
- Close unused browser tabs
- Increase Node.js memory:
  ```bash
  NODE_OPTIONS=--max_old_space_size=4096 npm run dev
  ```

**Slow Rendering:**
- Collapse deeply nested nodes in tree view
- Use search/filter to reduce visible nodes
- Switch to raw editor for large files

---

## 🚢 Deployment

### Deploy to Vercel (Recommended - 1-Click)

1. **Push to GitHub**
   ```bash
   git init
   git add .
   git commit -m "Initial commit"
   git remote add origin https://github.com/yourusername/json-vision.git
   git push -u origin main
   ```

2. **Connect to Vercel**
   - Visit [vercel.com/new](https://vercel.com/new)
   - Import your GitHub repository
   - Vercel auto-detects Next.js
   - Click "Deploy"
   - Done! 🎉

3. **Custom Domain (Optional)**
   - Go to project settings
   - Add your domain
   - Update DNS records
   - SSL automatically configured

### Deploy to Netlify

```bash
# Install Netlify CLI
npm install -g netlify-cli

# Build and deploy
npm run build
netlify deploy --prod
```

### Deploy to Railway

```bash
# Install Railway CLI
npm install -g railway

# Login and deploy
railway login
railway init
railway up
```

### Deploy with Docker

```dockerfile
# Dockerfile
FROM node:18-alpine
WORKDIR /app
COPY package*.json ./
RUN npm install
COPY . .
RUN npm run build
EXPOSE 3000
CMD ["npm", "start"]
```

```bash
# Build and run
docker build -t json-vision .
docker run -p 3000:3000 json-vision
```

### Environment Variables

Create `.env.local` for environment-specific config:

```bash
NEXT_PUBLIC_API_URL=your-api-url
NEXT_PUBLIC_ANALYTICS_ID=your-analytics-id
```

---

## 🤝 Contributing

We welcome contributions! Here's how to get started:

### Development Workflow

1. **Fork the repository**
2. **Create a feature branch**
   ```bash
   git checkout -b feature/amazing-feature
   ```
3. **Make your changes**
4. **Test thoroughly**
   ```bash
   npm run build
   npm start
   ```
5. **Commit your changes**
   ```bash
   git commit -m "Add amazing feature"
   ```
6. **Push to your fork**
   ```bash
   git push origin feature/amazing-feature
   ```
7. **Open a Pull Request**

### Code Style

- Follow TypeScript best practices
- Use functional components with hooks
- Maintain consistent formatting (Prettier recommended)
- Add comments for complex logic
- Keep components under 300 lines

### Commit Messages

Follow conventional commits:
- `feat:` New feature
- `fix:` Bug fix
- `docs:` Documentation
- `style:` Formatting
- `refactor:` Code restructuring
- `test:` Tests
- `chore:` Maintenance

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2025 JSON Vision

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
```

---

## 🙏 Acknowledgments

### Inspiration
- [JSONPath Finder](https://jsonpath.com/) - JSONPath testing
- [JSON Editor Online](https://jsoneditoronline.org/) - Classic JSON editor
- [JSON Crack](https://jsoncrack.com/) - Visual JSON editing

### Technologies
- **Next.js Team** - Amazing framework
- **Vercel** - Hosting and deployment platform
- **Lucide** - Beautiful icon set
- **Tailwind Labs** - CSS framework

### Community
- All contributors who have helped improve this project
- Open source community for inspiration and feedback
- Users who provided feature requests and bug reports

---

## 📞 Support

### Get Help

- 📧 **Email**: support@jsonvision.dev
- 💬 **Discord**: [Join our community](https://discord.gg/jsonvision)
- 🐛 **Issues**: [GitHub Issues](https://github.com/yourusername/json-vision/issues)
- 📖 **Docs**: [Full Documentation](https://docs.jsonvision.dev)

### Stay Updated

- ⭐ Star this repo to show support
- 👀 Watch for updates and releases
- 🐦 Follow on [Twitter](https://twitter.com/jsonvision)
- 📰 Read our [Blog](https://blog.jsonvision.dev)

---

## 🗺️ Roadmap

### Coming Soon
- [ ] JSON Schema validation
- [ ] Compare/Diff two JSON files
- [ ] Export to multiple formats (YAML, XML, CSV)
- [ ] Collaborative editing with real-time sync
- [ ] AI-powered data insights
- [ ] Browser extension
- [ ] VS Code extension
- [ ] Dark/Light theme toggle
- [ ] Custom color themes
- [ ] Keyboard shortcuts panel
- [ ] History/undo system
- [ ] Save to cloud (optional)

### Future Ideas
- GraphQL schema visualization
- API endpoint testing
- Mock data generation
- Performance profiling
- TypeScript interface generator
- Documentation generator

---

<div align="center">

**Made with ❤️ by [Hardik Joshi](https://github.com/yourusername)**

[⬆ Back to Top](#json-vision-)

---

[![GitHub](https://img.shields.io/badge/GitHub-181717?style=for-the-badge&logo=github)](https://github.com/yourusername/json-vision)
[![Twitter](https://img.shields.io/badge/Twitter-1DA1F2?style=for-the-badge&logo=twitter&logoColor=white)](https://twitter.com/yourhandle)
[![Website](https://img.shields.io/badge/Website-4285F4?style=for-the-badge&logo=google-chrome&logoColor=white)](https://jsonvision.dev)

</div>
