//treat maximal cliques as one vertex. if # of edges between two maximal cliques is above the threshold, connect the two vertices.
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>
#include <bitset>
#include <string>

using namespace std;

int n; //NO. of vertices
int e;  //NO. of edges
vector<vector<bool> >* vbits; //vector bool to store the adjacency matrix
vector<vector<bool> >* vbits1; //vector bool to store the result
vector<string> nodes;  // Node number to name mapping
map<string, int> node2num;  // Node name to number mapping
vector<vector<int> > cliques; // store all the maximal cliques 
int num_cliques;   // number of maximal cliques
int edges_t;    // the threshold of edges between maximal cliques

// splits a null terminated character array s into a vector of strings. c is the character to split on
void split(vector<string>& v, const char* s, char c)
{
    v.clear();
    while (true)
    {
        const char* begin = s;
        while (*s != c && *s) { ++s; }
        v.push_back(string(begin, s));
        if (!*s) break;
        if (!*++s) break;
    }
    if (*--s == c)                            //if last character is c, append another empty string
        v.push_back("");
}

// function to read the graph file
void read_graph(char* graph)
{
    int i = 0;
    int row, col;
    string node1, node2;
    ifstream input(graph);
    if(!input)
    {
        cerr << "Error - Unable to open file " << graph << endl;
        exit(EXIT_FAILURE);
    }
    //read the number of vertices and edges
    input >> n >> e;
    //allocate the memory for vector bool, nodes, and node2num
    vbits = new vector<vector<bool> >(n, vector<bool>(n));
    vbits1 = new vector<vector<bool> >(num_cliques, vector<bool>(num_cliques));
    nodes.resize(n);
    node2num.clear();
    input >> node1 >> node2;
    while(input)
    {
        if (node2num.find(node1) != node2num.end()) 
        {
            row = node2num[node1];
        }else 
        {
            nodes[i] = node1;
            node2num[node1] = i;
            row = i++;
        }
        if (node2num.find(node2) != node2num.end()) 
        {
            col = node2num[node2];
        }else 
        {
            nodes[i] = node2;
            node2num[node2] = i;
            col = i++;
        }
        (*vbits)[row][col]=1;
        (*vbits)[col][row]=1;
        input >> node1 >> node2;
    }
    input.close();
    //set the diagonal of the matrix to 1
    for(int j=0; j<n; j++)
        (*vbits)[j][j] = 1;
}

// function to read the maximal cliques
void read_maximal_cliques(char* graphs)
{
    int i,j;
    vector <string> line;
    string str;
    ifstream fp;
    cliques.resize(num_cliques);

    fp.open(graphs);
    if (!fp) {
        cerr << "Error opening input file '" << graphs << "'\n";
        exit(1);
    }

    j = 0;
    while (getline(fp, str))
    {
        split(line, str.c_str(), '\t');
        for (i=0; i<line.size(); i++)                //parse each value
        {
            cliques[j].push_back(node2num[line[i]]);
        }
        j++;
    }
    fp.close();
}

// function to compute the edges between maximal cliques
void com_edges()
{
    for(int i=0; i<num_cliques-1; i++)
    {
        for(int j=i+1; j<num_cliques; j++)
        {
            int counter = 0;
            
            for(int k=0; k<cliques[i].size(); k++)
            {
                for(int s=0; s<cliques[j].size(); s++)
                {
                    if((*vbits)[cliques[i][k]][cliques[j][s]])
                    {
                        counter++;
                    }
                }
            }
            //cout<< counter << endl;
            if(counter >= edges_t)
            {
                (*vbits1)[i][j] = 1;
                (*vbits1)[j][i] = 1;
            }
        }
    }

    //set the diagonal of the matrix to 0
    for(int j=0; j<num_cliques; j++)
        (*vbits1)[j][j] = 0;

}

int main(int argc, char* argv[])
{
    num_cliques = atoi(argv[3]);
    edges_t = atoi(argv[4]);
    read_graph(argv[1]);

    //test for read_graph
    /*for(int i=0; i<n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout<< (*vbits)[i][j] << " ";
        }
        cout<< endl;
    }
    for(int i=0; i<n; i++)
    {
        cout<< nodes[i] << " " << node2num[nodes[i]] << endl;
    }*/

    read_maximal_cliques(argv[2]); 

    //test for read_maximal_cliques
    /*for(int i=0; i<num_cliques; i++)
    {
        for (int j = 0; j < cliques[i].size(); j++)
        {
            cout<< nodes[cliques[i][j]] << " ";
        }
        cout<< endl;
    }*/

    com_edges();

    // output the edge list
    for(int i=0; i<num_cliques; i++)
    {
        for (int j = i+1; j < num_cliques; j++)
        {
            //note here
            if((*vbits1)[i][j])
                cout<< i << " " << j << endl;
        }
    }

}
