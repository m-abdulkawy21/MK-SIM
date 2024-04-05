#include <iostream>
#include <fstream>
#include <random>
#include <new>
#include <vector>
#include <ctime>
#include <climits>
#include <string>
using namespace std;

string jobTitles[5] = { "none", "Quaes", "Aedile", "Praetor", "Consul" };

int StabilityScore = 100;

class Statesman
{
public:
    int age;
    int title;
    int serviceDuration;
    int consulTerm;

    void initiate()
    {
        this->age = rand() % 55 + 25;
        this->serviceDuration = 0;
        this->title = 0;
        this->consulTerm = 0;
    }

    bool operator == (Statesman other)
    {
        return this->age == other.age && this->title == other.title && this->serviceDuration == other.serviceDuration;
    }
};

vector<Statesman> newbieQuaestors;
vector<Statesman> selectedConsuls;

int averageConsulAge = 0;
int averagePraetorAge = 0;
int averageAedileAge = 0;
int averageQuaestorAge = 0;

int lowestConsulAge = INT_MAX;
int lowestPraetorAge = INT_MAX;
int lowestAedileAge = INT_MAX;
int lowestQuaestorAge = INT_MAX;

int highestConsulAge = 0;
int highestPraetorAge = 0;
int highestAedileAge = 0;
int highestQuaestorAge = 0;

int consulCount = 0;
int praetorCount = 0;
int aedileCount = 0;
int quaestorCount = 0;

bool isConsulSelected(Statesman s)
{
    for (size_t i = 0; i < selectedConsuls.size(); i++)
    {
        if (selectedConsuls[i] == s)
        {
            return true;
        }
    }
    return false;
}

void setup(vector<Statesman>& nominees)
{
    Statesman nominee;
    int Quaestors = 0;
    int Aediles = 0;
    int Praetors = 0;
    int Consuls = 0;

    for (int i = 0; i < 40; i++)
    {
        nominee.initiate();
        if (nominee.age >= 42)
        {
            if (Consuls < 2)
            {
                Consuls++;
                nominee.title = 4;
                nominee.serviceDuration = 6;
            }
            else if (Praetors < 8)
            {
                Praetors++;
                nominee.title = 3;
                nominee.serviceDuration = 4;
            }
            else if (Aediles < 10)
            {
                Aediles++;
                nominee.title = 2;
                nominee.serviceDuration = 2;
            }
            else if (Quaestors < 20)
            {
                Quaestors++;
                newbieQuaestors.push_back(nominee);
                nominee.title = 1;
                nominee.serviceDuration = 0;
            }
        }
        else if (nominee.age >= 39)
        {
            if (Praetors < 8)
            {
                Praetors++;
                nominee.title = 3;
                nominee.serviceDuration = 4;
            }
            else if (Aediles < 10)
            {
                Aediles++;
                nominee.title = 2;
                nominee.serviceDuration = 2;
            }
            else if (Quaestors < 20)
            {
                Quaestors++;
                nominee.title = 1;
                nominee.serviceDuration = 0;
            }
        }
        else if (nominee.age >= 36)
        {
            if (Aediles < 10)
            {
                Aediles++;
                nominee.title = 2;
                nominee.serviceDuration = 2;
            }
            else if (Quaestors < 20)
            {
                Quaestors++;
                nominee.title = 1;
                nominee.serviceDuration = 0;
            }
        }
        else if (nominee.age >= 30)
        {
            if (Quaestors < 20)
            {
                Quaestors++;
                nominee.title = 1;
                nominee.serviceDuration = 0;
            }
            else
            {
                nominee.serviceDuration = 0;
                nominee.title = 0;
            }
        }
        else
        {
            nominee.serviceDuration = 0;
            nominee.title = 0;
        }

        nominees.push_back(nominee);
    }
}

