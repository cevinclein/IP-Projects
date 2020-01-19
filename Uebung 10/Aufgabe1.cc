#include <iostream>
#include <string>
#include <fstream>

//Lines zu Datei hinzufügen.
void writeLinesToFile(std::string s)
{
    //Dateiendung hinzufügen wenn nicht vorhanden.
    std::string readfile = s + ".txt";
    std::string writefile = s + "-a.txt";

    //Datei zum Lesen öffnen.
    std::ifstream ifile;
    ifile.open(readfile, std::ios::in);

    //Datei zum schreiben öffnen.
    std::ofstream ofile;
    ofile.open(writefile, std::ios::out | std::ios::app);

    //Zeilen hinzufügen.
    std::string line;
    int i = 0;

    //Line für Line auslesen.
    while (ifile.good())
    {
        i++;
        std::string j = std::to_string(i);
        std::getline(ifile, line);
        line = j + " : " + line;
        std::cout << line;
        ofile << line << std::endl;
    }
   
    //Datei schließen.
    ifile.close();
    ofile.close();
}

int main(int argc, char **argv)
{
    //Datei von standarteingabe lesen.
    //Bitte ohne Dateiendung angeben, also ohne .txt, sondern nur der Name der Datei!
    writeLinesToFile(argv[1]);
    return 0;
}