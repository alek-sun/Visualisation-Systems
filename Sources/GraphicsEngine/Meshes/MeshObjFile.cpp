#include "MeshObjFile.h"
#include "GraphicsEngine/Application.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::cout;
using std::endl;
using std::string;
using std::vector;

MeshObjFile::MeshObjFile(const char * filepath)
{
	m_filepath = Application::Instance().GetDataDirectory() + "/" + filepath;
}

vector<double> getValD(vector<string> strings) {
	vector<double> doubles;
	for (string s : strings) {
		doubles.push_back(atof(s.c_str()));
	}
	return doubles;
}

vector<int> getValI(vector<string> strings) {
	vector<int> ints;
	for (string s : strings) {
		ints.push_back(atoi(s.c_str()));
	}
	return ints;
}

vector<int> correctIndexes(vector<int> indexes) {
	for (int i = 0; i < indexes.size(); ++i) {
		indexes[i]-=1;
	}
	return indexes;
}

vector<string> getStrings(string str, char del) {
	vector<string> v;
	size_t iBegin = 0;
	size_t iEnd;
	do {
		iEnd = str.find(del, iBegin);
		string substr = str.substr(iBegin, iEnd - iBegin);
		v.push_back(substr);
		iBegin = iEnd + 1;
	} while (iEnd != string::npos);
	
	return v;
}

vector<double> handleStrings(string str) {
	vector<string> strings = getStrings(str, ' ');
	return getValD(strings);
}

void MeshObjFile::Init()
{
	Mesh::Init();

	vector<Vector3> vertices;
	vector<Vector3> normals;
	vector<Vector3> uv0;

	vector<int> vertexInd;
	vector<int> textureInd;
	vector<int> normalInd;

	std::ifstream in;
	in.open(m_filepath);

	if (!in) {
		cout << "File not opened : " << m_filepath << endl;
		exit(1);
	}
	string str;

	size_t polygonSize;

	while (std::getline(in, str)) {
		cout << str << endl;
		if (str[0] == 'v') {
			if (str[1] == ' ') {
				str = str.substr(2);
				vector<double> vertCoords = handleStrings(str);
				vertices.push_back(Vector3(vertCoords[0], vertCoords[1], vertCoords[2]));
			}
			else if (str[1] == 'n') {
				str = str.substr(3);
				vector<double> normalCoords = handleStrings(str);
				normals.push_back(Vector3(normalCoords[0], normalCoords[1], normalCoords[2]));
			}
			else if (str[1] == 't') {
				str = str.substr(3);
				vector<double> uvCoords = handleStrings(str);
				uv0.push_back(Vector3(uvCoords[0], uvCoords[1], 0));
			}			
		}
		else if (str[0] == 'f') {
			str = str.substr(2);
			vector<string> strings = getStrings(str, ' ');
			polygonSize = strings.size();
			for (string s : strings) {
				vector<string> inds = getStrings(s, '/');
				vector<int> indsNumbers = getValI(inds);
				indsNumbers = correctIndexes(indsNumbers);
				vertexInd.push_back(indsNumbers[0]);
				textureInd.push_back(indsNumbers[1]);
				normalInd.push_back(indsNumbers[2]);
			}
		}
	}

	vector<Vector4> colors;
	for (int i = 0; i < vertices.size(); i++) {
		colors.push_back(Vector4(1.0, 1.0, 1.0, 1.0));
	}

	meshImpl->SetVertices(vertices);
	meshImpl->SetColors(colors);
	meshImpl->SetNormals(normals);
	meshImpl->SetUV0(uv0);

	meshImpl->SetIndices(vertexInd, MESH_TOPOLOGY_TRIANGLE_LIST);

	meshImpl->Apply();
}

void MeshObjFile::Deinit()
{
	Mesh::Deinit();
}