void progressYear(vector<Statesman>& nominees)
{
    vector<Statesman> candidatePool;
    vector<Statesman> yearlyConsuls;
    vector<Statesman> yearlyPraetors;
    vector<Statesman> yearlyAediles;
    vector<Statesman> yearlyQuaestors;
    int QuaestorsNeeded = 0;
    int AedilesNeeded = 0;
    int PraetorsNeeded = 0;
    int ConsulsNeeded = 0;

    for (int i = 0; i < nominees.size(); i++)
    {
        nominees[i].age++;
        nominees[i].serviceDuration++;
        if (nominees[i].title == 4)
        {
            nominees[i].consulTerm++;
        }
        if (nominees[i].age < 80)
        {
            candidatePool.push_back(nominees[i]);
        }
    }

    for (size_t i = 0; i < newbieQuaestors.size(); i++)
    {
        if (newbieQuaestors[i].age >= 80)
        {
            newbieQuaestors.erase(newbieQuaestors.begin() + i);
            i--;
        }
    }

    Statesman freshNominee;

    for (int i = 0; i < 15; i++)
    {
        freshNominee.initiate();
        candidatePool.push_back(freshNominee);
    }
    for (size_t i = 0; i < newbieQuaestors.size(); i++)
    {
        candidatePool.push_back(newbieQuaestors[i]);
    }

    for (size_t i = 0; i < candidatePool.size(); i++)
    {
        if (candidatePool[i].serviceDuration >= 6 && candidatePool[i].age >= 42)
        {
            if (ConsulsNeeded < 2)
            {
                candidatePool[i].title = 4;
                ConsulsNeeded++;
                yearlyConsuls.push_back(candidatePool[i]);
            }
            else if (PraetorsNeeded < 8)
            {
                candidatePool[i].title = 3;
                PraetorsNeeded++;
                yearlyPraetors.push_back(candidatePool[i]);
            }
        }
        else if (candidatePool[i].serviceDuration >= 4 && candidatePool[i].age >= 39)
        {
            if (PraetorsNeeded < 8)
            {
                candidatePool[i].title = 3;
                PraetorsNeeded++;
                yearlyPraetors.push_back(candidatePool[i]);
            }
            else if (AedilesNeeded < 10)
            {
                candidatePool[i].title = 2;
                AedilesNeeded++;
                yearlyAediles.push_back(candidatePool[i]);
            }
        }
        else if (candidatePool[i].serviceDuration >= 2 && candidatePool[i].age >= 36)
        {
            if (AedilesNeeded < 10)
            {
                candidatePool[i].title = 2;
                AedilesNeeded++;
                yearlyAediles.push_back(candidatePool[i]);
            }
            else if (QuaestorsNeeded < 20)
            {
                candidatePool[i].title = 1;
                QuaestorsNeeded++;
                yearlyQuaestors.push_back(candidatePool[i]);
            }
        }
        else if (candidatePool[i].serviceDuration >= 0 && candidatePool[i].age >= 30)
        {
            if (QuaestorsNeeded < 20)
            {
                candidatePool[i].title = 1;
                QuaestorsNeeded++;
                yearlyQuaestors.push_back(candidatePool[i]);
            }
        }
    }

    for (size_t i = 0; i < selectedConsuls.size(); i++)
    {
        if (selectedConsuls[i].age > 80 || selectedConsuls[i].consulTerm >= 10)
        {
            selectedConsuls.erase(selectedConsuls.begin() + i);
            i--;
        }
    }

    nominees.clear();
    int consulTotalAge = 0;
    int praetorTotalAge = 0;
    int aedileTotalAge = 0;
    int quaestorTotalAge = 0;
    int selectIndex = 0;

    QuaestorsNeeded = 0;
    AedilesNeeded = 0;
    PraetorsNeeded = 0;
    ConsulsNeeded = 0;

    int leastConsulAge = INT_MAX;
    int leastPraetorAge = INT_MAX;
    int leastAedileAge = INT_MAX;
    int leastQuaestorAge = INT_MAX;

    int mostConsulAge = 0;
    int mostPraetorAge = 0;
    int mostAedileAge = 0;
    int mostQuaestorAge = 0;

    int sizeConsuls = yearlyConsuls.size();
    int sizePraetors = yearlyPraetors.size();
    int sizeAediles = yearlyAediles.size();
    int sizeQuaestors = yearlyQuaestors.size();

    bool wasSelected = false;

    for (int i = 0; i < 40; i++)
    {
        if (i < sizeConsuls)
        {
            selectIndex = rand() % yearlyConsuls.size();
            nominees.push_back(yearlyConsuls[selectIndex]);
            if (leastConsulAge > nominees.back().age)
            {
                leastConsulAge = nominees.back().age;
            }
            if (mostConsulAge < nominees.back().age)
            {
                mostConsulAge = nominees.back().age;
            }
            consulTotalAge += nominees.back().age;
            if (yearlyConsuls[selectIndex].consulTerm >= 10)
            {
                StabilityScore -= 10;
            }
            else
            {
                selectedConsuls.push_back(yearlyConsuls[selectIndex]);
            }

            ConsulsNeeded++;
            yearlyConsuls.erase(yearlyConsuls.begin() + selectIndex);
        }
        else if (i >= sizeConsuls && i < sizeConsuls + sizePraetors)
        {
            selectIndex = rand() % yearlyPraetors.size();
            nominees.push_back(yearlyPraetors[selectIndex]);
            if (leastPraetorAge > nominees.back().age)
            {
                leastPraetorAge = nominees.back().age;
            }
            if (mostPraetorAge < nominees.back().age)
            {
                mostPraetorAge = nominees.back().age;
            }
            praetorTotalAge += nominees.back().age;
            PraetorsNeeded++;
            yearlyPraetors.erase(yearlyPraetors.begin() + selectIndex);
        }
        else if (i >= sizeConsuls + sizePraetors && i < sizeConsuls + sizePraetors + sizeAediles)
        {
            selectIndex = rand() % yearlyAediles.size();
            nominees.push_back(yearlyAediles[selectIndex]);

            if (leastAedileAge > nominees.back().age)
            {
                leastAedileAge = nominees.back().age;
            }
            if (mostAedileAge < nominees.back().age)
            {
                mostAedileAge = nominees.back().age;
            }

            aedileTotalAge += nominees.back().age;
            AedilesNeeded++;
            yearlyAediles.erase(yearlyAediles.begin() + selectIndex);
        }
        else if (i >= sizeConsuls + sizePraetors + sizeAediles && i < sizeConsuls + sizePraetors + sizeAediles + sizeQuaestors)
        {
            selectIndex = rand() % yearlyQuaestors.size();
            nominees.push_back(yearlyQuaestors[selectIndex]);
            if (leastQuaestorAge > nominees.back().age)
            {
                leastQuaestorAge = nominees.back().age;
            }
            if (mostQuaestorAge < nominees.back().age)
            {
                mostQuaestorAge = nominees.back().age;
            }
            quaestorTotalAge += nominees.back().age;
            QuaestorsNeeded++;
            yearlyQuaestors.erase(yearlyQuaestors.begin() + selectIndex);
        }
    }
    int totalIndividuals = ConsulsNeeded + PraetorsNeeded + AedilesNeeded + QuaestorsNeeded;
    StabilityScore -= (40 - totalIndividuals) * 5;

    ofstream fileWriter("index.txt", ios::app);

    int percentageFilled = (float)(QuaestorsNeeded / 20) * 100;
    fileWriter << "Quaestor ";
    fileWriter << to_string(percentageFilled);
    fileWriter << '%';
    fileWriter << '\t';

    fileWriter << to_string(leastQuaestorAge);
    fileWriter << ':';
    fileWriter << to_string(quaestorTotalAge / QuaestorsNeeded);
    fileWriter << ':';
    fileWriter << to_string(mostQuaestorAge);
    fileWriter << '\t';

    percentageFilled = (float)(AedilesNeeded / 10) * 100;
    fileWriter << "Aedile ";
    fileWriter << to_string(percentageFilled);
    fileWriter << '%';
    fileWriter << '\t';

    fileWriter << to_string(leastAedileAge);
    fileWriter << ':';
    fileWriter << to_string(aedileTotalAge / AedilesNeeded);
    fileWriter << ':';
    fileWriter << to_string(mostAedileAge);
    fileWriter << '\t';

    percentageFilled = (float)(PraetorsNeeded / 8) * 100;
    fileWriter << "Praetor ";
    fileWriter << to_string(percentageFilled);
    fileWriter << '%';
    fileWriter << '\t';

    fileWriter << to_string(leastPraetorAge);
    fileWriter << ':';
    fileWriter << to_string(praetorTotalAge / PraetorsNeeded);
    fileWriter << ':';
    fileWriter << to_string(mostPraetorAge);
    fileWriter << '\t';

    percentageFilled = (float)(ConsulsNeeded / 2) * 100;
    fileWriter << "Consul ";
    fileWriter << to_string(percentageFilled);
    fileWriter << '%';
    fileWriter << '\t';
    fileWriter << to_string(leastConsulAge);

    fileWriter << ':';
    fileWriter << to_string(consulTotalAge / ConsulsNeeded);
    fileWriter << ':';
    fileWriter << to_string(mostConsulAge);
    fileWriter << '\t';

    fileWriter << to_string(StabilityScore);
    fileWriter << '\n';
    fileWriter.close();
    averageConsulAge += consulTotalAge / ConsulsNeeded;
    averagePraetorAge += praetorTotalAge / PraetorsNeeded;
    averageAedileAge += aedileTotalAge / AedilesNeeded;
    averageQuaestorAge += quaestorTotalAge / QuaestorsNeeded;

    consulCount += ConsulsNeeded;
    praetorCount += PraetorsNeeded;
    aedileCount += AedilesNeeded;
    quaestorCount += QuaestorsNeeded;

    if (lowestConsulAge > leastConsulAge)
    {
        lowestConsulAge = leastConsulAge;
    }
    if (highestConsulAge < mostConsulAge)
    {
        highestConsulAge = mostConsulAge;
    }

    if (lowestPraetorAge > leastPraetorAge)
    {
        lowestPraetorAge = leastPraetorAge;
    }
    if (highestPraetorAge < mostPraetorAge)
    {
        highestPraetorAge = mostPraetorAge;
    }

    if (lowestAedileAge > leastAedileAge)
    {
        lowestAedileAge = leastAedileAge;
    }
    if (highestAedileAge < mostAedileAge)
    {
        highestAedileAge = mostAedileAge;
    }

    if (lowestQuaestorAge > leastQuaestorAge)
    {
        lowestQuaestorAge = leastQuaestorAge;
    }
    if (highestQuaestorAge < mostQuaestorAge)
    {
        highestQuaestorAge = mostQuaestorAge;
    }
}

