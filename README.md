<!DOCTYPE html>
<html>
<head>
</head>
<body>
  <h1>🔥 Basic Firewall Project</h1>

  <p>This repository contains my attempt at developing a firewall. The goal of this project is to create a functional firewall that can filter network traffic based on predefined rules.</p>

  <h2>Project Overview</h2>

  <ul>
    <li>📁 <code>src/main.cpp</code>: The main source code file for the firewall program.</li>
    <li>📄 <code>docs/info.md</code>: A README file that explains code structure and troubleshooting.</li>
    <li>📝 <code>README.md</code>: The documentation file explaining the project.</li>
  </ul>

  <h2>Development Environment</h2>

  <p>To develop and run this firewall project, you will need:</p>

  <ul>
    <li>🖥️ Operating System: Windows 10, 11 or Linux/GNU based system (Ubuntu Recommended)</li>
    <li>🔧 Compiler: Any Windows C++ Compiler or Linux/GNU compiler (GCC)</li>
  </ul>

  <h2>Getting Started</h2>

  <p>Follow these steps to get started with the firewall project:</p>

  <ol>
    <li>🔀 Clone the repository to your local machine using the following command:</li>
  </ol>

  <pre><code>git clone https://github.com/your-username/firewall.git</code></pre>

  <ol start="2">
    <li>🛠️ Make sure you have the necessary development environment set up (MSYS with GCC).</li>
    <li>🖥️ Open the MSYS terminal and navigate to the project directory:</li>
  </ol>

  <pre><code>cd /path/to/firewall</code></pre>

  <ol start="4">
    <li>📋 Review the <code>rules.txt</code> file to understand the predefined rules for the firewall.</li>
    <li>🔨 Build the firewall program by compiling the <code>firewall.cpp</code> source code:</li>
  </ol>

  <pre><code>g++ -o firewall main.cpp -lssl -lcrypto </code></pre>

  <ol start="6">
    <li>▶️ Run the compiled firewall program:</li>
  </ol>
  <p>Windows Based OS</p>
  <pre><code>./firewall.exe</code></pre>
  <p>Linux Based OS</p>
  <pre><code>./firewall</code></pre>

  <ol start="7">
    <li>🔬 Test the firewall functionality by sending network traffic and observing the filtering based on the predefined rules.</li>
  </ol>

  <h2>Contribution</h2>

  <p>If you would like to contribute to this firewall project, you can follow these steps:</p>

  <!-- Add an emoji and an example picture -->
  <p>🔀 Fork this repository.</p>

  <ol>
    <li>🌿 Create a new branch for your changes:</li>
  </ol>

  <pre><code>git checkout -b feature/your-feature</code></pre>

  <ol start="3">
    <li>🔧 Make the necessary changes and additions to the code.</li>
    <li>🧪 Test your changes to ensure they work correctly.</li>
    <li>💾 Commit your changes with descriptive commit messages:</li>
  </ol>

  <pre><code>git commit -m "Add feature X"</code></pre>

  <ol start="6">
    <li>🔀 Push your changes to your forked repository:</li>
  </ol>

  <pre><code>git push origin feature/your-feature</code></pre>

  <ol start="7">
    <li>🔀 Open a pull request on the original repository to merge your changes.</li>
  </ol>

  <p>Please make sure to adhere to the project's coding style and guidelines.</p>

  <h2>License</h2>

  <p>This project is licensed under the <a href="LICENSE">MIT License</a>. Feel free to modify and distribute the code according to the terms of the license.</p>
</body>
</html>
