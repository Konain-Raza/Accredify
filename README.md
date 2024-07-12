# Accredify - Bulk Certificate Maker 🎓📜
<div style="text-align: center;">
    <img src="https://konainraza.vercel.app/assets/Accredify-yEZsyPMN.png" alt="Accredify Logo" style="max-width: 100%; height: auto;">
</div>


Welcome to Accredify, your trusty sidekick for bulk certificate making, designed to effortlessly churn out certificates from a CSV file using a LaTeX template. Perfect for organizations like GDSC (Google Developer Student Clubs) and MSDC (Microsoft Student Developer Clubs), Accredify automates the tedious task of creating certificates for hordes of students. 📊✍️ Say goodbye to manual processes and hello to automated bliss. Accredify is here to save you from the certificate-making chaos! 🏆✨🎓

## Features 🌟

- 📁 **CSV Input**: Read participant names from a CSV file.
- 📝 **LaTeX Template**: Use a customizable LaTeX template for certificates.
- 🔄 **Automatic Sorting**: Sort participant names alphabetically.
- 📑 **PDF Generation**: Compile LaTeX files to PDF format.
- 📂 **Output Management**: Save certificates in an organized folder and clean up temporary files.

## Getting Started 🚀

### Prerequisites 🛠️

Ensure you have the following installed:

- **C++ Compiler** (e.g., `g++`)
- **pdflatex** (LaTeX distribution)

#### Install pdflatex

- **Ubuntu**:
    ```bash
    sudo apt-get install texlive-latex-base
    ```
- **Windows**:
    - Download and install [MiKTeX](https://miktex.org/download).
- **macOS**:
    ```bash
    brew install mactex
    ```

### Installation 📥

1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/accredify.git
    cd accredify
    ```

2. **Compile the program**:
    ```bash
    g++ -o accredify main.cpp -std=c++17
    ```

### Usage 📖

1. **Prepare your CSV file** with participant names (e.g., `participants.csv`).

2. **Run the program**:
    ```bash
    ./accredify
    ```

3. **Follow the on-screen instructions** to provide the necessary details:
    - Path to the CSV file containing participant names.
    - Name of the certificate.
    - Name of your organization.
    - Certification issue date.

### Customizing the LaTeX Template 📄

Accredify uses a constant LaTeX template that you can modify as needed. The template includes placeholders for:
- `ApplicantName`
- `LOGO_FILENAME`
- `CertificateName`
- `OrganizationName`
- `Dateformat`

When running the program, these placeholders will be replaced with the corresponding information for each participant, ensuring consistency and accuracy across all generated certificates.

### Example LaTeX Template PDF 📄

An example PDF of the template is provided in the repository for your reference.

### Contributing 🤝

Contributions are welcome! Feel free to submit issues and pull requests. For major changes, please open an issue first to discuss what you would like to change.

### License 📜

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