int main()
{
    vector<Statesman> contenders;
    ofstream cleanFile("index.txt");
    cleanFile << "";
    cleanFile.close();
    srand(time(NULL));

    setup(contenders);

    for (int year = 1; year <= 200; year++)
    {
        progressYear(contenders);
    }
    cout << "PSI: " << StabilityScore << endl;
    cout << lowestConsulAge << ':' << averageConsulAge / 200 << ':' << highestConsulAge << endl;
    cout << lowestPraetorAge << ':' << averagePraetorAge / 200 << ':' << highestPraetorAge << endl;
    cout << lowestAedileAge << ':' << averageAedileAge / 200 << ':' << highestAedileAge << endl;
    cout << lowestQuaestorAge << ':' << averageQuaestorAge / 200 << ':' << highestQuaestorAge << endl;

    cout << endl;
    cout << "Consul Fill Rate: " << static_cast<float>(consulCount) / (2 * 200) * 100 << '%' << endl;
    cout << "Praetor Fill Rate: " << static_cast<float>(praetorCount) / (8 * 200) * 100 << '%' << endl;
    cout << "Aedile Fill Rate: " << static_cast<float>(aedileCount) / (10 * 200) * 100 << '%' << endl;
    cout << "Quaestor Fill Rate: " << static_cast<float>(quaestorCount) / (20 * 200) * 100 << '%' << endl;

    return 0;
}
