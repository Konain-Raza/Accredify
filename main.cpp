#include <iostream>
<<<<<<< HEAD
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;
=======
#include <fstream>    // for file handling
#include <filesystem> // for creating folder and files
#include <cctype>     // for to tolower funtion
#include <stdexcept>  // for catching errors
using namespace std;
>>>>>>> 1d72eca (finalized project v1.0)

class Node
{
public:
<<<<<<< HEAD
    string name;
    Node *next;

    Node(const string &name) : name(name), next(nullptr) {}
};

class LinkedList
{
public:
    LinkedList() : head(nullptr) {}

=======
    string name; // data
    Node *next;  // next pointer

    Node(const string &name)
    {
        this->name = name;
        this->next = nullptr;
    }
};
// singly linked list
class LinkedList
{
public:
    LinkedList()
    {
        head = nullptr;
    }
    // for storing all names from csv file in linked list
>>>>>>> 1d72eca (finalized project v1.0)
    void append(const string &name)
    {
        Node *newNode = new Node(name);
        if (!head)
        {
            head = newNode;
        }
        else
        {
            Node *temp = head;
            while (temp->next)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }
<<<<<<< HEAD

    void sort()
    {
        if (!head || !head->next)
            return; // No need to sort if list has 0 or 1 node

        Node *current = head;
        Node *index = nullptr;
        string temp;

        while (current)
        {
            index = current->next;
            while (index)
            {
                if (tolower(current->name[0]) > tolower(index->name[0]))
                { // Compare only the first letter, case-insensitive
                    temp = current->name;
                    current->name = index->name;
                    index->name = temp;
                }
                index = index->next;
            }
            current = current->next;
        }
    }

    void print() const
    {
        Node *temp = head;
        while (temp)
        {
            cout << temp->name << endl;
            temp = temp->next;
        }
    }

    ~LinkedList()
    {
        Node *current = head;
        while (current)
        {
            Node *next = current->next;
            delete current;
            current = next;
=======
    // sort names alphabetically
    void sort()
    {
        if (!head || !head->next)
            return;
        for (Node *i = head; i->next; i = i->next)
        {
            for (Node *j = i->next; j; j = j->next)
            {
                if (tolower(i->name[0]) > tolower(j->name[0]))
                {
                    swap(i->name, j->name);
                }
            }
>>>>>>> 1d72eca (finalized project v1.0)
        }
    }

    Node *getHead() const
    {
        return head;
    }

<<<<<<< HEAD
=======
    ~LinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

>>>>>>> 1d72eca (finalized project v1.0)
private:
    Node *head;
};

<<<<<<< HEAD
void readNamesFromCSV(const string &filename, LinkedList &list)
=======
void readNamesFromCSV(const string &filename, LinkedList &list) // append all names from csv file in linked list
>>>>>>> 1d72eca (finalized project v1.0)
{
    ifstream file(filename);
    if (!file.is_open())
    {
<<<<<<< HEAD
        cerr << "Error: Could not open the file." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        list.append(line);
    }

    file.close();
}

string readTemplateFile(const string &filename)
{
    ifstream templateFile(filename);
    if (!templateFile.is_open())
    {
        cerr << "Error: Could not open the template file." << endl;
        return "";
    }

    string content;
    char ch;
    while (templateFile.get(ch))
    {
        content += ch;
    }
    templateFile.close();
    return content;
}

void replacePlaceholder(string &content, const string &placeholder, const string &replacement)
{
    size_t pos = content.find(placeholder);
    while (pos != string::npos)
    {
        content.replace(pos, placeholder.length(), replacement);
        pos = content.find(placeholder, pos + replacement.length());
    }
}

void generateCertificate(const string &templateContent, const string &name, const string &outputFilename)
{
    string certificateContent = templateContent;
    replacePlaceholder(certificateContent, "\\textbf{Your Name}", name);

    ofstream outputFile(outputFilename);
    if (!outputFile.is_open())
    {
        cerr << "Error: Could not create the output file." << endl;
        return;
    }
    outputFile << certificateContent;
    outputFile.close();
}

void compilePDF(const string &latexFile, const string &outputFolder)
{
    string command = "pdflatex -interaction=batchmode -output-directory=\"" + outputFolder + "\" \"" + latexFile + "\""; // Enclose filename and output folder in quotes
    if (std::system(command.c_str()) != 0)
    {
        cerr << "Error: Failed to compile PDF for file " << latexFile << endl;
    }
}

void generateCertificates(const LinkedList &list, const string &templateFilename, const string &outputFolder)
{
    // Check if the output folder exists, if not, create it
    if (!fs::exists(outputFolder))
    {
        if (!fs::create_directory(outputFolder))
        {
            cerr << "Error: Failed to create output folder." << endl;
            return;
        }
    }

    string templateContent = readTemplateFile(templateFilename);

    Node *current = list.getHead();
    while (current)
    {
        // Remove spaces from the name to ensure the filename is valid
        string nameWithoutSpaces = current->name;
        nameWithoutSpaces.erase(remove_if(nameWithoutSpaces.begin(), nameWithoutSpaces.end(), ::isspace), nameWithoutSpaces.end());

        string texFilename = outputFolder + "/" + nameWithoutSpaces + ".tex"; // Use the name as the filename
        generateCertificate(templateContent, current->name, texFilename);
        compilePDF(texFilename, outputFolder); // Compile LaTeX to PDF
        fs::remove(texFilename);               // Remove the .tex file
        current = current->next;
    }

    // Remove intermediate .aux and .log files
    for (const auto &entry : fs::directory_iterator(outputFolder))
    {
        const auto &path = entry.path();
        if (path.extension() == ".aux" || path.extension() == ".log")
        {
            fs::remove(path);
        }
    }

    cout << "Certificates generated successfully." << endl;
=======
        throw runtime_error("Failed to open the file: " + filename);
    }

    string line;

    while (getline(file, line)) // store all names and append into linkedlist till file is not finish
    {
        list.append(line);
    }
    file.close();
}
// read latex template file
string readTemplateFile(string filename)
{
    string content;
    ifstream templateFile(filename);
    if (!templateFile.is_open())
    {
        throw runtime_error("Error: Could not open the template file: " + filename);
    }

    char data;
    while (templateFile.get(data)) // store whole content of latex template
    {
        content += data;
    }
    templateFile.close();

    return content;
}
// replace placeholder in latex file
void replacePlaceholder(string &content, const string &placeholder, const string &replacement)
{
    try
    {
        size_t pos = content.find(placeholder);
        while (pos != string::npos)
        {
            content.replace(pos, placeholder.length(), replacement);
            pos = content.find(placeholder, pos + replacement.length());
        }
    }
    catch (const std::exception &e)
    {
        cout << e.what() << '\n';
    }
}
// compile latex .tex file into pdf
void compilePDF(string latexFile, string outputFolder)
{
    try
    {
        string command = "pdflatex -interaction=batchmode -output-directory=\"" + outputFolder + "\" \"" + latexFile + "\" > /dev/null 2>&1";
        if (system(command.c_str()) != 0)
        {
            cout << "Error: Failed to compile PDF for file " << latexFile << endl;
            exit(0);
        }
    }
    catch (const exception &e)
    {
        cout << e.what() << '\n';
    }
}
// generate certifcates for all names in linked list and place in outputFolder
void generateCertificates(LinkedList &list, string templateFilename, string outputFolder, string logoFilename, string certificateName, string organizationName, string certificateDate)
{
    try
    {
        if (!filesystem::exists(outputFolder))
        {
            if (!filesystem::create_directory(outputFolder))
            {
                cout << "Error: Failed to create output folder." << endl;
                return;
            }
        }

        string templateContent = readTemplateFile(templateFilename);
        Node *current = list.getHead();
        int totalCertificates = 0;

        // Count total certificates
        while (current)
        {
            totalCertificates++;
            current = current->next;
        }

        // Reset current to the head of the list
        current = list.getHead();

        int completedCertificates = 0;
        float progress = 0.0f;
        int progressBarWidth = 50;
        // remove whitespaces from filenames and marge
        while (current)
        {
            string nameWithoutSpaces;
            for (char ch : current->name)
            {
                if (!isspace(ch))
                {
                    nameWithoutSpaces += ch;
                }
            }

            string certificateContent = templateContent;

            // replacing placeholder from latex template for every name
            replacePlaceholder(certificateContent, "ApplicantName", current->name);
            replacePlaceholder(certificateContent, "LOGO_FILENAME", logoFilename);
            replacePlaceholder(certificateContent, "CertificateName", certificateName);
            replacePlaceholder(certificateContent, "OrganizationName", organizationName);
            replacePlaceholder(certificateContent, "Dateformat", certificateDate);

            string texFilename = outputFolder + "/" + nameWithoutSpaces + ".tex";
            ofstream outputFile(texFilename);
            if (!outputFile.is_open())
            {
                cout << "Error: Could not create the output file." << endl;
                current = current->next;
                continue;
            }
            outputFile << certificateContent;
            outputFile.close();

            compilePDF(texFilename, outputFolder);

            completedCertificates++;

            // Calculate progress percentage
            progress = (float)completedCertificates / totalCertificates * 100;

            //  progress bar
            cout << "Progress: [";
            int pos = progressBarWidth * progress / 100;
            for (int i = 0; i < progressBarWidth; ++i)
            {
                if (i < pos)
                    cout << "=";
                else
                    cout << " ";
            }
            cout << "] " << int(progress) << "%\r";
            cout.flush();

            current = current->next;
        }

        cout << endl;

        for (const auto &entry : filesystem::directory_iterator(outputFolder)) // deleting unecessary files other than pdf
        {
            if (entry.path().extension() != ".pdf")
            {
                filesystem::remove(entry);
            }
        }
    }
    catch (const exception &ex)
    {
        cout << ex.what() << endl;
    }
>>>>>>> 1d72eca (finalized project v1.0)
}

int main()
{
    LinkedList nameList;
<<<<<<< HEAD

    // Read names from CSV and store in the linked list
    readNamesFromCSV("participants.csv", nameList);

    // Sort names alphabetically
    nameList.sort();

    // Print the sorted names
    cout << "Sorted Names:" << endl;
    nameList.print();

    // Generate certificates using the sorted names
    generateCertificates(nameList, "certificate.tex", "Certificates");
=======
    string templateFileName, certificateName, organizationName, logoFilename, certificateDate, csvFilePath;
    cout << "##########################################################\n";
    cout << "#                                                        #\n";
    cout << "#            Accredify - Bulk Certificate Maker          #\n";
    cout << "#                                                        #\n";
    cout << "##########################################################\n\n";

    cout << "Please provide the following details to generate certificates:\n";

    templateFileName = "certificate.tex";
    cout << "1. Enter the path of the CSV file containing participant names with the extension (e.g., /participants.csv): ";
    getline(cin, csvFilePath);
    cout << "2. Enter the name of the certificate: ";
    getline(cin, certificateName);

    cout << "3. Enter the name of your organization: ";
    getline(cin, organizationName);

    cout << "4. Enter the file path of your organization's logo with the extension: (e.g., /logo.png)";
    getline(cin, logoFilename);

    cout << "5. Enter the certification issue date (e.g., June 2, 2024): ";
    getline(cin, certificateDate);

    try
    {
        readNamesFromCSV(csvFilePath, nameList);
        nameList.sort();

        // Generate certificates
        generateCertificates(nameList, templateFileName, "Certificates", logoFilename, certificateName, organizationName, certificateDate);

        cout << "============================================================\n";
        cout << "        All certificates have been generated                 \n";
        cout << "============================================================\n";
    }
    catch (const exception &ex)
    {
        cout << "Error: " << ex.what() << endl;
    }
>>>>>>> 1d72eca (finalized project v1.0)

    return 0;
}
