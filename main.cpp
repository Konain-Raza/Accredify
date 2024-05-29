#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <algorithm>

using namespace std;
namespace fs = std::filesystem;

class Node
{
public:
    string name;
    Node *next;

    Node(const string &name) : name(name), next(nullptr) {}
};

class LinkedList
{
public:
    LinkedList() : head(nullptr) {}

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
        }
    }

    Node *getHead() const
    {
        return head;
    }

private:
    Node *head;
};

void readNamesFromCSV(const string &filename, LinkedList &list)
{
    ifstream file(filename);
    if (!file.is_open())
    {
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
}

int main()
{
    LinkedList nameList;

    // Read names from CSV and store in the linked list
    readNamesFromCSV("participants.csv", nameList);

    // Sort names alphabetically
    nameList.sort();

    // Print the sorted names
    cout << "Sorted Names:" << endl;
    nameList.print();

    // Generate certificates using the sorted names
    generateCertificates(nameList, "certificate.tex", "Certificates");

    return 0;
}
