#include <iostream>
#include <fstream>    // for file handling
#include <filesystem> // for creating folder and files
#include <cctype>     // for to tolower funtion
#include <stdexcept>  // for catching errors
using namespace std;

class Node
{
public:
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
        }
    }

    Node *getHead() const
    {
        return head;
    }

    ~LinkedList()
    {
        while (head)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

private:
    Node *head;
};

void readNamesFromCSV(const string &filename, LinkedList &list) // append all names from csv file in linked list
{
    ifstream file(filename);
    if (!file.is_open())
    {
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
}

int main()
{
    LinkedList nameList;
    string templateFileName, logoDestination, certificateName, organizationName, logoFilename, certificateDate, csvFilePath;
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
    getline(cin, logoDestination);

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

    return 0;
}
