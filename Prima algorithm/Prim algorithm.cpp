#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <cmath>
#include <set>

/*=========================================================================================================*/

const int MAX = INT_MAX;

/*=========================================================================================================*/

std::vector <std::vector <int> > inputAdjacencyMatrixFromFile();

bool checkForConnectivity(const std::vector <std::vector <int> >& adjacencyMatrix);

void primAlgorithm(const std::vector <std::vector <int> >& adjacencyMatrix);

void writeOutputToFile(const std::vector <std::pair <int, int> >& output, const int& weight);

/*=========================================================================================================*/

int main()
{
    std::vector <std::vector <int> > adjacencyMatrix = inputAdjacencyMatrixFromFile();

    if (!checkForConnectivity(adjacencyMatrix))
    {
        std::cout << "The graph is disconnected!";
        return 0;
    }

    primAlgorithm(adjacencyMatrix);
}

/*=========================================================================================================*/

std::vector <std::vector <int> > inputAdjacencyMatrixFromFile()
{
    std::ifstream reader("test1.txt"); //test1.txt - test6.txt

    if (reader.is_open())
    {
        int numOfVertexes;

        reader >> numOfVertexes;

        std::vector < std::vector <int > > adjacencyMatrix(numOfVertexes, std::vector <int>(numOfVertexes));

        for (int i = 0; i < numOfVertexes; ++i)
            for (int j = 0; j < numOfVertexes; ++j)
                if (!reader.eof())
                    reader >> adjacencyMatrix[i][j];
                else
                    break;

        reader.close();

        return adjacencyMatrix;
    }
    else
    {
        reader.close();

        std::cout << "File Alert!";

        std::exit(0);
    }
}

bool checkForConnectivity(const std::vector <std::vector <int> >& adjacencyMatrix)
{
    std::queue <int> snake;
    std::vector <bool> visitedVertexes(adjacencyMatrix.size(), false);

    visitedVertexes[0] = true;
    snake.push(0);

    while (!snake.empty())
    {
        int vertex = snake.front();
        snake.pop();

        for (int i = 0; i < adjacencyMatrix[vertex].size(); ++i)
            if (adjacencyMatrix[vertex][i] && !visitedVertexes[i])
            {
                snake.push(i);
                visitedVertexes[i] = true;
            }
    }

    return all_of(visitedVertexes.begin(), visitedVertexes.end(), [](bool value) { return value; });
}

void primAlgorithm(const std::vector <std::vector <int> >& adjacencyMatrix)
{
    std::vector <bool> usedVertexes(adjacencyMatrix.size(), false);
    usedVertexes[0] = true;

    std::vector <std::pair <int, int> > output;

    int countEdges = 0, row, column, weight = 0;

    while (countEdges < adjacencyMatrix.size() - 1)
    {
        int min = MAX;

        row = column = 0;

        for (int i = 0; i < adjacencyMatrix.size(); ++i)
            if (usedVertexes[i])
                for (int j = 0; j < adjacencyMatrix[i].size(); ++j)
                    if (!usedVertexes[j] && adjacencyMatrix[i][j] && min > adjacencyMatrix[i][j])
                    {
                        min = adjacencyMatrix[i][j];
                        row = i;
                        column = j;
                    }

        weight += adjacencyMatrix[row][column];

        std::pair <int, int> tempCoordinates = { row, column };

        output.push_back(tempCoordinates);

        usedVertexes[column] = true;

        ++countEdges;
    }

    writeOutputToFile(output, weight);
}

void writeOutputToFile(const std::vector <std::pair <int, int> >& output, const int& weight)
{
    std::cout << "The weight of the MTS is " << weight << "!\nThe MTS is written to a file output.txt!\n";

    std::ofstream writer;
    writer.open("output.txt");

    if (writer.is_open())
    {
        writer << "The minimum MTS is:\n";

        for (const auto& edge : output)
            writer << edge.first << " - " << edge.second << std::endl;

        writer.close();
    }
    else
    {
        writer.close();

        std::cout << "File Alert!\n";
    }
}